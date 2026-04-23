#include "include.h"
#include <unordered_set>

std::unordered_map<int, std::unordered_set<int>> excludedSkins = {
    {106,  {11, 20}},
    {107,  {9, 14}},
    {109,  {12, 15}},
    {111,  {10, 13, 15, 19, 20}},
    {112,  {15}},
    {116,  {10, 11}},
    {118,  {12, 16}},
    {129,  {12}},
    {130,  {11, 15}},
    {131,  {11, 16, 18}},
    {132,  {10, 13}},
    {136,  {9, 13}},
    {137,  {5, 6}},
    {141,  {11}},
    {142,  {13}},
    {150,  {13, 15}},
    {152,  {12}},
    {154,  {6, 12, 13}},
    {156,  {11}},
    {167,  {7, 10, 11, 12}},
    {174,  {8}},
    {190,  {9}},
    {191,  {9}},
    {199,  {6}},
    {501,  {19}},
    {520,  {11}},
    {524,  {14}},
    {543,  {7, 8}},
    {548,  {4, 5}},
    {598,  {2}},
    {599,  {1}},
};

bool skintranao(int heroID, int skinID) {
    auto it = excludedSkins.find(heroID);
    return it != excludedSkins.end() && it->second.count(skinID);
}

void (*RefreshHeroPanel)(void *instance,bool v1,bool v2,bool v3);
bool (*IsSkinAvailable)(int configID);
bool _IsSkinAvailable(int configID)
{
	if(unlockskin)
	{
		return true;
	}
    unhook_one_point(ModSkin[0]);
    bool result = IsSkinAvailable(configID);
    hook_one_point(ModSkin[0],(void*)_IsSkinAvailable);
    return result;
}
bool (*CanUseSkin)(void *instance,int heroID,int skinID);
bool _CanUseSkin(void *instance,int heroID,int skinID)
{
	if(instance != NULL && unlockskin)
	{
		if(skintranao(heroID,skinID))
		{
			skinid2 = skinID;
			dungao = true;
			EnableSkin = true;
			CspHeroID = heroID;
			if(skinID==1) CspSkinID = 2;
			else CspSkinID = 1;
			if(heroID == 132) CspSkinID = 12;
			else if(heroID == 111 && skinID >= 19 ) CspSkinID = 10;
			else if(heroID == 524) CspSkinID = 10;
		}
		else
		{
			EnableSkin = true;
			CspHeroID = heroID;
			CspSkinID = skinID;
			dungao = false;
		}
		return true;
	}
    unhook_one_point(ModSkin[1]);
    bool result = CanUseSkin(instance,heroID,skinID);
    hook_one_point(ModSkin[1],(void*)_CanUseSkin);
    return result;  
}
int (*GetHeroWearSkinId)(void *instance,int heroID);
int _GetHeroWearSkinId(void *instance,int heroID){
	currentHeroId = heroID;
    int skinid;
	if(unlockskin){
		if(EnableSkin && CspHeroID == heroID)
		{
			if(dungao)
			{
				skinid = skinid2;
			}
			else
			{
				skinid = CspSkinID;
			}
		}
		else
		{
			skinid = protocol._skinID;
		}
	} else {
		skinid = GetHeroWearSkinId(instance,heroID);
	}
    unhook_one_point(ModSkin[2]);
    currentSkinId = skinid;
    hook_one_point(ModSkin[2],(void*)_GetHeroWearSkinId);
    return skinid;
}
int32_t (*old_unpack)(void* instance, void* srcBuf, int32_t cutVer);
bool g_unpack_installed = false;

inline uint32_t getdwHeroID_inline(void* p) {
    return p ? *(uint32_t*)((uintptr_t)p + 0x10) : 0;
}
inline uint16_t getwSkinID_inline(void* p) {
    return p ? *(uint16_t*)((uintptr_t)p + 0x42) : 0;
}
inline void setwSkinID_inline(void* p, uint16_t id) {
    if (p) *(uint16_t*)((uintptr_t)p + 0x42) = id;
}

