
#include "LoadView/Includes.h"

#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <sys/sysctl.h>
#include <Foundation/Foundation.h>
#include <libgen.h>
#include <mach-o/dyld.h>
#include <mach-o/fat.h>
#include <mach-o/loader.h>
#include <mach/vm_page_size.h>
#include <unistd.h>
#include <array>
#include <deque>
#include <map>
#include <vector>
#include <algorithm>
#include <set>
#import <unordered_map>
#include <CoreFoundation/CoreFoundation.h>
#include <limits>
#import <UIKit/UIKit.h>
#include <chrono>

#import "modfile/ModFile.h"

#import "Hook/patch.h"

#import "imgui/stb_image.h"
#import "imgui/bdvt.h"
#import "imgui/json.hpp"

#import "../Utils/hack/Function.h"
#import "../Utils/EspManager.h"
#import "../Utils/hack/VInt3.h"
#import "../Utils/hack/Vector2.h"
#import "../Utils/hack/Vector3.h"
#import "../Utils/hack/Quaternion.h"
#import "../Utils/ESP.h"
#import "../Utils/Unity.h"


#import "mylib/Il2cpp.h"
#import "mylib/il2cpp-aov-1.61.h"
#import "Security/Obfuscatee.h"
#import "mylib/mahoa.h"
#import "mylib/stb_image.h"
#import "../mylib/CSProtocol.h"
#import "../mylib/MonoString.h"
#import "../mylib/hook.h"
#import "../mylib/Herolib.h"

// Item Icons
#import "../hocvienlienquan/GiapHoiSinh_icon.h"
#import "../hocvienlienquan/CauBangSuong_icon.h"
#import "../hocvienlienquan/LiemDoatMenh_icon.h"
#import "../hocvienlienquan/ThuongKhungKiem_icon.h"
#import "../hocvienlienquan/HerculesThinhNo_icon.h"
#import "../hocvienlienquan/CungTaMa_icon.h"
#import "../hocvienlienquan/XaNhatCung_icon.h"
#import "../hocvienlienquan/NhamThuan_icon.h"

#include "imgui/fonts/Icon.h"
#include "imgui/fonts/Iconcpp.h"
#include "imgui/fonts/ico_font.h"
#include "imgui/fonts/zzz.h"
#include "imgui/fonts/ProFont.h"


/* #import "Hook/Ryoma.h"
#define Hook(x, y, z) \
{ \
    NSString* result_##y = StaticInlineHookPatch(("Frameworks/UnityFramework.framework/UnityFramework"), x, nullptr); \
    if (result_##y) { \
        void* result = StaticInlineHookFunction(("Frameworks/UnityFramework.framework/UnityFramework"), x, (void *) y); \
        *(void **) (&z) = (void*) result; \
    } \
} */

#import "Hook/RyomaTF.h"
#define Hook(x, y, z) \
{ \
    void* result = StaticInlineHookFunction(("Frameworks/UnityFramework.framework/UnityFramework"), x, (void *) y); \
    *(void **) (&z) = (void*) result; \
}

#import <sstream>
using namespace std::chrono;
using namespace std;


#define Colorwhite ImVec4(1.0f, 1.0f, 1.0f, 1.0f)

#define timer(sec) dispatch_after(dispatch_time(DISPATCH_TIME_NOW, sec * NSEC_PER_SEC), dispatch_get_main_queue(), ^

#define iPhonePlus ([UIScreen instancesRespondToSelector:@selector(currentMode)] ? CGSizeEqualToSize(CGSizeMake(1242, 2208), [[UIScreen mainScreen] currentMode].size) : NO)

#define kWidth [UIScreen mainScreen].bounds.size.width
#define kHeight [UIScreen mainScreen].bounds.size.height
#define kWidth [UIScreen mainScreen].bounds.size.width
#define kHeight [UIScreen mainScreen].bounds.size.height
#define kScale [UIScreen mainScreen].nativeScale
#define screenHeight [UIScreen mainScreen].bounds.size.height
#define screenWidth [UIScreen mainScreen].bounds.size.width

bool hackmapenable = false;
bool BugChieu = false;
bool autoyue = false;


