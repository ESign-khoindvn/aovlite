#import <mach-o/loader.h>
#import <mach-o/getsect.h>
#import <mach-o/dyld.h>
#import <dlfcn.h>
#import <objc/runtime.h>
#import <sys/stat.h>
#import <dirent.h>
#import <unistd.h>
#import <Security/Security.h>
#import <CoreFoundation/CoreFoundation.h>
#import "hook/fishhook.h"


//Fix
typedef struct __SecTask *SecTaskRef;

extern CFTypeRef SecTaskCopyValueForEntitlement(
    SecTaskRef task,
    CFStringRef entitlement,
    CFErrorRef *error
);


//Fake Encrypt AppStore
const struct encryption_info_command_64 *fake_get_encryption_info_64(struct mach_header_64 *mh) {
    static struct encryption_info_command_64 fake = {0};
    fake.cmd = LC_ENCRYPTION_INFO_64;
    fake.cmdsize = sizeof(struct encryption_info_command_64);
    fake.cryptoff = 0;
    fake.cryptsize = 0;
    fake.cryptid = 1;   //giả mạo App đang được mã hóa như App Store
    return &fake;
}


// ======================================================
//  DANH SÁCH DYLIB PHẢI ẨN
// ======================================================
const char *blockedDylibList[] = {
    "imgui.dylib",
    "cheat",
    "libhook",
    "iosipadl",
    "AOVIOSTUTORIALS",
    "AWSS3",

    // Dobby
    "Dobby",
    "libdobby",
    "dobby",

    // Substrate
    "libsubstrate",
    "CydiaSubstrate",
    "MobileSubstrate",
    "SubstrateLoader",
    "MSHookFunction",
    "MSHookMessageEx",

    // HookZz & CaptainHook
    "hookzz",
    "HookZz",
    "libhookzz",
    "CaptainHook",

    // Frida
    "frida",
    "frida-agent",
    "frida-gadget",
    "libfrida",

    // MonkeyDev
    "MonkeyDev",
    "theos",
    "tweak.dylib",

    // Flex
    "flex",
    "libflex",

    // Common jailbreak dylibs
    "libjailbreak",
    "libhooker",
    "substitute",
    "libsubstitute",
};

// ======================================================
//  DANH SÁCH FILE / FOLDER CẦN ẨN
// ======================================================
const char *blockedPathList[] = {
    "/var/jb",
    "/var/jb/usr",
    "/var/jb/etc",
    "/var/jb/Library",
    "/var/jb/Applications",
    "/var/jb/usr/bin/jbctl",
    "/var/jb/usr/lib/libjailbreak",
    "/private/preboot",
    "/private/preboot/procursus",
    "/var/lib/jb",

    // Electra/Chimera/Unc0ver
    "/usr/sbin/frida-server",
    "/usr/lib/libjailbreak.dylib",
    "/.installed_unc0ver",
    "/jb/offsets.plist",

    // Substrate
    "/Library/MobileSubstrate",
    "/Library/MobileSubstrate/DynamicLibraries",

    // Cydia
    "/Applications/Cydia.app",
    "/var/lib/cydia",
    "/etc/apt",

    // TrollStore
    "/Applications/TrollStore.app",
    "/var/containers/Bundle/Application/TrollStore.app",

    NULL
};


// ======================================================
//  CHECK DYLIB
// ======================================================
BOOL shouldHideImage(const char *path) {
    if (!path) return NO;
    for (int i = 0; blockedDylibList[i]; i++) {
        if (strstr(path, blockedDylibList[i])) return YES;
    }
    return NO;
}


// ======================================================
//  CHECK PATH
// ======================================================
BOOL shouldBlockPath(const char *path) {
    if (!path) return NO;
    for (int i = 0; blockedPathList[i]; i++) {
        if (strstr(path, blockedPathList[i])) return YES;
    }
    return NO;
}


// ======================================================
//  HOOK DYLD IMAGE NAME
// ======================================================
const char *(*orig_dyld_get_image_name)(uint32_t);
const char *safe_dyld_get_image_name(uint32_t i) {
    const char *name = orig_dyld_get_image_name(i);
    return shouldHideImage(name) ? "/usr/lib/libobjc.A.dylib" : name;
}