int32_t unpack_postcall(void* instance, void* srcBuf, int32_t cutVer) {

    unhook_one_point(ModSkin[6]);

    int32_t ret = old_unpack ? old_unpack(instance, srcBuf, cutVer) : 0;

    if (unlockskin && instance && [protocol isEnabled]) {
        const uint32_t heroID = getdwHeroID_inline(instance);
        const uint16_t oldSkin = getwSkinID_inline(instance);

        if (protocol._heroID > 0 && heroID == (uint32_t)protocol._heroID && protocol._skinID > 0) {
            setwSkinID_inline(instance, (uint16_t)protocol._skinID);
        } else if ([protocol checkHeroID:heroID]) {
            int saved = [protocol getHeroSkinID:heroID];
            if (saved > 0) setwSkinID_inline(instance, (uint16_t)saved);
        } else {
            [protocol checkAndUpdateHeroSkin:heroID skinID:oldSkin];
        }
    }

    hook_one_point(ModSkin[6], (void*)unpack_postcall);
    return ret;
}
void *(*GetAwakeSkinData)(uint32_t wakeSkinID);
bool (*_IsAwakeSkin)(uint32_t wakeSkinID);
bool IsAwakeSkin(uint32_t wakeSkinID) {
    void *awakeSkin = GetAwakeSkinData(wakeSkinID);
    if (awakeSkin != nullptr)
    {
      *(uint8_t *)((uintptr_t)awakeSkin + ModSkinOffField[8]) = 5;
      *(uint8_t *)((uintptr_t)awakeSkin + ModSkinOffField[9]) = 5;
      *(uint64_t *)((uintptr_t)awakeSkin + ModSkinOffField[10]) = 2147483647;
    }
    unhook_one_point(ModSkin[8]);
    bool result = _IsAwakeSkin(wakeSkinID);
    hook_one_point(ModSkin[8],(void*)IsAwakeSkin);
    return result;
}

void* (*unpack2)(uintptr_t instance, void **srcBuf, uint32_t cutVer);
void* _unpack2(uintptr_t instance, void **srcBuf, uint32_t cutVer){
    unhook_one_point(ModSkin[10]);
  void* result = unpack2(instance, srcBuf, cutVer);
  if (result) return result;
  *(uint8_t *)((uintptr_t)instance + ModSkinOffField[11]) = 5;
  *(uint64_t *)((uintptr_t)instance + ModSkinOffField[12]) = 2147483647;
    hook_one_point(ModSkin[10], (void*)_unpack2);
  return result;
}


void* (*GetHeroSkin)(int heroID,int skinID);
void* (*GetSkin)(void* instance,int skinID);
void* _GetSkin(void* instance,int skinID)
{
    unhook_one_point(ModSkin[12]);
    
    MonoString* lobbycamera = *(MonoString**)((uintptr_t)instance + 0x48);
    NSString* str = [NSString stringWithUTF8String:lobbycamera->toString().c_str()];
    NSError *error = nil;
    // Tạo regex để tìm Prefab_Characters/Prefab_Hero/(number)_
    NSRegularExpression *regex = [NSRegularExpression regularExpressionWithPattern:@"Prefab_Characters/Prefab_Hero/(\\d+)_"
                                                                        options:0
                                                                            error:&error];
    // Tìm số hero ID trong chuỗi
    NSTextCheckingResult *match = [regex firstMatchInString:str options:0 range:NSMakeRange(0, str.length)];
    if (match && match.numberOfRanges > 1) {
        NSRange range = [match rangeAtIndex:1]; // Lấy giá trị số
        NSString *skinIDStr = [str substringWithRange:range];
        int heroID = skinIDStr.intValue;
        if(heroID == CspHeroID)
        {
            int id= CspSkinID;
            int checkhero = CspSkinID;
            if(dungao)
            {   
                if((heroID == 132) || (heroID == 111 && skinid2 >= 19 ) || (heroID == 524)) checkhero = skinid2;
                skinID = skinid2;
                id = skinid2;
            }
            void* forskin = GetHeroSkin(heroID,checkhero);
            if(forskin)
            {
                *(int*)((uintptr_t)forskin + ModSkinOffField[13]) = heroID*100 + id;
            }
        }
    }
    
    void* result = GetSkin(instance,skinID);
    hook_one_point(ModSkin[12], (void*)_GetSkin);
    return result;
}