int solan = 0;
int goldcoin = 0;
bool giap = true;
bool bangsuongactive = true;
bool liem = true;
bool thuongkhung = true;
bool nhamthuan = true;
bool hercules = true;
int lastId = -1;
int stt = 0;
bool fullslot = false;
bool checktime = false;
uint16_t ItemID[6];
bool muaitem = false;
bool doiitem = false;

static auto lastCall = std::chrono::steady_clock::now();
static int step = 0;
static size_t currentIndex = 0;
static void *lastActorManager = NULL;
static std::vector<void *> effectQueue;
static std::vector<void *> effectQueue2;

int delayspam = 10;
static int spamMode = 0;
static bool spamemoji = false;
static bool Bhideemoji = false;
bool daloadoffset = false;
int counttime = 0;
static int refreshRate = 0;
NSTimer *updateTimer;
ImFont *_espFont;
ImFont *_iconFont;

static bool MenDeal = false;
UIWindow *mainWindow1;
static ImGuiDrawView *sharedInstance = nil;
NSUserDefaults *saveSetting = [NSUserDefaults standardUserDefaults];
void *CBattle_Instance = nullptr;
void *CRoleInfoManager_Instance = nullptr;
void *GameInput_Instance = nullptr;
void *LLogicCore_Instance = nullptr;
void *LBattleLogic = nullptr;

void *BattleSystem = nullptr;
void *LGameActorMgr_Instance = nullptr;
void *BattleLogic_Instance = nullptr;
bool m_isInHeroSelectState = false;
void *Req5 = nullptr;
void *Req6 = nullptr;
void *Req0 = nullptr;
void *Req1 = nullptr;
void *Req2 = nullptr;
void *Req3 = nullptr;
void *Req9 = nullptr;
int Req6_slotype = 0;
bool BugSkillDistance = true;
bool CancelAnimationElsu = true;
bool hookcancel = false;
float debugDistanceSub = 0;
void *Skill[50];
void *hideemoji;
bool isHookedEmoji = false;

Vector3 useSkillDirection1, useSkillDirection2, useSkillDirection3;
bool showlsd = true;
bool fixskin = false;
bool HackSao = false;
bool wingame = false;
bool Hacksaoenable = false;
bool ingame = false;
bool resetcam = false;
bool isFirst = true;
bool isFirstrun = true;
bool hookaim = false;
bool hookcamera = false;
bool hooklsd = false;
bool Camstraight = false;
bool load_offset = false;
int ActiveTab = 1;
bool EspMonster = false;
bool IgnoreInvisibleMon = false;
bool showMinimapMon = false;
bool showMonsterHp = false;
bool VipMon = false;
bool ESPEnable = true;
bool StreamerMode = false;
bool PlayerLine = false;
bool PlayerTalent = false;
bool CustomIconBT = false;
bool AimbotNew = false;
float CustomX = 1.0f;
float CustomY = 1.0f;
bool Drawicon = false;
static ImVec2 manhinh;
bool customIcon = false;
float customIconSize = 1.0f;
float boxWidthScreen = 0;
float customIconPOS = 0;
float iconradius = 0;
bool PlayerBox = false;
bool Circle3D = false;
bool unlocknut = false;
bool unlockskin = false;
int heroid = 0;
int Skinid = 0;
int heroid2 = 0;
int skinid2 = 0;
int CspHeroID = 0;
int CspSkinID = 0;
bool dungao = false;
bool EnableSkin = false;
static int BillBoard_ID = 0;
static int personalButtonID = 0;
static int SoldierSkinID = 0;
static int Button_Select = 0;
static int BillBoard_Select = 0;
static int SoldierSkinID_Select = 0;
static float customBTScale = 1.0f;
bool PlayerDistance = false;
bool PlayerName = false;
bool showMinimap = false;
bool hiencooldowns = false;
bool PlayerAlert = false;
bool IgnoreInvisible = false;
float MinimapX = 1;
float MinimapY = 1;
float MinimapSizeX = 1;
float MinimapSizeY = 1;
bool AimbotEnable = false;
bool Aimhook = false;
bool MANUALAIM = false;
bool enableSkill1 = false;
bool enableSkill2 = false;
bool enableSkill3 = false;
bool RangeSkill = false;
float speedSkill1 = 1.0f;
float speedSkill2 = 1.0f;
float speedSkill3 = 1.0f;
float RangeSkill1 = 1.0f;
float RangeSkill2 = 1.0f;
float RangeSkill3 = 1.0f;
bool Rangeauto = false;
float RangeSkill1auto = 1.0f;
float RangeSkill2auto = 1.0f;
float RangeSkill3auto = 1.0f;
bool AutoBP = false;
bool AutoBS = false;
bool AutoTT = false;
bool rongta = false;
int currentTimer = 0;
bool CeaserOnly = false;
bool SliderCamera = false;
float Camera = 1.0f;
float AutoBPHp = 13.7f;
float AutoBSHp = 50.0f;
size_t MinimapOffField[10];
void *Cam[10];
void *offset[50];
uint64_t offset_uint64[50];
void *Esp[50];
size_t EspField[50];
void *ActorLinkerOff[50];
size_t ActorLinkerOffField[50];
void *LActorRootOff[50];
size_t LActorRootOffField[50];
void *ModSkin[20];
size_t ModSkinOffField[20];
size_t ModRankOffField[20];
void *Antiban[20];
int MapType = 1;
bool ManualMinimap = false;
Vector2 MinimapOrg;
Vector2 MinimapPos;
Vector2 MinimapSizeImGUi;
Vector2 BigmapSizeImGUi;
Vector2 BigmapPos;
Vector2 MinimapSize;
Vector2 BigmapSize;
Vector2 minimapPos;
Vector2 bigmapPos;
float MinimapCenterX;
float MinimapCenterY;
float BigmapCenterX;
float BigmapCenterY;
float MinimapScale = 1;
int roomtype = 0;
bool isFliped = false;
int settingmode = 1;
int myTeam = 1;
int KillMode = 0, NameMode = 0;
bool unlocktb = false;
bool unlockbt = false;
int mode = 0, aimType = 0, drawType = 2, skillSlot;
bool fakerank = false;
int sosao = 234;
int rankht = 32;
int topnumber = 1;
int dauan = 30;
bool ChangeName = false;
int currentHeroId = 0;
int currentSkinId = 0;
std::string customname = "Name";
bool AutoWin = false;
map<uint64_t, Vector3> previousEnemyPositions;
bool isHookedSkin = false;
bool isHookedButton = false;
bool isHackMap = false;
bool isHooked = true;
float lerp(float a, float b, float t)
{
    return a + t * (b - a);
}