// ======================================================
//  HOOK dladdr
// ======================================================
int (*orig_dladdr)(const void *, Dl_info *);
int safe_dladdr(const void *addr, Dl_info *info) {
    int r = orig_dladdr(addr, info);
    if (r && info && shouldHideImage(info->dli_fname)) {
        memset(info, 0, sizeof(Dl_info));
        return 0;
    }
    return r;
}


// ======================================================
//  HOOK objc_copyClassNamesForImage
// ======================================================
char **(*orig_objc_copyClassNamesForImage)(const char *, unsigned int *);
char **safe_objc_copyClassNamesForImage(const char *image, unsigned int *outCount) {
    if (shouldHideImage(image)) {
        if (outCount) *outCount = 0;
        return NULL;
    }
    return orig_objc_copyClassNamesForImage(image, outCount);
}


// ======================================================
//  HOOK FILE API (stat/access/fopen/opendir)
// ======================================================
int (*orig_stat)(const char *, struct stat *);
int safe_stat(const char *path, struct stat *buf) {
    if (shouldBlockPath(path)) return -1;
    return orig_stat(path, buf);
}

int (*orig_access)(const char *, int);
int safe_access(const char *path, int mode) {
    if (shouldBlockPath(path)) return -1;
    return orig_access(path, mode);
}

FILE *(*orig_fopen)(const char *, const char *);
FILE *safe_fopen(const char *path, const char *mode) {
    if (shouldBlockPath(path)) return NULL;
    return orig_fopen(path, mode);
}

DIR *(*orig_opendir)(const char *);
DIR *safe_opendir(const char *path) {
    if (shouldBlockPath(path)) return NULL;
    return orig_opendir(path);
}


// ======================================================
//   SecTaskCopyValueForEntitlement  *** PHẦN NÀY ẨN ĐƯỢC TOÀN BỘ JAILBREAK ROOTLESS***
// ======================================================

typedef CFTypeRef (*SecTaskCopyValueForEntitlement_t)(SecTaskRef task, CFStringRef entitlement, CFErrorRef *error);
SecTaskCopyValueForEntitlement_t orig_SecTaskCopyValueForEntitlement;

CFTypeRef safe_SecTaskCopyValueForEntitlement(SecTaskRef task, CFStringRef key, CFErrorRef *error) {

    static const char* blockedEnt[] = {
        "get-task-allow",
        "com.apple.private.security.no-sandbox",
        "com.apple.private.skip-library-validation",
        "task_for_pid-allow",
        "com.apple.system-task-ports",
        NULL
    };

    char ent[256] = {0};
    CFStringGetCString(key, ent, sizeof(ent), kCFStringEncodingUTF8);

    for (int i = 0; blockedEnt[i]; i++) {
        if (strcmp(ent, blockedEnt[i]) == 0) {
            return NULL;
        }
    }

    return orig_SecTaskCopyValueForEntitlement(task, key, error);
}


// ======================================================
//  INSTALL HOOKS
// ======================================================
int (*orig_lstat)(const char *, struct stat *);


__attribute__((constructor))
static void init_hide_jb_and_dylib() {

    struct rebinding rebs[] = {
        {"dyld_get_image_name", (void *)safe_dyld_get_image_name, (void **)&orig_dyld_get_image_name},
        {"dladdr", (void *)safe_dladdr, (void **)&orig_dladdr},
        {"objc_copyClassNamesForImage", (void *)safe_objc_copyClassNamesForImage, (void **)&orig_objc_copyClassNamesForImage},

        {"stat", (void *)safe_stat, (void **)&orig_stat},
        {"lstat", (void *)safe_stat, (void **)&orig_lstat},  // FIXED: dùng đúng biến orig_lstat
        {"access", (void *)safe_access, (void **)&orig_access},
        {"fopen", (void *)safe_fopen, (void **)&orig_fopen},
        {"opendir", (void *)safe_opendir, (void **)&orig_opendir},

        {"SecTaskCopyValueForEntitlement",
            (void *)safe_SecTaskCopyValueForEntitlement,
            (void **)&orig_SecTaskCopyValueForEntitlement},
    };

    rebind_symbols(rebs, sizeof(rebs) / sizeof(rebs[0]));
}