bool (*get_IsHostProfile)(void* instance);
bool _get_IsHostProfile(void* instance) {
    if (instance != NULL) {
        return true;  // Giả mạo là profile của mình
    }
    unhook_one_point(offset[11]);
    bool result = get_IsHostProfile(instance);
    hook_one_point(offset[11],(void*)_get_IsHostProfile);
    return result;  // Trả về kết quả thật
}

////


/*void* CBattle_Instance = Il2CppGetSingleton(oxorany("Project_d.dll"),oxorany("Assets.Scripts.GameSystem"),oxorany("CBattleSystem"));
if(CBattle_Instance)
{
    void* CBattleEquipSystem = *(void**)((uint64_t)CBattle_Instance + getFieldOffset(oxorany("Project_d.dll"),oxorany("Assets.Scripts.GameSystem"),oxorany("CBattleSystem"),oxorany("<TheBattleEquipSystem>k__BackingField")));
}

    void* BattleLogic_Instance = Il2CppGetSingleton(oxorany("Project_d.dll"),oxorany("Assets.Scripts.GameLogic"),oxorany("BattleLogic"));
    if(BattleLogic_Instance)
    {
    void* CBattleEquipSystem = *(void**)((uint64_t)CBattle_Instance + getFieldOffset(oxorany("Project_d.dll"),oxorany("Assets.Scripts.GameSystem"),oxorany("CBattleSystem"),oxorany("<TheBattleEquipSystem>k__BackingField")));
        
    }
*/




///
/*void* CBattle_Instance = Il2CppGetSingleton(oxorany("Project_d.dll"),oxorany("Assets.Scripts.GameSystem"),oxorany("CBattleSystem"));
if(CBattle_Instance)
{
    void* CBattleEquipSystem = *(void**)((uint64_t)CBattle_Instance + getFieldOffset(oxorany("Project_d.dll"),oxorany("Assets.Scripts.GameSystem"),oxorany("CBattleSystem"),oxorany("<TheBattleEquipSystem>k__BackingField")));
}*/
///￼/
/*void* (*get_battleLogic)(void* instance);

void* get_battleLogic(void* instance) {
    if (!instance) 
        return nullptr;
    LBattleLogic = get_battleLogic(instance);
    return LBattleLogic;
}*/



/*void* (*CBattleSystem_Update)(void* instance);
void* _CBattleSystem_Update(void* instance){
    if(instance != NULL){
        CBattle_Instance = instance;  
    }
    CBattleSystem_Update(CBattle_Instance);
}
void* (*get_battleLogic)(void* instance);
void* _get_battleLogic(void* instance){
    if(instance != NULL){
        LBattleLogic = get_battleLogic(instance);
        return LBattleLogic;
    }
    return get_battleLogic(instance);
}
*/


void (*OnCameraHeightChanged)(void *instance);

float(*GetZoomRate)(void* instance);
float _GetZoomRate(void* instance)
{ 
    float original = *(float*)((uintptr_t)instance + EspField[21]);
	if (instance != NULL)
	{	
		return original + Camera;
	}
    return original;
}

enum COM_PLAYERCAMP {
    ComPlayercampMid = 0,
    ComPlayercamp1 = 1,
    ComPlayercamp2 = 2,
    ComPlayercamp3 = 3,
    ComPlayercamp4 = 4,
    ComPlayercamp5 = 5,
    ComPlayercamp6 = 6,
    ComPlayercamp7 = 7,
    ComPlayercamp8 = 8,
    ComPlayercampCount = 9,
    ComPlayercampOb = 10,
    ComPlayercampInvalid = 254,
    ComPlayercampAll = 255
};

bool (*SetVisible)(void *instance, COM_PLAYERCAMP camp, bool bVisible, bool forceSync);

bool _SetVisible(void *instance, COM_PLAYERCAMP camp, bool bVisible, bool forceSync) {
    if (instance && hackmapenable) {
        bVisible = true;
        forceSync = true;  // Force sync để cập nhật ngay
    }
    
    // Gọi function gốc với tham số đã modify
    unhook_one_point(offset[0]);
    bool result = SetVisible(instance, camp, bVisible, forceSync);
    hook_one_point(offset[0], (void*)_SetVisible);
    
    return result;
}