ImVec4 lerp(const ImVec4 &a, const ImVec4 &b, float t)
{
    return ImVec4(lerp(a.x, b.x, t), lerp(a.y, b.y, t), lerp(a.z, b.z, t), lerp(a.w, b.w, t));
}

monoString *CreateMonoString(const char *str)
{
    int length = (int)strlen(str);
    int startIndex = 0;
    monoString *(*String_CreateString)(void *instance, const char *str, int startIndex, int length) = (monoString * (*)(void *, const char *, int, int))((uintptr_t)offset[14]);
    return String_CreateString(NULL, str, startIndex, length);
}
CSProtocol *protocol = [[CSProtocol alloc] init];



struct EquipSkill
{
    int id;
    int cooldown;
    int index;
};
enum EquipID
{
    CauBangSuong = 1242,    // Cầu Băng Sương
    ThuanNhamThach = 1340,  // Thuẫn Nham Thạch
    ThuongKhungKiem = 1149, // Thương Khung Kiếm
    GiapHoiSinh = 1337,     // Giáp Hồi Sinh
    LiemDoatMenh = 11271,   // Liềm Đoạt Mệnh
    HerculesThinhNo = 1328, // Hercules Thịnh Nộ

    DaiDiaThanKhien = 16211, // Đại Địa Thần Khiên
    DaiDiaMaNhan = 16212,    // Đại Địa Ma Nhãn
    DaiDiaThanToc = 16213,   // Đại Địa Thần Tốc
    DaiDiaMoTroi = 16214,    // Đại Địa Mở Trói
    DaiDiaHoiHuyet = 16215,  // Đại Địa Hồi Huyết

    LietHoaThanKhien = 16231, // Liệt Hỏa Thần Khiên
    LietHoaMaNhan = 16232,    // Liệt Hỏa Ma Nhãn
    LietHoaThanToc = 16233,   // Liệt Hỏa Thần Tốc
    LietHoaMoTroi = 16234,    // Liệt Hỏa Mở Trói
    LietHoaHoiHuyet = 16235,  // Liệt Hỏa Hồi Huyết

