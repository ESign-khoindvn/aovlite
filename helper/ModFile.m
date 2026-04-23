#import "ModFile.h"
#import <mach/mach.h>
#include <sys/sysctl.h>
#include <sys/param.h>
#include <sys/mount.h>
#import <SystemConfiguration/SystemConfiguration.h>
#import <SafariServices/SafariServices.h>
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <MobileCoreServices/MobileCoreServices.h>
#import <UIKit/UIKit.h>
#import <MobileCoreServices/MobileCoreServices.h>
#import "SSZipArchive/SSZipArchive.h"


#define SCREEN_WIDTH [UIScreen mainScreen].bounds.size.width


@interface main () <UIGestureRecognizerDelegate, UIImagePickerControllerDelegate, UINavigationControllerDelegate>


@property (nonatomic, strong) UIDocumentPickerViewController *documentPicker;

@end

@implementation main{
    UIDocumentPickerViewController *_documentPicker;
}

static main *extraInfo;

+ (instancetype)sharemain {
    static main *sharemain;
    static dispatch_once_t onceToken;

    dispatch_once(&onceToken, ^{
        sharemain = [[main alloc] init];
    });

    return sharemain;
}

+ (void)load {
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(4 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        [main sharemain];
    });
}

- (instancetype)init {
    self = [super init];
    if (self) {
 
        }
    return self;
}
- (void)modskinquafile {
_documentPicker = [[UIDocumentPickerViewController alloc] initWithDocumentTypes:@[@"public.zip-archive"] inMode:UIDocumentPickerModeImport];
    _documentPicker.delegate = self;

    if (@available(iOS 11.0, *)) {
        _documentPicker.allowsMultipleSelection = NO;
    }

    UIViewController *rootViewController = [[[UIApplication sharedApplication] keyWindow] rootViewController];
    [rootViewController presentViewController:_documentPicker animated:YES completion:nil];
}

- (void)documentPicker:(UIDocumentPickerViewController *)controller didPickDocumentsAtURLs:(NSArray<NSURL *> *)urls {
    NSURL *fileURL = urls.firstObject;

    [self giainen:fileURL];
    [controller dismissViewControllerAnimated:YES completion:nil];
}

- (void)cancel:(UIDocumentPickerViewController *)controller {
    [controller dismissViewControllerAnimated:YES completion:nil];
}

- (void)giainen:(NSURL *)url {
    NSString *filePath = [url path];

    // Di chuyển file zip đến thư mục của ứng dụng
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *documentsDir = [paths objectAtIndex:0];
    NSString *destinationPath = [documentsDir stringByAppendingPathComponent:[url lastPathComponent]];

    NSFileManager *fileManager = [NSFileManager defaultManager];
    NSError *error;

    BOOL success = [fileManager moveItemAtPath:filePath toPath:destinationPath error:&error];

    if (!success) {
        NSLog(@"Lỗi khi di chuyển file zip: %@", error.localizedDescription);
        return;
    }

    // Giải nén tệp zip vào thư mục "Resources" hiện tại
    NSString *dataPath = [documentsDir stringByAppendingPathComponent:@"/"]; //thực hiện ghi đè
    success = [SSZipArchive unzipFileAtPath:destinationPath toDestination:dataPath];

    if (success) {
        NSLog(@"Giải nén thành công vào thư mục Resources");

        // Xóa file zip sau khi giải nén thành công
        [fileManager removeItemAtPath:destinationPath error:&error];
        if (error) {
            NSLog(@"Lỗi khi xóa file zip: %@", error.localizedDescription);
        }

        // Hiển thị thông báo thành công
        [self modsuccess];
    } else {
        NSLog(@"Lỗi khi giải nén: %@", error.localizedDescription);
    }
}

- (void)modsuccess {
    UIViewController *rootViewController = [[[UIApplication sharedApplication] keyWindow] rootViewController];

    UIAlertController *alert = [UIAlertController alertControllerWithTitle:@"🎉 Thành Công!"
                                                                  message:@"Mod đã được cài đặt thành công!\nỨng dụng sẽ tự thoát sau 2 giây."
                                                           preferredStyle:UIAlertControllerStyleAlert];

    [rootViewController presentViewController:alert animated:YES completion:nil];

    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(2.0 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        [alert dismissViewControllerAnimated:YES completion:^{
            exit(0);
        }];
    });
}


@end