Vector3 (*GetUseSkillDirection)(void* instance,bool isUseSkill);
Vector3 _GetUseSkillDirection(void* instance,bool isUseSkill)
{
    if(instance != NULL && AimbotEnable)
    {
        void* SkillSlot = *(void**)((uintptr_t)instance + EspField[17]);
        if(SkillSlot != NULL)
        {
            int SkillSlotType = *(int*)((uintptr_t)SkillSlot + EspField[18]);
            if(SkillSlotType == 1)
            {
                if (EnemyTarget1.bullettime > 0.0f && EnemyTarget1.myPos != Vector3::zero() && EnemyTarget1.enemyPos != Vector3::zero() && (!MANUALAIM || (MANUALAIM && enableSkill1))) {
                    return calculateSkillDirection(EnemyTarget1.myPos,EnemyTarget1.enemyPos,EnemyTarget1.moveForward,EnemyTarget1.currentSpeed,EnemyTarget1.bullettime,EnemyTarget1.Ranger);
                }
            }
            else if(SkillSlotType == 2)
            {
                if (EnemyTarget2.bullettime > 0.0f && EnemyTarget2.myPos != Vector3::zero() && EnemyTarget2.enemyPos != Vector3::zero() && (!MANUALAIM || (MANUALAIM && enableSkill2))) {
                    return calculateSkillDirection(EnemyTarget2.myPos,EnemyTarget2.enemyPos,EnemyTarget2.moveForward,EnemyTarget2.currentSpeed,EnemyTarget2.bullettime,EnemyTarget2.Ranger);
                }
            }
            else if(SkillSlotType == 3)
            {
                if (EnemyTarget3.bullettime > 0.0f && EnemyTarget3.myPos != Vector3::zero() && EnemyTarget3.enemyPos != Vector3::zero() && (!MANUALAIM || (MANUALAIM && enableSkill3))) {
                    return calculateSkillDirection(EnemyTarget3.myPos,EnemyTarget3.enemyPos,EnemyTarget3.moveForward,EnemyTarget3.currentSpeed,EnemyTarget3.bullettime,EnemyTarget3.Ranger);
                }
            }
        }
    }
    return *(Vector3*) ((uintptr_t)instance + ActorLinkerOffField[9]);
}
Vector3 (*GetUseSkillPosition)(void* instance,bool isUseSkill);
Vector3 _GetUseSkillPosition(void* instance,bool isUseSkill)
{
    if(instance != NULL && AimbotEnable)
    {
        void* SkillSlot = *(void**)((uintptr_t)instance + EspField[17]);
        if(SkillSlot != NULL)
        {
            int SkillSlotType = *(int*)((uintptr_t)SkillSlot + EspField[18]);
            if(SkillSlotType == 1)
            {
                if (EnemyTarget1.bullettime > 0.0f && EnemyTarget1.myPos != Vector3::zero() && EnemyTarget1.enemyPos != Vector3::zero() && (!MANUALAIM || (MANUALAIM && enableSkill1))) {
                    return calculateSkillPosition(EnemyTarget1.myPos,EnemyTarget1.enemyPos,EnemyTarget1.moveForward,EnemyTarget1.currentSpeed,EnemyTarget1.bullettime,EnemyTarget1.Ranger);
                }
            }
            else if(SkillSlotType == 2)
            {
                if (EnemyTarget2.bullettime > 0.0f && EnemyTarget2.myPos != Vector3::zero() && EnemyTarget2.enemyPos != Vector3::zero() && (!MANUALAIM || (MANUALAIM && enableSkill2))) {
                    return calculateSkillPosition(EnemyTarget2.myPos,EnemyTarget2.enemyPos,EnemyTarget2.moveForward,EnemyTarget2.currentSpeed,EnemyTarget2.bullettime,EnemyTarget2.Ranger);
                }
            }
            else if(SkillSlotType == 3)
            {
                if (EnemyTarget3.bullettime > 0.0f && EnemyTarget3.myPos != Vector3::zero() && EnemyTarget3.enemyPos != Vector3::zero() && (!MANUALAIM || (MANUALAIM && enableSkill3))) {
                    return calculateSkillPosition(EnemyTarget3.myPos,EnemyTarget3.enemyPos,EnemyTarget3.moveForward,EnemyTarget3.currentSpeed,EnemyTarget3.bullettime,EnemyTarget3.Ranger);
                }
            }
        }
    }
    return *(Vector3*) ((uintptr_t)instance + ActorLinkerOffField[10]);
}