    CungTaMa = 1145,  // Cung Tà Ma
    XaNhatCung = 1148 // Xạ Nhật Cung
};
struct ItemData
{
    int stt;
    int id;
    int cost;
    int sellPrice;
    int cd;
    int cdRemain;    // Cooldown còn lại (seconds)
    int lastSold;    // Thời điểm bán lần cuối
    int index;       // slot hiện tại (-1 nếu chưa có)
    int lastbuy;     // Thời điểm mua lần cuối
    bool shouldBuy;
    int cdmax;       // Cooldown tối đa
};
vector<ItemData> items = {
    {1, EquipID::GiapHoiSinh, 2400, 1440, 0, 0, 0, -1, 0, true, 150},    // Giáp hồi sinh
    {2, EquipID::CauBangSuong, 2200, 1320, 0, 0, 0, -1, 0, true, 75},    // Cầu băng sương
    {3, EquipID::LiemDoatMenh, 2000, 1200, 0, 0, 0, -1, 0, true, 120},   // Liềm đoạt mệnh
    {4, EquipID::ThuongKhungKiem, 2120, 1272, 0, 0, 0, -1, 0, true, 90}, // Thương khung kiếm
    {5, EquipID::ThuanNhamThach, 1980, 1188, 0, 0, 0, -1, 0, true, 60},  // Thuẫn Nham Thạch
    {6, EquipID::HerculesThinhNo, 2080, 1248, 0, 0, 0, -1, 0, true, 60}, // Hercules thịnh nộ
    {7, EquipID::CungTaMa, 2250, 1350, 0, 0, 0, -1, 0, true, 60},
    {8, EquipID::XaNhatCung, 2000, 1200, 0, 0, 0, -1, 0, true, 60},

};

struct ItemOption
{
    const char *name;
    ItemData item;
};
static const ItemOption itemOptions[] = {
    {"Giáp Hồi sinh", items[0]},
    {"Cầu Băng Sương", items[1]},
    {"Liềm Đoạt Mệnh", items[2]},
    {"Thương Khung Kiếm", items[3]},
    {"Thuẫn Nham Thạch", items[4]},
    {"Hercules Thịnh Nộ", items[5]},
    {"Cung Tà Ma", items[6]},
    {"Xạ Nhật Cung", items[7]}};
const int ITEM_COUNT = sizeof(itemOptions) / sizeof(ItemOption);
const int COMBO_COUNT = 8;
static int selectedIndices[COMBO_COUNT] = {0, 1, 2, 3, 4, 5, 6, 7};
static bool isEnabled[COMBO_COUNT] = {true, true, true, true, true, true, true, true};
static int itemDisplayOrder[COMBO_COUNT] = {0, 1, 2, 3, 4, 5, 6, 7};
static bool itemEnabled[COMBO_COUNT] = {true, true, true, true, true, true, true, true};
vector<ItemData> BuildSelectedItemsVector(vector<ItemData> &items, int displayOrder[COMBO_COUNT], bool isEnabled[COMBO_COUNT])
{
    vector<ItemData> selectedItems;
    for (int i = 0; i < COMBO_COUNT; ++i)
    {
        int itemIndex = displayOrder[i]; // Lấy index theo thứ tự sắp xếp
        if (itemIndex >= 0 && itemIndex < items.size() && isEnabled[itemIndex])
        {
            selectedItems.push_back(items[itemIndex]);
        }
    }
    return selectedItems;
}

// Load item icon textures
id<MTLTexture> itemIconTextures[8] = {nullptr};

void SwapItemOrder(int index1, int index2)
{
    if (index1 >= 0 && index1 < COMBO_COUNT && index2 >= 0 && index2 < COMBO_COUNT)
    {
        int temp = itemDisplayOrder[index1];
        itemDisplayOrder[index1] = itemDisplayOrder[index2];
        itemDisplayOrder[index2] = temp;
    }
}

