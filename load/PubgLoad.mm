#import "PubgLoad.h"
#import <UIKit/UIKit.h>
#import <CoreFoundation/CoreFoundation.h>
#import "../libAuth/Auth.h"
#import "../helper/Obfuscatee.h"

#import "JHPP.h"
#import "JHDragView.h"
#import "ImGuiLoad.h"
#import "ImGuiDrawView.h"

@interface PubgLoad()
@property (nonatomic, strong) ImGuiDrawView *vna;
@end

@implementation PubgLoad

static PubgLoad *extraInfo;
UIWindow *mainWindow2;

- (void)tapIconView {
    if (!_vna) {
        ImGuiDrawView *vc = [[ImGuiDrawView alloc] init];
        _vna = vc;
    }
    [ImGuiDrawView showChange:true];
    [[UIApplication sharedApplication].windows[0].rootViewController.view addSubview:_vna.view];
}

@end

static void didFinishLaunching(CFNotificationCenterRef center, void *observer, CFStringRef name, const void *object, CFDictionaryRef info) {
    /* [[AnhvuAuth shareInstance]
        packages:NSOBFUSCATE("3EpNe64rLnGcYxjGnuXDFyf6Fl5F8ke2snW8RSMvuOKF5owdvvD9oHPsrJZ9ugwV")
        onAuthenticated:^{ */
            dispatch_async(dispatch_get_main_queue(), ^{
                mainWindow2 = [UIApplication sharedApplication].keyWindow;
                extraInfo = [PubgLoad new];
                [extraInfo tapIconView];
            });
        //}];
}

__attribute__((constructor)) static void initialize() {
    CFNotificationCenterAddObserver(
        CFNotificationCenterGetLocalCenter(),
        NULL,
        &didFinishLaunching,
        (CFStringRef)UIApplicationDidFinishLaunchingNotification,
        NULL,
        CFNotificationSuspensionBehaviorDrop
    );
}