void InitRandomSeed()
{
    srand((unsigned int)time(NULL)); 
}

uint32_t RandomPlayerId()
{
    return 10000 + (rand() % 900000);
}

unsigned long long RandomPlayerUid()
{
    return 100000000000000 + (rand() % 900000000000000); 
}
bool goi = false;
void* (*CreateReportData)(void *instance, uint playerId, unsigned long long playerUid, bool bGMWin, bool bWin, bool isMultiGame);
void* _CreateReportData(void *instance, uint playerId, unsigned long long playerUid, bool bGMWin, bool bWin, bool isMultiGame)
{
    if (instance != NULL && HackSao && bWin == false) {
        bGMWin = true;
        bWin = true;
        isMultiGame = false;;
        playerId = RandomPlayerId();
        playerUid = RandomPlayerUid();
        goi = true;
    }
    unhook_one_point(Antiban[4]);
    void* result = CreateReportData(instance, playerId, playerUid, bGMWin, bWin, isMultiGame);
    hook_one_point(Antiban[4],(void*)_CreateReportData);
    return result;
}

void (*CreateDestroyReportData)(void *instance, uint playerId, void *commonData, bool bGMWin);
void _CreateDestroyReportData(void *instance, uint playerId, void *commonData, bool bGMWin)
{
    if (instance != NULL && HackSao && goi) { 
        bGMWin = true;
        playerId = RandomPlayerId();
    }
    unhook_one_point(Antiban[5]);
    CreateDestroyReportData(instance, playerId, commonData, bGMWin);
    hook_one_point(Antiban[5],(void*)_CreateDestroyReportData);
}
void (*HandleGameSettle)(void* instance,bool bSuccess, bool bShouldDisplayWinLose, Byte GameResult,void* svrData);
void _HandleGameSettle(void* instance,bool bSuccess, bool bShouldDisplayWinLose, Byte GameResult, void* svrData)
{
    if (HackSao && instance) { 
        if(GameResult == 1)
        {
            bSuccess = false;
            bShouldDisplayWinLose = false;
            GameResult = (Byte)1;
            svrData = NULL; 
        }
    }
    unhook_one_point(Antiban[6]);
    HandleGameSettle(instance,bSuccess, bShouldDisplayWinLose, GameResult, svrData);
    hook_one_point(Antiban[6],(void*)_HandleGameSettle);
}


void hook_no_org()
{ 
    hook_reset(
    (void *[]) {
        // (void *)((uintptr_t)ModSkin[0]),
        (void *)((uintptr_t)ModSkin[1]),
        (void *)((uintptr_t)ModSkin[2]),
        (void *)((uintptr_t)ModSkin[6]),
        (void *)((uintptr_t)ModSkin[8]),
        (void *)((uintptr_t)ModSkin[10]),
        (void *)((uintptr_t)ModSkin[12])
    },
    (void *[]) {
        // (void *)_IsHaveHeroSkin,
        (void *)_CanUseSkin,
        (void *)_GetHeroWearSkinId,
        (void *)unpack_postcall,
        (void *)IsAwakeSkin,
        (void *)_unpack2,
        (void *)_GetSkin
        },
    6);
    isHookedSkin = true;
}
void un_hook_no_org()
{
    unhook(
    (void *[]) {
        (void *)((uintptr_t)ModSkin[1]),
        (void *)((uintptr_t)ModSkin[2]),
        (void *)((uintptr_t)ModSkin[6]),
        (void *)((uintptr_t)ModSkin[8]),
        (void *)((uintptr_t)ModSkin[10]),
        (void *)((uintptr_t)ModSkin[12])
    },
    6);
    isHookedSkin = false;
}