void ShowItemControlMenu()
{
    ImGui::Text("Chọn & Sắp Xếp Đồ:");
    ImGui::Separator();
    
    float iconSize = 30.0f;
    float padding = 6.0f;
    
    static int draggedIndex = -1;
    
    ImGui::BeginGroup();
    
    for (int i = 0; i < COMBO_COUNT; ++i)
    {
        int itemIndex = itemDisplayOrder[i];
        
        if (i > 0) ImGui::SameLine(0, padding);
        
        ImGui::PushID(i);
        
        // Vẽ icon với alpha dựa trên enabled state
        if (itemIconTextures[itemIndex])
        {
            float alpha = itemEnabled[itemIndex] ? 1.0f : 0.25f;
            char btnId[32];
            sprintf(btnId, "##item%d", i);
            ImGui::ImageButton(
                btnId,
                (ImTextureID)(uintptr_t)itemIconTextures[itemIndex], 
                ImVec2(iconSize, iconSize),
                ImVec2(0, 0), ImVec2(1, 1),
                ImVec4(0, 0, 0, 0), // No background
                ImVec4(1, 1, 1, alpha)
            );
        }
        else
        {
            ImGui::Button("##empty", ImVec2(iconSize, iconSize));
        }
        
        // Click để toggle on/off
        if (ImGui::IsItemClicked())
        {
            itemEnabled[itemIndex] = !itemEnabled[itemIndex];
        }
        
        // Drag & Drop
        if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID))
        {
            draggedIndex = i;
            ImGui::SetDragDropPayload("ITEM_SWAP", &i, sizeof(int));
            
            // Preview khi kéo
            if (itemIconTextures[itemIndex])
            {
                ImGui::Image((ImTextureID)(uintptr_t)itemIconTextures[itemIndex], ImVec2(iconSize, iconSize));
            }
            
            ImGui::EndDragDropSource();
        }
        
        if (ImGui::BeginDragDropTarget())
        {
            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ITEM_SWAP"))
            {
                int sourceIdx = *(const int*)payload->Data;
                if (sourceIdx != i && sourceIdx >= 0 && sourceIdx < COMBO_COUNT && i >= 0 && i < COMBO_COUNT)
                {
                    // Swap positions
                    int temp = itemDisplayOrder[sourceIdx];
                    itemDisplayOrder[sourceIdx] = itemDisplayOrder[i];
                    itemDisplayOrder[i] = temp;
                }
            }
            ImGui::EndDragDropTarget();
        }
        
        ImGui::PopID();
    }
    
    ImGui::EndGroup();

}

void ShowSequentialItemCombosWithCheckbox()
{
    ShowItemControlMenu();
}


NSString *GetDocumentsPath()
{
    return NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES)[0];
}
void SaveToFile(const string &content)
{
    NSString *filePath = [GetDocumentsPath() stringByAppendingPathComponent:@"Test.txt"];
    ofstream outFile([filePath UTF8String], ios::app);
    if (outFile.is_open())
    {
        outFile << content << endl;
    }
}
void SaveToFile(int value)
{
    SaveToFile("giatri: " + to_string(value));
}
typedef struct
{
    float minScale;
    float maxScale;
    int minHeight;
    int maxHeight;
    int minWidth;
    int maxWidth;
    float scaleValue;
} DeviceScaleConfig;

DeviceScaleConfig scaleConfigs[] = {
    // Case 1: iPhone X & XS & 11 Pro (ưu tiên cao nhất)
    {3.0f, 3.0f, 375, 375, 812, 812, 0.5253f},

    // Case 2: iPhone XR
    {2.19f, 2.23f, 375, 375, 812, 812, 5.0f / 7},

    // Case 3: iPhone 7, 8, SE 2020, 2022
    {2.0f, 2.0f, 375, 375, 667, 667, 719.0f / 750},

    // Case 4: iPhone 12
    {3.0f, 3.0f, 390, 390, 844, 844, 0.505f},

    // Case 5: iPhone 7 Plus
    {2.59f, 2.62f, 414, 414, 736, 736, 2.0f / 3},

    // Case 6: iPhone 13/14 Pro
    {3.0f, 3.0f, 0, 400, 0, 9999, 0.5f},

    // Case 7: General case (ưu tiên thấp nhất)
    {2.0f, 2.0f, 0, 500, 0, 9999, 0.0f}};
