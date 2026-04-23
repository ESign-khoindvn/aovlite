#import <UniformTypeIdentifiers/UniformTypeIdentifiers.h>
#import "VideoSanh.h"
#import <UIKit/UIKit.h>
#import <Photos/Photos.h>
#import <MobileCoreServices/MobileCoreServices.h>


@interface VideoSanh () <UIImagePickerControllerDelegate, UINavigationControllerDelegate>

@end

@implementation VideoSanh

+ (void)pickVideo {
    UIImagePickerController *videoPicker = [[UIImagePickerController alloc] init];
    videoPicker.sourceType = UIImagePickerControllerSourceTypeSavedPhotosAlbum;
    videoPicker.mediaTypes = @[UTTypeMovie.identifier];
    videoPicker.delegate = (id<UINavigationControllerDelegate, UIImagePickerControllerDelegate>)self;
    UIViewController *rootVC = [UIApplication sharedApplication].keyWindow.rootViewController;
    [rootVC presentViewController:videoPicker animated:YES completion:nil];
}

+ (void)imagePickerController:(UIImagePickerController *)picker didFinishPickingMediaWithInfo:(NSDictionary<UIImagePickerControllerInfoKey, id> *)info {
    NSURL *videoURL = info[UIImagePickerControllerMediaURL];

    NSString *documentsPath = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) firstObject];
    NSString *savedVideoPath = [documentsPath stringByAppendingPathComponent:@"SavedVideo.mp4"];
    
    NSFileManager *fileManager = [NSFileManager defaultManager];
    if ([fileManager fileExistsAtPath:savedVideoPath]) {
        [fileManager removeItemAtPath:savedVideoPath error:nil];
    }
    
    NSError *error = nil;
    [fileManager copyItemAtPath:videoURL.path toPath:savedVideoPath error:&error];
    [picker dismissViewControllerAnimated:YES completion:^{
        if (!error) {
            [self processVideo];
        } else {
            [self showAutoAlert:@"❌ Error" message:@"Failed to save video."];
        }
    }];
}

+ (void)processVideo {
    UIAlertController *progressAlert = [UIAlertController alertControllerWithTitle:@"⏳ Processing"
                                        message:@"Replacing lobby video, please wait..."
                                preferredStyle:UIAlertControllerStyleAlert];
    UIViewController *rootVC = [UIApplication sharedApplication].keyWindow.rootViewController;
    [rootVC presentViewController:progressAlert animated:YES completion:nil];
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        NSString *documentsPath = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) firstObject];
        NSString *lobbyPath = [documentsPath stringByAppendingPathComponent:@"Extra/2022.V3/ISPDiff/LobbyMovie"];
        NSString *backupPath = [documentsPath stringByAppendingPathComponent:@"Extra/2022.V3/ISPDiff/LobbyMovie.backup"];
        
        NSFileManager *fileManager = [NSFileManager defaultManager];
        if (![fileManager fileExistsAtPath:backupPath]) {
            [fileManager createDirectoryAtPath:backupPath withIntermediateDirectories:YES attributes:nil error:nil];
        }

        // Backup original videos
        NSArray *lobbyVideos = [fileManager contentsOfDirectoryAtPath:lobbyPath error:nil];
        for (NSString *video in lobbyVideos) {
            NSString *srcPath = [lobbyPath stringByAppendingPathComponent:video];
            NSString *dstPath = [backupPath stringByAppendingPathComponent:video];
            [fileManager moveItemAtPath:srcPath toPath:dstPath error:nil];
        }

        // Replace each video with user's video (keep original filenames)
        NSString *savedVideoPath = [documentsPath stringByAppendingPathComponent:@"SavedVideo.mp4"];
        for (NSString *video in lobbyVideos) {
            NSString *dstPath = [lobbyPath stringByAppendingPathComponent:video];
            [fileManager copyItemAtPath:savedVideoPath toPath:dstPath error:nil];
        }

        // Cleanup temp file
        [fileManager removeItemAtPath:savedVideoPath error:nil];

        dispatch_async(dispatch_get_main_queue(), ^{
            [progressAlert dismissViewControllerAnimated:YES completion:^{
                [self showAutoAlert:@"🎉 Success!" message:@"Lobby video replaced!\nApp will exit in 2 seconds."];
            }];
        });
    });
}

+ (void)restoreVideo {
    NSString *documentsPath = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) firstObject];
    NSString *lobbyPath = [documentsPath stringByAppendingPathComponent:@"Extra/2022.V3/ISPDiff/LobbyMovie"];
    NSString *backupPath = [documentsPath stringByAppendingPathComponent:@"Extra/2022.V3/ISPDiff/LobbyMovie.backup"];
    
    NSFileManager *fileManager = [NSFileManager defaultManager];
    if (![fileManager fileExistsAtPath:backupPath]) {
        [self showAutoAlert:@"⚠️ Notice" message:@"No backup found."];
        return;
    }

    UIAlertController *progressAlert = [UIAlertController alertControllerWithTitle:@"⏳ Restoring"
                        message:@"Restoring original lobby video..."
                            preferredStyle:UIAlertControllerStyleAlert];
    UIViewController *rootVC = [UIApplication sharedApplication].keyWindow.rootViewController;
    [rootVC presentViewController:progressAlert animated:YES completion:nil];
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        if ([fileManager fileExistsAtPath:lobbyPath]) {
            [fileManager removeItemAtPath:lobbyPath error:nil];
        }
        [fileManager moveItemAtPath:backupPath toPath:lobbyPath error:nil];
        dispatch_async(dispatch_get_main_queue(), ^{
            [progressAlert dismissViewControllerAnimated:YES completion:^{
                [self showAutoAlert:@"🎉 Restored!" message:@"Original video restored!\nApp will exit in 2 seconds."];
            }];
        });
    });
}

// Auto-dismiss alert consistent with ModFile style → exit after 2s
+ (void)showAutoAlert:(NSString *)title message:(NSString *)message {
    UIViewController *rootVC = [UIApplication sharedApplication].keyWindow.rootViewController;
    UIAlertController *alert = [UIAlertController alertControllerWithTitle:title
                                                                  message:message
                                                           preferredStyle:UIAlertControllerStyleAlert];
    [rootVC presentViewController:alert animated:YES completion:nil];

    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(2.0 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        [alert dismissViewControllerAnimated:YES completion:^{
            exit(0);
        }];
    });
}

@end