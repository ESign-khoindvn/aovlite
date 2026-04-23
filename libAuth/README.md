# AnhvuAuth Library - Hướng Dẫn Tích Hợp

## 📦 Files
- `Auth.a` - Thư viện static (arm64)
- `Auth.h` - Header file

## 🚀 Makefile

```makefile
TWEAK_NAME = YourTweak
$(TWEAK_NAME)_OBJ_FILES = libAuth/Auth.a
$(TWEAK_NAME)_FILES = Tweak.xm
$(TWEAK_NAME)_FRAMEWORKS = UIKit Foundation
```

## 💡 Cách Dùng

```objectivec
#import "libAuth/Auth.h"

// Khởi tạo auth
[[AnhvuAuth shareInstance] packages:@"YOUR_TOKEN" 
                    onAuthenticated:^{
    NSLog(@"✅ Xác thực thành công!");
    
    // Code của bạn ở đây
}];
```

## 📋 Filter.plist

```plist
{ Filter = { Executables = ( "YourApp" ); }; }
```

## 🔨 Build

```bash
 make
```

## ✅ Checklist

- Copy `Auth.a` và `Auth.h` vào `libAuth/`
- Thay `YOUR_TOKEN` bằng token thật
- Cấu hình Filter.plist với app target
- Build và test

## 🐛 Debug

```bash
# Xem log
idevicesyslog | grep "Tweak\|Auth"
```