float FindScaleConfig(float currentScale, int height, int width)
{
    for (int i = 0; i < sizeof(scaleConfigs) / sizeof(scaleConfigs[0]); i++)
    {
        DeviceScaleConfig config = scaleConfigs[i];

        bool scaleMatch = (currentScale >= config.minScale) && (currentScale <= config.maxScale);
        bool heightMatch = (height >= config.minHeight) && (height <= config.maxHeight);
        bool widthMatch = (width >= config.minWidth) && (width <= config.maxWidth);

        if (scaleMatch && heightMatch && widthMatch)
        {
            if (i == sizeof(scaleConfigs) / sizeof(scaleConfigs[0]) - 1)
            {
                return (5.0f * (currentScale + 2)) / 14;
            }
            return config.scaleValue * kScale;
        }
    }
    return (5.0f * (currentScale + 1)) / 14; // Default value
}
struct EntityInfo
{
    Vector3 myPos;
    Vector3 enemyPos;
    Vector3 moveForward;
    int ConfigID;
    float bullettime;
    float Ranger;
    int currentSpeed;
};
EntityInfo EnemyTarget1;
EntityInfo EnemyTarget2;
EntityInfo EnemyTarget3;



void DrawHeroSkinInfo()
{
    ImGui::Text("Hero ID: %u", currentHeroId);
    ImGui::SameLine();
    ImGui::Text("Skin ID: %u", currentSkinId);
}

static inline void OpenURL_iOS(const char *url_cstr)
{
    NSString *s = [NSString stringWithUTF8String:url_cstr ?: ""];
    NSURL *u = [NSURL URLWithString:s];
    if (!u)
        return;
    UIApplication *app = [UIApplication sharedApplication];
    if (@available(iOS 10.0, *))
    {
        [app openURL:u options:@{} completionHandler:nil];
    }
    else
    {
        [app openURL:u];
    }
}


struct Texture
{
    id<MTLTexture> texture;
    float height;
    float width;
};
id<MTLTexture> LoadImageFromMemory(id<MTLDevice> device, unsigned char *image_data, size_t image_size)
{
    CFDataRef imageData = CFDataCreate(kCFAllocatorDefault, image_data, image_size);
    CGDataProviderRef dataProvider = CGDataProviderCreateWithCFData(imageData);
    CGImageRef cgImage = CGImageCreateWithPNGDataProvider(dataProvider, NULL, false, kCGRenderingIntentDefault);
    CFRelease(imageData);
    CGDataProviderRelease(dataProvider);
    if (!cgImage)
    {
        return nil;
    }
    NSError *error = nil;
    MTKTextureLoader *textureLoader = [[MTKTextureLoader alloc] initWithDevice:device];
    NSDictionary *options = @{MTKTextureLoaderOptionSRGB : @(NO)};
    id<MTLTexture> texture = [textureLoader newTextureWithCGImage:cgImage options:options error:&error];

    if (error)
    {
        CGImageRelease(cgImage);
        return nil;
    }
    CGImageRelease(cgImage);
    return texture;
}
std::vector<unsigned char> Base64Decode(const std::string &in)
{
    std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    std::vector<unsigned char> out;
    std::vector<int> T(256, -1);
    for (int i = 0; i < 64; i++)
        T[base64_chars[i]] = i;

    int val = 0, valb = -8;
    for (unsigned char c : in)
    {
        if (T[c] == -1)
            break;
        val = (val << 6) + T[c];
        valb += 6;
        if (valb >= 0)
        {
            out.push_back(char((val >> valb) & 0xFF));
            valb -= 8;
        }
    }
    return out;
}
id<MTLTexture> LoadTextureFromBase64(id<MTLDevice> device, const std::string &base64)
{
    // 1. Giải mã Base64 thành dữ liệu nhị phân
    std::vector<unsigned char> decodedData = Base64Decode(base64);

    // 2. Load ảnh từ bộ nhớ
    int width, height, channels;
    unsigned char *imageData = stbi_load_from_memory(decodedData.data(), decodedData.size(), &width, &height, &channels, 4);
    if (!imageData)
    {
        NSLog(@"[Error] Failed to load image from Base64");
        return nil;
    }

    // 3. Tạo descriptor cho texture
    MTLTextureDescriptor *descriptor = [[MTLTextureDescriptor alloc] init];
    descriptor.pixelFormat = MTLPixelFormatRGBA8Unorm;
    descriptor.width = width;
    descriptor.height = height;
    descriptor.usage = MTLTextureUsageShaderRead;

    // 4. Tạo texture Metal
    id<MTLTexture> texture = [device newTextureWithDescriptor:descriptor];
    if (texture)
    {
        // Sao chép dữ liệu ảnh vào texture
        MTLRegion region = {{0, 0, 0}, {static_cast<NSUInteger>(width), static_cast<NSUInteger>(height), 1}};
        [texture replaceRegion:region mipmapLevel:0 withBytes:imageData bytesPerRow:width * 4];
    }
    else
    {
        NSLog(@"[Error] Failed to create texture");
    }

    // 5. Giải phóng bộ nhớ ảnh
    stbi_image_free(imageData);

    return texture;
}
vector<Texture> textures;
void AddTexturesFromImageData(id<MTLDevice> device)
{
    for (const auto &heroData : heroArray)
    {
        Texture tex;
        tex.texture = LoadImageFromMemory(device, heroData.data, heroData.size);
        if (tex.texture == nil)
            continue;
        tex.width = tex.texture.width;
        tex.height = tex.texture.height;
        textures.push_back(tex);
    }
}

