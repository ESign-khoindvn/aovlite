ARCHS = arm64
DEBUG = 0
FINALPACKAGE = 1
FOR_RELEASE = 1

TARGET = iphone:latest:14.5
include $(THEOS)/makefiles/common.mk

FRAMEWORK_NAME = AWSS3

HOOK_SRC = $(wildcard hook/*.c)
IMGUI_SRC = $(wildcard imgui/*.cpp) $(wildcard imgui/*.mm)
LOAD_SRC = $(wildcard load/*.mm) $(wildcard load/*.m)

$(FRAMEWORK_NAME)_FRAMEWORKS =  UIKit SafariServices Accelerate Foundation QuartzCore CoreGraphics AudioToolbox CoreText Metal MobileCoreServices Security SystemConfiguration IOKit CoreTelephony CoreImage CFNetwork AdSupport AVFoundation

$(FRAMEWORK_NAME)_LDFLAGS +=  -lresolv -lz -liconv hook/Ryoma.a libAuth/Auth.a

$(FRAMEWORK_NAME)_CCFLAGS = -std=c++17 -fno-rtti -fno-exceptions -DNDEBUG -Wall -Wno-deprecated-declarations -Wno-unused-variable -Wno-unused-value -Wno-unused-function -fvisibility=hidden -fexceptions

$(FRAMEWORK_NAME)_CFLAGS = -fobjc-arc -Wall -Wno-deprecated-declarations -Wno-unused-variable -Wno-unused-value -Wno-unused-function -fvisibility=hidden

# SSZipArchive minizip: suppress old-C warnings
helper/SSZipArchive/minizip/ioapi.m_CFLAGS = -Wno-deprecated-non-prototype -Wno-error
helper/SSZipArchive/minizip/zip.m_CFLAGS   = -Wno-unused-but-set-variable -Wno-error
helper/SSZipArchive/minizip/unzip.m_CFLAGS = -Wno-error

HELPER_SRC = helper/ModFile.m helper/VideoSanh.m helper/SSZipArchive/SSZipArchive.m $(wildcard helper/SSZipArchive/minizip/*.m)

$(FRAMEWORK_NAME)_FILES = ImGuiDrawView.mm helper/FakeEnc.xm $(HELPER_SRC) $(HOOK_SRC) $(LOAD_SRC) $(IMGUI_SRC)


include $(THEOS_MAKE_PATH)/framework.mk