void LoadItemIcons(id<MTLDevice> device)
{
    itemIconTextures[0] = LoadImageFromMemory(device, _GiapHoiSinh_data, _GiapHoiSinh_data_len);
    itemIconTextures[1] = LoadImageFromMemory(device, _CauBangSuong_data, _CauBangSuong_data_len);
    itemIconTextures[2] = LoadImageFromMemory(device, _LiemDoatMenh_data, _LiemDoatMenh_data_len);
    itemIconTextures[3] = LoadImageFromMemory(device, _ThuongKhungKiem_data, _ThuongKhungKiem_data_len);
    itemIconTextures[4] = LoadImageFromMemory(device, _NhamThuan_data, _NhamThuan_data_len);
    itemIconTextures[5] = LoadImageFromMemory(device, _HerculesThinhNo_data, _HerculesThinhNo_data_len);
    itemIconTextures[6] = LoadImageFromMemory(device, _CungTaMa_data, _CungTaMa_data_len);
    itemIconTextures[7] = LoadImageFromMemory(device, _XaNhatCung_data, _XaNhatCung_data_len);
}

struct ButtonMod {
    const char* name;
    int ButtonId;
};

static const ButtonMod ChooseButton[] = {
    {"Mặc Định", 0},
    {"Billow T-Rex Bất Bại", 56},
    {"Arthur Pompompurins", 58},
    {"Natalya Kuromis Heart", 59},
    {"Aya Cinnamorolls Dream", 60},
    {"Triệu Vân Chiến Thần Vô Song", 43},
    {"Yorn Conan Edogawa", 45},
    {"Hayate Siêu Đạo Chích Kid", 46},
    {"Rouie Linh Sứ", 40},
    {"Stuart Siêu Trùm", 42},
    {"TelAnnas Thứ Nguyên Vệ Thần", 44},    {"TelAnnas Hổ Phách", 38},  {"TelAnnas Lâm Quang Thánh Điệu", 32},
    {"Lauriel Thứ Nguyên Vệ Thần", 1},
    {"Điêu Thuyền Eternal Sailor Moon", 2},
    {"Eland'orr Tuxedo", 3},    {"Elandorr Chuyến Tàu Mơ Ước", 52},
    {"Alice Eternal Sailor Chibi Moon", 5},
    {"Butterfly Kim Ngư", 6},   {"Butterfly Khởi Nguyên", 7},   {"Butterfly EVO5", 33},
    {"Iggy Rimuru Tempest", 54},
    {"Qi Milim Nava", 55},
    {"Raz Gon", 8},
    {"Enzo Kurapika", 9},
    {"Nakroth Killua", 10}, {"Nakroth Quỷ Thương Liệp Đế", 15}, {"Nakroth Bạch Diện Chiến Thương", 17}, {"Nakroth Thứ Nguyên Vệ Thần", 52},
    {"Murad Tuyệt Thế Thần Binh", 11},   {"Murad Thiên Luân Kiếm Thánh", 20},
    {"Airi Thứ Nguyên Vệ Thần", 12},
    {"Yena Huyền Kiếm", 13},
    {"Veres Lưu Ly Long Mẫu", 14},
    {"Aya Công Chúa Cầu Vồng", 16},
    {"Capheny Bugcag Assembler", 49},   {"Capheny Càn Nguyên Điện Chủ", 27},
    {"Krixi Phù Thủy Thời Không", 19},
    {"Liliana Ma Pháp Tối Thượng", 21},
    {"Biron Yuji Itadori", 22},
    {"Tulen Satoru Gojo", 23},
    {"Lumia Lưỡng Nghi Long Hậu", 24},
    {"Vanhel Vệ Thần", 25},
    {"Violet Thứ Nguyên Vệ Thần", 26},  {"Violet Nobara Kugisaki", 34}, {"Violet Thần Long", 4},
    {"Billow Thiên Tướng - Độ Ách", 28},
    {"Bolt Baron Thiên Phủ - Tư Mệnh", 29},
    {"Veres Lưu Ly Long Mẫu", 30},
    {"Yena Huyền Kiếm", 31},
    {"Paine Megumi Fushiguro", 35},
    {"Zepphy Hổ Phách", 36},
    {"Florentino Hổ Phách", 37},
    {"Bijan Lữ Khách", 39}
};


struct BillboardMod {
    const char* name;
    int thongbaoId;
};

static const BillboardMod ChooseThongbao[] = {
    {"Mặc Định", 0},
    {"Aya Cinnamorolls Dream", 52},
    {"Arthur Pompompurins", 53},
    {"Natalya Kuromis Heart", 54},
    {"Verra My Melodys Love", 55},
    {"Yorn Conan Edogawa",35},
    {"Hayate Siêu Đạo Chích Kid", 36},  {"Hayate Tu Di Thánh Đế", 2},
    {"Rouie Linh Sứ", 40},
    {"Stuart Siêu Trùm", 42},
    {"Vanhel Vệ Thần", 27},
    {"Yena Huyền Cửu Thiên", 11},
    {"Violet Nobara Kugisaki", 33},    {"Violet Thứ Nguyên Vệ Thần", 28}, 
    {"Lauriel Thứ Nguyên Vệ Thần", 49},
    {"Iggy Rimuru Tempest", 50},
    {"Qi Milim Nava", 51},
    {"Veres Lưu Ly Long Mẫu", 15},
    {"Veera Phù Thủy Hội Họa", 22},
    {"Tulen Satoru Gojo", 25},
    {"Triệu Vân Thần Tài", 1},
    {"TelAnnas Lâm Quang Thánh Điệu", 31}, {"TelAnnas Thú Nguyên Vệ Thần", 38},
    {"Raz Gon", 10},
    {"Paine Megumi fushiguro", 34},
    {"Ngộ Không Tân Niên Võ Thần", 3},
    {"Nakroth Killua", 9},    {"Nakroth Quỷ Thương Liệp Đế", 16},    {"Nakroth Thứ Nguyên Vệ Thần", 45},    {"Nakroth Bạch Diện Chiến Thương", 20},
    {"Murad Tuyệt Thế Thần Binh", 13},  {"Murad Thiên Luân Kiếm Thánh", 21},
    {"Liliana Ma Pháp Tối Thượng", 23},
    {"Krixi Phù Thuỷ Thời Không", 19},
    {"Ilumia Lưỡng Nghi Long Hậu", 26},
    {"Grakk Thần Ẩm Thực", 14},
    {"Enzo Kurapika", 8},
    {"Eland'orr Tuxedo", 6},    {"Eland'orr  Chuyến Tàu Mơ Ước", 47},
    {"Điêu Thuyền Eternal Sailor Moon", 4},
    {"Capheny Càn Nguyên Điện Chủ", 29},
    {"Butterfly Thánh Nữ Khởi Nguyên", 7}, {"Butterfly EVO5", 32},
    {"Biron Yuji Itadori", 24},
    {"Aya Công Chúa Cầu Vồng", 17},
    {"Allain Lân Sư Vũ Thần", 30},
    {"Elsu Chuyến Tàu Mơ Ước", 46},
    {"Alice Eternal Sailor Chibi Moon", 5},
    {"Airi Thứ Nguyên Vệ Thần", 12}
};



struct SoldierSkinMod {
    const char* name;
    int soldierId;
};

static const SoldierSkinMod ChooseSoldierSkin[] = {
    {"lính thường", 0},
    {"Cinnamon",93003},
    {"Lính Conan", 93001},
    {"Lính Yêu Tinh", 93002}
};