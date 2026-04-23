#include "ESP.h"

// Wrapper macros: FindMethodOffsetN returns RVA, add Moudule_Base for absolute address
#define FIND_METHOD(dll, ns, cls, method, args) \
    (void*) Unity::FindMethodOffsetN(dll, ns, cls, method, args)

#define FIND_FIELD(dll, ns, cls, field) \
    Unity::FindFieldOffset(dll, ns, cls, field)

void CheatHandle()
{
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
    offset[1] = FIND_METHOD(OBFUSCATE("Project.Plugins_d.dll"),OBFUSCATE("NucleusDrive.Logic"),OBFUSCATE("LVActorLinker"),OBFUSCATE("ForceSetVisible"), 1);
    offset[2] = FIND_METHOD(OBFUSCATE("Project.Plugins_d.dll"),OBFUSCATE("NucleusDrive.Logic"),OBFUSCATE("LVActorLinker"),OBFUSCATE("SyncActiveView"), 0);
    offset[3] = FIND_METHOD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameSystem"),OBFUSCATE("CLobbySystem"),OBFUSCATE("OpenWaterMark"), 0);
    
    offset[4] = FIND_METHOD(OBFUSCATE("Project_d.dll"),OBFUSCATE(""),OBFUSCATE("CameraSystem"),OBFUSCATE("GetZoomRate"), 0);
    offset[5] = FIND_METHOD(OBFUSCATE("Project_d.dll"),OBFUSCATE(""),OBFUSCATE("CameraSystem"),OBFUSCATE("update"), 0);
    offset[6] = FIND_METHOD(OBFUSCATE("Project_d.dll"),OBFUSCATE(""),OBFUSCATE("CameraSystem"),OBFUSCATE("OnCameraHeightChanged"), 0);

    offset[7] = FIND_METHOD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameSystem"),OBFUSCATE("HeroInfoPanel"),OBFUSCATE("ShowHeroInfo"), 2);
    offset[8] = FIND_METHOD(OBFUSCATE("Project_d.dll"),OBFUSCATE(""),OBFUSCATE("MiniMapHeroInfo"),OBFUSCATE("ShowHeroHpInfo"), 1);
    offset[9] = FIND_METHOD(OBFUSCATE("Project_d.dll"),OBFUSCATE(""),OBFUSCATE("MiniMapHeroInfo"),OBFUSCATE("ShowSkillStateInfo"), 1);
    offset[10] = FIND_METHOD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameSystem"),OBFUSCATE("HeroSelectBanPickWindow"),OBFUSCATE("InitTeamHeroList"), 4);
    offset[11] = FIND_METHOD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameSystem"),OBFUSCATE("CPlayerProfile"),OBFUSCATE("get_IsHostProfile"), 0);
    offset[12] = FIND_METHOD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameSystem"),OBFUSCATE("PVPLoadingView"),OBFUSCATE("checkTeamLaderGradeMax"), 1);
    offset[13] = FIND_METHOD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameSystem"),OBFUSCATE("PVPLoadingView"),OBFUSCATE("OnEnter"), 0);
    offset[14] = FIND_METHOD(OBFUSCATE("mscorlib.dll"),OBFUSCATE("System"),OBFUSCATE("String"),OBFUSCATE("CreateString"), 3);
    offset[15] = FIND_METHOD(OBFUSCATE("Project_d.dll"),OBFUSCATE("PhoneNotify"),OBFUSCATE("PhoneNotifySystem"),OBFUSCATE("_OnGameEnd"), 0);
    offset[16] = FIND_METHOD(OBFUSCATE("Project_d.dll"),OBFUSCATE("PhoneNotify"),OBFUSCATE("PhoneNotifySystem"),OBFUSCATE("_OnGameStart"), 0);
    offset[17] = FIND_METHOD(OBFUSCATE("Project.Plugins_d.dll"),OBFUSCATE("NucleusDrive.Logic"), OBFUSCATE("LFrameSyncBattleLogic"),OBFUSCATE("SendSyncData"), 2);
    offset[18] = FIND_METHOD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.UI"), OBFUSCATE("CUIUtility"),OBFUSCATE("RemovEspace"), 1);
    offset[19] = FIND_METHOD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameSystem"), OBFUSCATE("CRoleInfo"),OBFUSCATE("IsNewbieFirstOperateBitSet"), 1);
    offset[20] = FIND_METHOD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameSystem"), OBFUSCATE("InBattleMsgNetCore"),OBFUSCATE("SendInBattleMsg_InputChat"), 2);


    Esp[0]  = FIND_METHOD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Kyrios"),OBFUSCATE("KyriosFramework"),OBFUSCATE("get_actorManager"), 0);
    Esp[1]  = FIND_METHOD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameSystem"),OBFUSCATE("CBattleSystem"),OBFUSCATE("get_TheMinimapSys"), 0);
    Esp[2]  = FIND_METHOD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameSystem"),OBFUSCATE("CBattleSystem"),OBFUSCATE("CvtWorld2UISM"), 1);
    Esp[3]  = FIND_METHOD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameSystem"),OBFUSCATE("CBattleSystem"),OBFUSCATE("CvtWorld2UIBM"), 1);
    Esp[4] = FIND_METHOD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameSystem"),OBFUSCATE("CBattleSystem"),OBFUSCATE("GetHero_Icon"), 2);
    Esp[5] = FIND_METHOD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Kyrios"),OBFUSCATE("KyriosFramework"),OBFUSCATE("get_playerCenter"), 0);
    Esp[6] = FIND_METHOD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Kyrios"),OBFUSCATE("KyriosFramework"),OBFUSCATE("get_hostLogic"), 0);
    Esp[7] = FIND_METHOD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameLogic"),OBFUSCATE("BattleLogic"),OBFUSCATE("GetCurLvelContext"), 0);
    Esp[8] = FIND_METHOD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameLogic"),OBFUSCATE("SLevelContext"),OBFUSCATE("GetGameRoomType"), 0);
    Esp[9] = FIND_METHOD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameLogic"),OBFUSCATE("SkillSlot"),OBFUSCATE("RequestUseSkill"), 0);
    Esp[10] = FIND_METHOD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameLogic"),OBFUSCATE("SkillSlot"),OBFUSCATE("ReadyUseSkill"), 1);
    Esp[11] = FIND_METHOD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameLogic"),OBFUSCATE("SkillSlot"),OBFUSCATE("get_IsCharging"), 0);
    Esp[12]  = FIND_METHOD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameSystem"),OBFUSCATE("CBattleSystem"),OBFUSCATE("get_FightForm"), 0);
    Esp[13] = FIND_METHOD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameSystem"),OBFUSCATE("CSkillButtonManager"),OBFUSCATE("CanRequestSkill"), 1);
    Esp[14] = FIND_METHOD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameSystem"),OBFUSCATE("CSkillButtonManager"),OBFUSCATE("RequestUseSkillSlot"), 4);
    Esp[15] = FIND_METHOD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameLogic"),OBFUSCATE("HudComponent3D"),OBFUSCATE("SetPlayerName"), 4);
    Esp[16] = FIND_METHOD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameSystem"),OBFUSCATE("CHeroSelectBaseSystem"),OBFUSCATE("GetSelfCamp"), 0);
    Esp[17] = FIND_METHOD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameSystem"),OBFUSCATE("CHeroSelectBaseSystem"),OBFUSCATE("GetTeamHeroCommonInfoList"), 1);
    Esp[18] = FIND_METHOD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameLogic"),OBFUSCATE("LobbyMsgHandler"),OBFUSCATE("ForceKillCrystal"),1);
    Esp[19] = FIND_METHOD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameSystem"),OBFUSCATE("CRoleInfoManager"),OBFUSCATE("GetMasterRoleInfo"), 0);
    Esp[20] = FIND_METHOD(OBFUSCATE("UnityEngine.CoreModule.dll"),OBFUSCATE("UnityEngine"),OBFUSCATE("Object"),OBFUSCATE("FindObjectOfType"), 1);
    Esp[21] = FIND_METHOD(OBFUSCATE("mscorlib.dll"),OBFUSCATE("System"),OBFUSCATE("Type"),OBFUSCATE("GetType"), 1);
    Esp[22] = FIND_METHOD(OBFUSCATE("UnityEngine.CoreModule.dll"),OBFUSCATE("UnityEngine"),OBFUSCATE("Object"),OBFUSCATE("FindObjectsOfType"), 1);
    Esp[23] = FIND_METHOD(OBFUSCATE("mscorlib.dll"),OBFUSCATE("System"),OBFUSCATE("Type"),OBFUSCATE("ToString"), 0);
    Esp[24] = FIND_METHOD(OBFUSCATE("UnityEngine.CoreModule.dll"),OBFUSCATE("UnityEngine"),OBFUSCATE("Resources"),OBFUSCATE("FindObjectsOfTypeAll"), 1);
    Esp[25] = FIND_METHOD(OBFUSCATE("mscorlib.dll"),OBFUSCATE("System.Reflection"),OBFUSCATE("Assembly"),OBFUSCATE("Load"), 1);
    Esp[26] = FIND_METHOD(OBFUSCATE("mscorlib.dll"),OBFUSCATE("System.Reflection"),OBFUSCATE("Assembly"),OBFUSCATE("GetType"), 1);
    Esp[27] = FIND_METHOD(OBFUSCATE("UnityEngine.CoreModule.dll"),OBFUSCATE("UnityEngine"),OBFUSCATE("Object"),OBFUSCATE("GetName"), 1);
    Esp[28] = FIND_METHOD(OBFUSCATE("UnityEngine.CoreModule.dll"),OBFUSCATE("UnityEngine"),OBFUSCATE("GameObject"),OBFUSCATE("get_activeInHierarchy"), 0);
    Esp[29] = FIND_METHOD(OBFUSCATE("UnityEngine.CoreModule.dll"),OBFUSCATE("UnityEngine"),OBFUSCATE("GameObject"),OBFUSCATE("GetComponentsInternal"), 6);
    Esp[30] = FIND_METHOD(OBFUSCATE("UnityEngine.CoreModule.dll"),OBFUSCATE("UnityEngine"),OBFUSCATE("GameObject"),OBFUSCATE("GetComponent"), 1);
    Esp[31] = FIND_METHOD(OBFUSCATE("UnityEngine.CoreModule.dll"),OBFUSCATE("UnityEngine"),OBFUSCATE("GameObject"),OBFUSCATE("GetComponentInChildren"), 1);
    Esp[32] = FIND_METHOD(OBFUSCATE("UnityEngine.CoreModule.dll"),OBFUSCATE("UnityEngine"),OBFUSCATE("GameObject"),OBFUSCATE("GetComponentInParent"), 1);
    Esp[33] = FIND_METHOD(OBFUSCATE("UnityEngine.CoreModule.dll"),OBFUSCATE("UnityEngine"),OBFUSCATE("Object"),OBFUSCATE("GetOffsetOfInstanceIDInCPlusPlusObject"), 0);
    Esp[34] = FIND_METHOD(OBFUSCATE("Project.Plugins_d.dll"),OBFUSCATE(""),OBFUSCATE("Text2"),OBFUSCATE("get_text"), 0);
    Esp[35] = FIND_METHOD(OBFUSCATE("UnityEngine.CoreModule.dll"),OBFUSCATE("UnityEngine"),OBFUSCATE("Object"),OBFUSCATE("GetInstanceID"), 0);
    Esp[36] = FIND_METHOD(OBFUSCATE("UnityEngine.CoreModule.dll"),OBFUSCATE("UnityEngine"),OBFUSCATE("Camera"),OBFUSCATE("get_cameraToWorldMatrix"), 0); 
    Esp[37] = FIND_METHOD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameLogic"),OBFUSCATE("SkillControlIndicator"),OBFUSCATE("GetUseSkillPosition"),1);
    Esp[38] = FIND_METHOD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameLogic"),OBFUSCATE("SkillControlIndicator"),OBFUSCATE("GetUseSkillDirection"),1);
    Esp[39] = FIND_METHOD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameLogic"),OBFUSCATE("BuffSkill"),OBFUSCATE("get_SkillID"),0);
    Esp[40] = FIND_METHOD(OBFUSCATE("Project.Plugins_d.dll"),OBFUSCATE("NucleusDrive.Logic.Battle.CommunicateSignal"),OBFUSCATE("CommunicateAgent"),OBFUSCATE("GetGameTime"),0);
    Esp[41] = FIND_METHOD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameLogic"),OBFUSCATE("GameInput"),OBFUSCATE("CalcDirectionByTouchPosition"),2);
    
    EspField[0] = FIND_FIELD(OBFUSCATE("Project.Plugins_d.dll"),OBFUSCATE("NucleusDrive.Logic.GameKernal"),OBFUSCATE("GamePlayerCenter"),OBFUSCATE("_players"));
    EspField[1] = FIND_FIELD(OBFUSCATE("Project.Plugins_d.dll"),OBFUSCATE("LDataProvider"),OBFUSCATE("PlayerBase"),OBFUSCATE("PlayerId"));
    EspField[2] = FIND_FIELD(OBFUSCATE("Project.Plugins_d.dll"),OBFUSCATE("LDataProvider"),OBFUSCATE("PlayerBase"),OBFUSCATE("broadcastID"));
    EspField[3] = FIND_FIELD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Kyrios.Actor"),OBFUSCATE("ActorManager"),OBFUSCATE("HeroActors"));
    EspField[4] = FIND_FIELD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Kyrios.Actor"),OBFUSCATE("ActorManager"),OBFUSCATE("OrganActors"));
    EspField[5] = FIND_FIELD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Kyrios.Actor"),OBFUSCATE("ActorManager"),OBFUSCATE("TowerActors"));
    EspField[6] = FIND_FIELD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Kyrios.Actor"),OBFUSCATE("ActorManager"),OBFUSCATE("MonsterActors"));
    EspField[7] = FIND_FIELD(OBFUSCATE("Project.Plugins_d.dll"),OBFUSCATE("NucleusDrive.Logic"),OBFUSCATE("LLogicCore"),OBFUSCATE("instances"));
    EspField[8] = FIND_FIELD(OBFUSCATE("Project.Plugins_d.dll"),OBFUSCATE("NucleusDrive.Logic"),OBFUSCATE("LDeskBase"),OBFUSCATE("<DeskBattleLogic>k__BackingField"));
    EspField[9] = FIND_FIELD(OBFUSCATE("Project.Plugins_d.dll"),OBFUSCATE("NucleusDrive.Logic"),OBFUSCATE("LBattleLogic"),OBFUSCATE("<gameActorMgr>k__BackingField"));
    EspField[10] = FIND_FIELD(OBFUSCATE("Project.Plugins_d.dll"),OBFUSCATE("NucleusDrive.Logic"),OBFUSCATE("LGameActorMgr"),OBFUSCATE("HeroActors"));
    EspField[11] = FIND_FIELD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameSystem"),OBFUSCATE("FightForm"),OBFUSCATE("<m_skillButtonManager>k__BackingField"));
    EspField[12] = FIND_FIELD(OBFUSCATE("Project.Plugins_d.dll"),OBFUSCATE("LDataProvider"),OBFUSCATE("PlayerBase"),OBFUSCATE("Name"));
    EspField[13] = FIND_FIELD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Kyrios"),OBFUSCATE("VHostLogic"),OBFUSCATE("<HostPlayerId>k__BackingField"));
    EspField[15]  = FIND_FIELD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameSystem"),OBFUSCATE("CBattleSystem"),OBFUSCATE("m_isInBattle"));
    EspField[16]  = FIND_FIELD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameSystem"),OBFUSCATE("CSkillButtonManager"),OBFUSCATE("m_currentSkillSlotType"));
    EspField[17]  = FIND_FIELD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameLogic"),OBFUSCATE("SkillControlIndicator"),OBFUSCATE("skillSlot"));
    EspField[18]  = FIND_FIELD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameLogic"),OBFUSCATE("SkillSlot"),OBFUSCATE("SlotType"));
    EspField[19] = FIND_FIELD(OBFUSCATE("Project.Plugins_d.dll"),OBFUSCATE("NucleusDrive.Logic"),OBFUSCATE("LGameActorMgr"),OBFUSCATE("MonsterActors"));
	EspField[20] = FIND_FIELD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Kyrios.Actor"),OBFUSCATE("ActorLinker"),OBFUSCATE("isMoving"));
	EspField[21] = FIND_FIELD(OBFUSCATE("Project_d.dll"),OBFUSCATE(""),OBFUSCATE("CameraSystem"),OBFUSCATE("zoomRateFromAge"));
    EspField[22]  = FIND_FIELD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameSystem"),OBFUSCATE("CBattleSystem"),OBFUSCATE("<TheBattleEquipSystem>k__BackingField"));
    EspField[23] = FIND_FIELD(OBFUSCATE("Project.Plugins_d.dll"),OBFUSCATE("NucleusDrive.Logic"),OBFUSCATE("LLogicCore"),OBFUSCATE("nFrameTimeMS"));

    ActorLinkerOff[0] = FIND_METHOD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Kyrios.Actor"),OBFUSCATE("ActorLinker"),OBFUSCATE("IsHostPlayer"),0);
    ActorLinkerOff[1] = FIND_METHOD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Kyrios.Actor"),OBFUSCATE("ActorLinker"),OBFUSCATE("IsHostCamp"),0);
    ActorLinkerOff[2] = FIND_METHOD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Kyrios.Actor"),OBFUSCATE("ActorLinker"),OBFUSCATE("get_objType"),0);
    ActorLinkerOff[3] = FIND_METHOD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Kyrios.Actor"),OBFUSCATE("ActorLinker"),OBFUSCATE("get_objCamp"),0);
    ActorLinkerOff[4] = FIND_METHOD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Kyrios.Actor"),OBFUSCATE("ActorLinker"),OBFUSCATE("get_position"),0);
    ActorLinkerOff[5] = FIND_METHOD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Kyrios.Actor"),OBFUSCATE("ActorLinker"),OBFUSCATE("get_HPBarVisible"),0);
    ActorLinkerOff[6] = FIND_METHOD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Kyrios.Actor"),OBFUSCATE("ActorLinker"),OBFUSCATE("get_ObjID"),0);
    ActorLinkerOff[7] = FIND_METHOD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Kyrios.Actor"),OBFUSCATE("ActorLinker"),OBFUSCATE("get_bVisible"),0);
    ActorLinkerOff[8] = FIND_METHOD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Kyrios.Actor"),OBFUSCATE("ActorLinker"),OBFUSCATE("AsHero"),0);
    ActorLinkerOff[9] = FIND_METHOD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Kyrios.Actor"),OBFUSCATE("ActorLinker"),OBFUSCATE("get_playerId"),0);
    ActorLinkerOff[10] = FIND_METHOD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameLogic"),OBFUSCATE("HudComponent3D"),OBFUSCATE("get_ValueCompChangeActor"), 0);
    ActorLinkerOff[11] = FIND_METHOD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Kyrios.Actor"),OBFUSCATE("ValueLinkerComponent"),OBFUSCATE("get_actorHp"),0);
    ActorLinkerOff[12] = FIND_METHOD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Kyrios.Actor"),OBFUSCATE("ValueLinkerComponent"),OBFUSCATE("get_actorHpTotal"),0);
    ActorLinkerOff[13] = FIND_METHOD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Kyrios.Actor"),OBFUSCATE("ValueLinkerComponent"),OBFUSCATE("get_actorSoulLevel"),0);
    
    ActorLinkerOffField[0] = FIND_FIELD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Kyrios.Actor"),OBFUSCATE("ActorLinker"),OBFUSCATE("ValueComponent"));
    ActorLinkerOffField[1] = FIND_FIELD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Kyrios.Actor"),OBFUSCATE("ActorLinker"),OBFUSCATE("HudControl"));
    ActorLinkerOffField[2] = FIND_FIELD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Kyrios.Actor"),OBFUSCATE("ActorLinker"),OBFUSCATE("CharInfo"));
    ActorLinkerOffField[3] = FIND_FIELD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Kyrios.Actor"),OBFUSCATE("ActorLinker"),OBFUSCATE("ObjLinker"));
    ActorLinkerOffField[4] = FIND_FIELD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Kyrios.Actor"),OBFUSCATE("ActorLinker"),OBFUSCATE("EquipLinkerComp"));
    ActorLinkerOffField[5] = FIND_FIELD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Kyrios.Actor"),OBFUSCATE("ActorLinker"),OBFUSCATE("SkillControl"));
    ActorLinkerOffField[6] = FIND_FIELD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameLogic"),OBFUSCATE("SkillComponent"),OBFUSCATE("SkillSlotArray"));
    ActorLinkerOffField[7] = FIND_FIELD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameLogic"),OBFUSCATE("SkillSlot"),OBFUSCATE("skillIndicator"));
    ActorLinkerOffField[8] = FIND_FIELD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameLogic"),OBFUSCATE("SkillControlIndicator"),OBFUSCATE("curindicatorDistance"));
    ActorLinkerOffField[9] = FIND_FIELD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameLogic"),OBFUSCATE("SkillControlIndicator"),OBFUSCATE("useSkillDirection"));
    ActorLinkerOffField[10] = FIND_FIELD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameLogic"),OBFUSCATE("SkillControlIndicator"),OBFUSCATE("useSkillPosition"));
    ActorLinkerOffField[11] = FIND_FIELD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameLogic"),OBFUSCATE("ActorConfig"),OBFUSCATE("ConfigID"));
    ActorLinkerOffField[12] = FIND_FIELD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Kyrios.Actor"),OBFUSCATE("HeroWrapperData"),OBFUSCATE("heroWrapSkillData_1"));
    ActorLinkerOffField[13] = FIND_FIELD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Kyrios.Actor"),OBFUSCATE("HeroWrapperData"),OBFUSCATE("heroWrapSkillData_2"));
    ActorLinkerOffField[14] = FIND_FIELD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Kyrios.Actor"),OBFUSCATE("HeroWrapperData"),OBFUSCATE("heroWrapSkillData_3"));
    ActorLinkerOffField[15] = FIND_FIELD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Kyrios.Actor"),OBFUSCATE("HeroWrapperData"),OBFUSCATE("heroWrapSkillData_5"));
    ActorLinkerOffField[16] = FIND_FIELD(OBFUSCATE("Project.Plugins_d.dll"),OBFUSCATE("NucleusDrive.Share"),OBFUSCATE("HeroWrapSkillData"),OBFUSCATE("Skill1SlotCD"));
    ActorLinkerOffField[17] = FIND_FIELD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Kyrios.Actor"),OBFUSCATE("ActorLinker"),OBFUSCATE("BuffControl"));
    ActorLinkerOffField[18] = FIND_FIELD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameLogic"),OBFUSCATE("BuffLinkerComponent"),OBFUSCATE("SpawnedBuffList"));
    ActorLinkerOffField[19] = FIND_FIELD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameLogic"),OBFUSCATE("SkillComponent"),OBFUSCATE("curSkilSlot"));
    ActorLinkerOffField[20] = FIND_FIELD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameLogic"),OBFUSCATE("SkillControlIndicator"),OBFUSCATE("useOffsetPosition"));
    ActorLinkerOffField[21] = FIND_FIELD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameLogic"),OBFUSCATE("SkillControlIndicator"),OBFUSCATE("useSkillPosition"));
    ActorLinkerOffField[22] = FIND_FIELD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameLogic"),OBFUSCATE("SkillControlIndicator"),OBFUSCATE("curSkillCfg"));
    ActorLinkerOffField[23] = FIND_FIELD(OBFUSCATE("AovTdr.dll"),OBFUSCATE("ResData"),OBFUSCATE("ResSkillCfgInfo"),OBFUSCATE("iGuideDistance"));
    ActorLinkerOffField[24] = FIND_FIELD(OBFUSCATE("AovTdr.dll"),OBFUSCATE("ResData"),OBFUSCATE("ResSkillCfgInfo"),OBFUSCATE("iFixedDistance"));
    ActorLinkerOffField[25] = FIND_FIELD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameLogic"),OBFUSCATE("Skill"),OBFUSCATE("cfgData"));
    


    LActorRootOff[0] = FIND_METHOD(OBFUSCATE("Project.Plugins_d.dll"),OBFUSCATE("NucleusDrive.Logic"),OBFUSCATE("LActorRoot"),OBFUSCATE("get_forward"),0);
    LActorRootOff[1] = FIND_METHOD(OBFUSCATE("Project.Plugins_d.dll"),OBFUSCATE("NucleusDrive.Logic"),OBFUSCATE("LActorRoot"),OBFUSCATE("get_location"),0);
    LActorRootOff[2] = FIND_METHOD(OBFUSCATE("Project.Plugins_d.dll"),OBFUSCATE("NucleusDrive.Logic"),OBFUSCATE("LActorRoot"),OBFUSCATE("AsHero"),0);
    LActorRootOff[3] = FIND_METHOD(OBFUSCATE("Project.Plugins_d.dll"),OBFUSCATE("NucleusDrive.Logic"),OBFUSCATE("LActorRoot"),OBFUSCATE("GiveMyEnemyCamp"),0);
    LActorRootOff[4] = FIND_METHOD(OBFUSCATE("Project.Plugins_d.dll"),OBFUSCATE("NucleusDrive.Logic"),OBFUSCATE("LActorRoot"),OBFUSCATE("get_bActive"),0);
    LActorRootOff[5] = FIND_METHOD(OBFUSCATE("Project.Plugins_d.dll"),OBFUSCATE("NucleusDrive.Logic"),OBFUSCATE("LActorRoot"),OBFUSCATE("get_ObjID"),0);
    LActorRootOff[6] = FIND_METHOD(OBFUSCATE("Project.Plugins_d.dll"),OBFUSCATE("NucleusDrive.Logic"),OBFUSCATE("LObjWrapper"),OBFUSCATE("get_IsDeadState"),0);
    LActorRootOff[7] = FIND_METHOD(OBFUSCATE("Project.Plugins_d.dll"),OBFUSCATE("NucleusDrive.Logic"),OBFUSCATE("LObjWrapper"),OBFUSCATE("IsAutoAI"),0);
    LActorRootOff[8] = FIND_METHOD(OBFUSCATE("Project.Plugins_d.dll"),OBFUSCATE("NucleusDrive.Logic"),OBFUSCATE("ValuePropertyComponent"),OBFUSCATE("get_actorHp"),0);
    LActorRootOff[9] = FIND_METHOD(OBFUSCATE("Project.Plugins_d.dll"),OBFUSCATE("NucleusDrive.Logic"),OBFUSCATE("ValuePropertyComponent"),OBFUSCATE("get_actorHpTotal"),0);
    LActorRootOff[10] = FIND_METHOD(OBFUSCATE("Project.Plugins_d.dll"),OBFUSCATE("NucleusDrive.Logic"),OBFUSCATE("LActorRoot"),OBFUSCATE("get_PlayerMovement"),0);
    LActorRootOff[11] = FIND_METHOD(OBFUSCATE("Project.Plugins_d.dll"),OBFUSCATE("NucleusDrive.Logic"),OBFUSCATE("LEquipComponent"),OBFUSCATE("BuyEquip"),3);
    LActorRootOff[12] = FIND_METHOD(OBFUSCATE("Project.Plugins_d.dll"),OBFUSCATE("NucleusDrive.Logic"),OBFUSCATE("LEquipComponent"),OBFUSCATE("SellEquip"),1);
    LActorRootOff[13] = FIND_METHOD(OBFUSCATE("Project.Plugins_d.dll"),OBFUSCATE("NucleusDrive.Logic"),OBFUSCATE("LEquipComponent"),OBFUSCATE("GetEquips"),0);
    LActorRootOff[14] = FIND_METHOD(OBFUSCATE("Project.Plugins_d.dll"),OBFUSCATE("NucleusDrive.Logic"),OBFUSCATE("ValuePropertyComponent"),OBFUSCATE("get_actorSoulLevel"), 0);
    LActorRootOff[15] = FIND_METHOD(OBFUSCATE("Project.Plugins_d.dll"),OBFUSCATE("NucleusDrive.Logic"),OBFUSCATE("ValuePropertyComponent"),OBFUSCATE("get_actorEp"), 0);
    LActorRootOff[16] = FIND_METHOD(OBFUSCATE("Project.Plugins_d.dll"),OBFUSCATE("NucleusDrive.Logic"),OBFUSCATE("ValuePropertyComponent"),OBFUSCATE("get_actorEpTotal"), 0);
    LActorRootOff[17] = FIND_METHOD(OBFUSCATE("Project.Plugins_d.dll"),OBFUSCATE("NucleusDrive.Logic"),OBFUSCATE("LSkillComponent"),OBFUSCATE("GetSkillSlot"), 1);
    LActorRootOff[18] = FIND_METHOD(OBFUSCATE("Project.Plugins_d.dll"),OBFUSCATE("NucleusDrive.Logic"),OBFUSCATE("SkillSlot"),OBFUSCATE("get_RealSkillObj"), 0);
    LActorRootOff[19] = FIND_METHOD(OBFUSCATE("Project.Plugins_d.dll"),OBFUSCATE("NucleusDrive.Logic"),OBFUSCATE("PlayerMovement"),OBFUSCATE("get_speed"),0);
    LActorRootOff[20] = FIND_METHOD(OBFUSCATE("Project.Plugins_d.dll"),OBFUSCATE("NucleusDrive.Logic"),OBFUSCATE("LFrameSyncBattlePooledClassObject"),OBFUSCATE("get_battleLogic"),0);
    LActorRootOff[21] = FIND_METHOD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameSystem"),OBFUSCATE("CBattleSystem"),OBFUSCATE("Update"),0);

    LActorRootOffField[0] = FIND_FIELD(OBFUSCATE("Project.Plugins_d.dll"),OBFUSCATE("NucleusDrive.Logic"),OBFUSCATE("LActorRoot"),OBFUSCATE("ValueComponent"));
    LActorRootOffField[1] = FIND_FIELD(OBFUSCATE("Project.Plugins_d.dll"),OBFUSCATE("NucleusDrive.Logic"),OBFUSCATE("LActorRoot"),OBFUSCATE("ActorControl"));
    LActorRootOffField[2] = FIND_FIELD(OBFUSCATE("Project.Plugins_d.dll"),OBFUSCATE("NucleusDrive.Logic"),OBFUSCATE("LActorRoot"),OBFUSCATE("EquipComponent"));
    LActorRootOffField[3] = FIND_FIELD(OBFUSCATE("Project.Plugins_d.dll"),OBFUSCATE("NucleusDrive.Logic"),OBFUSCATE("LActorRoot"),OBFUSCATE("EquipComponent"));
    LActorRootOffField[4] = FIND_FIELD(OBFUSCATE("Project.Plugins_d.dll"),OBFUSCATE("NucleusDrive.Logic"),OBFUSCATE("LActorRoot"),OBFUSCATE("SkillControl"));
    LActorRootOffField[5] = FIND_FIELD(OBFUSCATE("Project.Plugins_d.dll"),OBFUSCATE("NucleusDrive.Logic"),OBFUSCATE("LActorRoot"),OBFUSCATE("ObjLinker"));
    LActorRootOffField[6] = FIND_FIELD(OBFUSCATE("Project.Plugins_d.dll"),OBFUSCATE("NucleusDrive.Logic"),OBFUSCATE("SkillSlot"),OBFUSCATE("<CurSkillCD>k__BackingField"));
    LActorRootOffField[7] = FIND_FIELD(OBFUSCATE("Project.Plugins_d.dll"),OBFUSCATE("NucleusDrive.Logic"),OBFUSCATE("LActorRoot"),OBFUSCATE("HorizonMarker"));
    LActorRootOffField[8] = FIND_FIELD(OBFUSCATE("Project.Plugins_d.dll"),OBFUSCATE("NucleusDrive.Logic"),OBFUSCATE("LBattleLogic"),OBFUSCATE("<spectatorMgr>k__BackingField"));
    LActorRootOffField[9] = FIND_FIELD(OBFUSCATE("Project.Plugins_d.dll"),OBFUSCATE("NucleusDrive.Logic"),OBFUSCATE("LVActorLinker"),OBFUSCATE("Visible"));
    LActorRootOffField[10] = FIND_FIELD(OBFUSCATE("Project.Plugins_d.dll"),OBFUSCATE("NucleusDrive.Logic"),OBFUSCATE("LHeroWrapper"),OBFUSCATE("CommunicateAgentCtrl"));


    MinimapOffField[0] = FIND_FIELD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameSystem"),OBFUSCATE("MinimapSys"),OBFUSCATE("mMapTransferData"));
    MinimapOffField[1] = FIND_FIELD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameSystem"),OBFUSCATE("MinimapSys"),OBFUSCATE("curMapType"));
    MinimapOffField[2] = FIND_FIELD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameSystem"),OBFUSCATE("MinimapSys/CMapTransferData"),OBFUSCATE("mmFinalScreenSize"));
    MinimapOffField[3] = FIND_FIELD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameSystem"),OBFUSCATE("MinimapSys/CMapTransferData"),OBFUSCATE("mmFinalScreenPos"));
    MinimapOffField[4] = FIND_FIELD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameSystem"),OBFUSCATE("MinimapSys/CMapTransferData"),OBFUSCATE("bmFinalScreenPos"));
    MinimapOffField[5] = FIND_FIELD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameSystem"),OBFUSCATE("MinimapSys/CMapTransferData"),OBFUSCATE("bmFinalScreenSize"));
    MinimapOffField[6] = FIND_FIELD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.Framework"),OBFUSCATE("GameFramework"),OBFUSCATE("newResolutionMode"));

    Cam[0] = FIND_METHOD(OBFUSCATE("UnityEngine.CoreModule.dll"),OBFUSCATE("UnityEngine"),OBFUSCATE("Camera"),OBFUSCATE("get_main"), 0);
    Cam[1] = FIND_METHOD(OBFUSCATE("UnityEngine.CoreModule.dll"),OBFUSCATE("UnityEngine"),OBFUSCATE("Camera"),OBFUSCATE("WorldToScreenPoint"), 1);
    Cam[2] = FIND_METHOD(OBFUSCATE("UnityEngine.CoreModule.dll"),OBFUSCATE("UnityEngine"),OBFUSCATE("Camera"),OBFUSCATE("WorldToViewportPoint"), 1);
    Cam[3] = FIND_METHOD(OBFUSCATE("UnityEngine.CoreModule.dll"),OBFUSCATE("UnityEngine"),OBFUSCATE("Camera"),OBFUSCATE("get_fieldOfView"), 0);
    Cam[4] = FIND_METHOD(OBFUSCATE("UnityEngine.CoreModule.dll"),OBFUSCATE("UnityEngine"),OBFUSCATE("Camera"),OBFUSCATE("set_fieldOfView"), 1);

    ModSkin[0] = FIND_METHOD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.Framework"),OBFUSCATE("GameDataMgr"),OBFUSCATE("IsSkinAvailable"),1);
    ModSkin[1] = FIND_METHOD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameSystem"),OBFUSCATE("CRoleInfo"),OBFUSCATE("IsCanUseSkin"), 2);
    ModSkin[2] = FIND_METHOD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameSystem"),OBFUSCATE("CRoleInfo"),OBFUSCATE("GetHeroWearSkinId"), 1);	
    ModSkin[3] = FIND_METHOD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameSystem"),OBFUSCATE("CRoleInfo"),OBFUSCATE("IsPrimeFreeSkin"), 2);
    ModSkin[4] = FIND_METHOD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameSystem"),OBFUSCATE("HeroSelectNormalWindow"),OBFUSCATE("OnClickSelectHeroSkin"), 2);
    ModSkin[5] = FIND_METHOD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameSystem"),OBFUSCATE("HeroSelectNormalWindow"),OBFUSCATE("RefreshHeroPanel"), 3);
    ModSkin[6] = FIND_METHOD(OBFUSCATE("AovTdr.dll"),OBFUSCATE("CSProtocol"),OBFUSCATE("COMDT_HERO_COMMON_INFO"),OBFUSCATE("unpack"),2);
    ModSkin[7] = FIND_METHOD(OBFUSCATE("AovTdr.dll"),OBFUSCATE("ResData"),OBFUSCATE("ResHeroSkin"),OBFUSCATE("unpack"),2);
    ModSkin[8] = FIND_METHOD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameSystem"),OBFUSCATE("AwakeSkinHelper"),OBFUSCATE("IsAwakeSkin"), 1);
    ModSkin[9] = FIND_METHOD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameSystem"),OBFUSCATE("AwakeSkinHelper"),OBFUSCATE("GetAwakeSkinData"), 1);
    ModSkin[10] = FIND_METHOD(OBFUSCATE("AovTdr.dll"),OBFUSCATE("CSProtocol"),OBFUSCATE("COMDT_CHOICEHERO"),OBFUSCATE("unpack"), 2);
    
    ModSkin[11] = FIND_METHOD(OBFUSCATE("Project_d.dll"), OBFUSCATE("Assets.Scripts.GameSystem"), OBFUSCATE("CSkinInfo"), OBFUSCATE("GetHeroSkin"), 2);
    ModSkin[12] = FIND_METHOD(OBFUSCATE("Project_d.dll"), OBFUSCATE("Assets.Scripts.GameLogic"), OBFUSCATE("CActorInfo"), OBFUSCATE("GetSkin"), 1);
    ModSkinOffField[13] = FIND_FIELD(OBFUSCATE("AovTdr.dll"), OBFUSCATE("ResData"), OBFUSCATE("ResHeroSkin"), OBFUSCATE("dwID"));
    
    ModSkinOffField[0] = FIND_FIELD(OBFUSCATE("AovTdr.dll"),OBFUSCATE("CSProtocol"),OBFUSCATE("COMDT_HERO_COMMON_INFO"),OBFUSCATE("dwHeroID"));
    ModSkinOffField[1] = FIND_FIELD(OBFUSCATE("AovTdr.dll"),OBFUSCATE("CSProtocol"),OBFUSCATE("COMDT_HERO_COMMON_INFO"),OBFUSCATE("wSkinID"));
    ModSkinOffField[2] = FIND_FIELD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameSystem"),OBFUSCATE("CHeroSelectNormalSystem"),OBFUSCATE("_heroSelectNormalWindowScript"));
    ModSkinOffField[3] = FIND_FIELD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameSystem"),OBFUSCATE("CHeroSelectBanPickSystem"),OBFUSCATE("m_banPickStep"));
    ModSkinOffField[4] = FIND_FIELD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameSystem"),OBFUSCATE("CHeroSelectBanPickSystem"),OBFUSCATE("banHeroIDList"));
    ModSkinOffField[5] = FIND_FIELD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameSystem"),OBFUSCATE("CHeroSelectBaseSystem"),OBFUSCATE("m_isInHeroSelectState"));

    ModSkinOffField[6] = FIND_FIELD(OBFUSCATE("Project.Plugins_d.dll"), OBFUSCATE("LDataProvider"), OBFUSCATE("PlayerBase"), OBFUSCATE("PersonalButtonID"));
    ModSkinOffField[7] = FIND_FIELD(OBFUSCATE("Project.Plugins_d.dll"), OBFUSCATE("LDataProvider"), OBFUSCATE("PlayerBase"), OBFUSCATE("usingSoldierSkinID"));

    ModSkinOffField[8] = FIND_FIELD(OBFUSCATE("AovTdr.dll"), OBFUSCATE("CSProtocol"), OBFUSCATE("COMDT_HERO_SKIN_WAKE_DATA"), OBFUSCATE("bWakeLevel")); 
    ModSkinOffField[9] = FIND_FIELD(OBFUSCATE("AovTdr.dll"), OBFUSCATE("CSProtocol"), OBFUSCATE("COMDT_HERO_SKIN_WAKE_DATA"), OBFUSCATE("bCurWearLevel"));
    ModSkinOffField[10] = FIND_FIELD(OBFUSCATE("AovTdr.dll"), OBFUSCATE("CSProtocol"), OBFUSCATE("COMDT_HERO_SKIN_WAKE_DATA"), OBFUSCATE("ullWearFeatureMask"));
    ModSkinOffField[11] = FIND_FIELD(OBFUSCATE("AovTdr.dll"), OBFUSCATE("CSProtocol"), OBFUSCATE("COMDT_CHOICEHERO"), OBFUSCATE("bSkinWakeLevel"));
    ModSkinOffField[12] = FIND_FIELD(OBFUSCATE("AovTdr.dll"), OBFUSCATE("CSProtocol"), OBFUSCATE("COMDT_CHOICEHERO"), OBFUSCATE("ullSkinWakeFeatureMask"));
    
    ModRankOffField[0] = FIND_FIELD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameSystem"), OBFUSCATE("CRoleInfo"),OBFUSCATE("m_rankScore"));
    ModRankOffField[1] = FIND_FIELD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameSystem"), OBFUSCATE("CRoleInfo"),OBFUSCATE("m_rankHistoryHighestScore"));
    ModRankOffField[2] = FIND_FIELD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameSystem"), OBFUSCATE("CRoleInfo"),OBFUSCATE("m_rankShowGrade"));
    ModRankOffField[3] = FIND_FIELD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameSystem"), OBFUSCATE("CRoleInfo"),OBFUSCATE("m_rankHistoryHighestShowGrade"));
    ModRankOffField[4] = FIND_FIELD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameSystem"), OBFUSCATE("CRoleInfo"),OBFUSCATE("m_rankSeasonHighestShowGrade"));
    ModRankOffField[5] = FIND_FIELD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameSystem"), OBFUSCATE("CRoleInfo"),OBFUSCATE("mTotalReachRankSTimes"));
    ModRankOffField[6] = FIND_FIELD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameSystem"), OBFUSCATE("CRoleInfo"),OBFUSCATE("m_rankClass"));
    ModRankOffField[7] = FIND_FIELD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameSystem"), OBFUSCATE("CRoleInfo"),OBFUSCATE("m_rankHistoryHighestClass"));
    ModRankOffField[8] = FIND_FIELD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameSystem"), OBFUSCATE("CRoleInfo"),OBFUSCATE("m_rankSeasonHighestClass"));
    ModRankOffField[9] = FIND_FIELD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameSystem"), OBFUSCATE("CRoleInfo"),OBFUSCATE("m_Name"));
    ModRankOffField[10] = FIND_FIELD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameSystem"), OBFUSCATE("CLadderSystem"),OBFUSCATE("currentRankDetail"));
    ModRankOffField[11] = FIND_FIELD(OBFUSCATE("AovTdr.dll"),OBFUSCATE("CSProtocol"), OBFUSCATE("COMDT_RANKDETAIL"),OBFUSCATE("dwScore"));
    ModRankOffField[12] = FIND_FIELD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameSystem"), OBFUSCATE("CRoleInfo"),OBFUSCATE("m_GameVipLevel"));


    

    Antiban[0] = FIND_METHOD(OBFUSCATE("Project.Plugins_d.dll"),OBFUSCATE("NucleusDrive.Logic"),OBFUSCATE("LFrameSynchr"),OBFUSCATE("UpdateFrameLater"), 0);
    Antiban[1] = FIND_METHOD(OBFUSCATE("Project.Plugins_d.dll"),OBFUSCATE("NucleusDrive.Logic"),OBFUSCATE("LSynchrReport"),OBFUSCATE("EnqueHashValueByFrameNum"), 2);
    Antiban[2] = FIND_METHOD(OBFUSCATE("Project.Plugins_d.dll"),OBFUSCATE("NucleusDrive.Logic"),OBFUSCATE("LSynchrReport"),OBFUSCATE("OnHashCheckRsp"), 1);
    Antiban[3] = FIND_METHOD(OBFUSCATE("Project_d.dll"),OBFUSCATE(""),OBFUSCATE("FirebasePush"),OBFUSCATE("handleReportInfoResult"), 1);
    Antiban[4] = FIND_METHOD(OBFUSCATE("Project.Plugins_d.dll"),OBFUSCATE("NucleusDrive.Statistics"),OBFUSCATE("BattleStatistic"),OBFUSCATE("CreateReportData"), 5);
    Antiban[5] = FIND_METHOD(OBFUSCATE("Project.Plugins_d.dll"),OBFUSCATE("NucleusDrive.Statistics"),OBFUSCATE("BattleStatistic"),OBFUSCATE("CreateDestroyReportData"), 3);
    Antiban[6] = FIND_METHOD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameLogic"),OBFUSCATE("LobbyMsgHandler"),OBFUSCATE("HandleGameSettle"), 4);

	Skill[5] = FIND_METHOD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameSystem"),OBFUSCATE("CSkillButtonManager"),OBFUSCATE("SkillButtonDown"), 3);


    // GetZoomRate = (float (*)(void*))((uintptr_t)offset[4]);
    
    OnCameraHeightChanged = (void (*)(void*))((uintptr_t)offset[6]);

    get_talentSystem = (void* (*)(void*))((uintptr_t)FIND_METHOD(OBFUSCATE("Project.Plugins_d.dll"),OBFUSCATE("NucleusDrive.Logic"), OBFUSCATE("LSkillComponent"),OBFUSCATE("get_talentSystem"), 0));
    GetGoldCoinInBattle = (int (*)(void*))((uintptr_t)FIND_METHOD(OBFUSCATE("Project.Plugins_d.dll"),OBFUSCATE("NucleusDrive.Logic"), OBFUSCATE("ValuePropertyComponent"),OBFUSCATE("GetGoldCoinInBattle"), 0));
    GetEquipActiveSkillCD = (int (*)(void*, int))((uintptr_t)FIND_METHOD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Kyrios.Actor"),OBFUSCATE("VEquipLinkerComponent"),OBFUSCATE("GetEquipActiveSkillCD"),1));
    GetTalentCDTime = (int (*)(void*, int))((uintptr_t)FIND_METHOD(OBFUSCATE("Project.Plugins_d.dll"),OBFUSCATE("NucleusDrive.Logic"),OBFUSCATE("TalentSystem"),OBFUSCATE("GetTalentCDTime"), 1));
    SendBuyEquipFrameCommand = (void (*)(void*,int,bool))((uintptr_t)FIND_METHOD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameSystem"),OBFUSCATE("CBattleEquipSystem"),OBFUSCATE("SendBuyEquipFrameCommand"),2));
    SendSellEquipFrameCommand = (void (*)(void*,int))((uintptr_t)FIND_METHOD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameSystem"),OBFUSCATE("CBattleEquipSystem"),OBFUSCATE("SendSellEquipFrameCommand"),1));
    SendPlayerChoseEquipSkillCommand = (void (*)(void*,int))((uintptr_t)FIND_METHOD(OBFUSCATE("Project_d.dll"),OBFUSCATE("Assets.Scripts.GameSystem"),OBFUSCATE("CBattleEquipSystem"),OBFUSCATE("SendPlayerChoseEquipSkillCommand"),1));
	
    _SkillButtonDown = (void (*)(void *, void*, int, Vector2))((uintptr_t)Skill[5]);
    SendEmojiDanceCommandByIndex = (void (*)(void*, int)) FIND_METHOD(OBFUSCATE("Project_d.dll"), OBFUSCATE("Assets.Scripts.GameLogic"), OBFUSCATE("EffectPlayComponent"), OBFUSCATE("SendEmojiDanceCommandByIndex"), 1);

    get_IsHostProfile = (bool (*)(void *))((uintptr_t)offset[11]);
    SetVisible = (bool (*)(void *, COM_PLAYERCAMP, bool, bool))((uintptr_t)offset[0]);
    ForceSetVisible = (void (*)(void *, bool))((uintptr_t)offset[1]);
    SyncActiveView = (void (*)(void *))((uintptr_t)offset[2]);
    IsSkinAvailable = (bool (*)(int))((uintptr_t)ModSkin[0]);
    CanUseSkin = (bool (*)(void *,int,int))((uintptr_t)ModSkin[1]);
    GetHeroWearSkinId = (int (*)(void *,int))((uintptr_t)ModSkin[2]);
    RefreshHeroPanel = (void (*)(void *,bool,bool,bool))((uintptr_t)ModSkin[5]);
    old_unpack = (int32_t (*)(void *, void *, int32_t))((uintptr_t)ModSkin[6]);
    GetAwakeSkinData = (void *(*)(uint32_t))(ModSkin[9]);
    _IsAwakeSkin = (bool (*)(uint32_t))((uintptr_t)ModSkin[8]);
    unpack2 = (void* (*)(uintptr_t, void**, uint32_t))((uintptr_t)ModSkin[10]);
    GetHeroSkin = (void *(*)(int,int))((uintptr_t)ModSkin[11]);
    //get_PersonalBtnId = (int (*)())((uintptr_t)ModSkin[9]);
    get_actorManager = (void* (*)())((uintptr_t)Esp[0]); 
    get_TheMinimapSys = (void* (*)(void*))((uintptr_t)Esp[1]);
    CvtWorld2UISM = (Vector2(*)(void *,Vector3))((uintptr_t)Esp[2]);
    CvtWorld2UIBM = (Vector2(*)(void *,Vector3))((uintptr_t)Esp[3]);
    GetHero_Icon = (MonoString* (*)(void *,int,int))((uintptr_t)Esp[4]);
    get_playerCenter = (void* (*)())((uintptr_t)Esp[5]);
    get_VHostLogic = (void* (*)())((uintptr_t)Esp[6]);
    GetCurLvelContext = (void* (*)(void *))((uintptr_t)Esp[7]);
    GetGameRoomType = (int (*)(void *))((uintptr_t)Esp[8]);
    Reqskill = (bool (*)(void *))((uintptr_t)Esp[9]);
    Reqskill2 = (bool (*)(void *,bool))((uintptr_t)Esp[10]);
    get_IsCharging = (bool (*)(void *))((uintptr_t)Esp[11]);
    get_FightForm = (void* (*)(void *))((uintptr_t)Esp[12]);
    CanRequestSkill = (bool (*)(void*,int))((uintptr_t)Esp[13]);
    RequestUseSkillSlot = (bool (*)(void*,int, int, uint, int))((uintptr_t)Esp[14]);
    SetPlayerName = (void (*)(void*, MonoString*, MonoString*, bool, MonoString*))((uintptr_t)Esp[15]);
    GetSelfCamp = (int (*)(void *))((uintptr_t)Esp[16]);
    GetTeamHeroCommonInfoList = (List<void**>* (*)(void *,int))((uintptr_t)Esp[17]);
    ForceKillCrystal = (void (*)(int))((uintptr_t)Esp[18]);
    GetMasterRoleInfo = (void* (*)(void *))((uintptr_t)Esp[19]);
    FindObjectOfType = (void* (*)(void*))((uintptr_t)Esp[20]);
    GetTypeName = (void* (*)(MonoString*))((uintptr_t)Esp[21]);
    FindObjectsOfType = (Array<void*>* (*)(void*))((uintptr_t)Esp[22]);
    ToStringUnity = (MonoString* (*)(void*))((uintptr_t)Esp[23]);
    FindObjectsOfTypeAll = (Array<void*>* (*)(void*))((uintptr_t)Esp[24]);
    assemblyLoad = (void* (*)(MonoString*))((uintptr_t)Esp[25]);
    assemblyGetType = (void* (*)(void*,MonoString*))((uintptr_t)Esp[26]);
    Object_get_name = (MonoString* (*)(void*))((uintptr_t)Esp[27]);
    get_activeInHierarchy = (bool (*)(void*))((uintptr_t)Esp[28]);
    GetComponents = (Array<void*>* (*)(void*,void*,bool,bool,bool,bool,void*))((uintptr_t)Esp[29]);
    GetComponent = (void* (*)(void*,void*))((uintptr_t)Esp[30]);
    GetComponentInChildren = (void* (*)(void*,void*))((uintptr_t)Esp[31]);
    GetComponentInParent = (void* (*)(void*,void*))((uintptr_t)Esp[32]);
    GetOffsetOfInstanceIDInCPlusPlusObject = (int (*)())((uintptr_t)Esp[33]);
    get_text = (MonoString* (*)(void*))((uintptr_t)Esp[34]);
    GetInstanceID = (void* (*)(void*))((uintptr_t)Esp[35]);
    get_SkillID = (int (*)(void*))((uintptr_t)Esp[39]);
    GetGameTime = (int (*)(void*))((uintptr_t)Esp[40]);
    CalcDirectionByTouchPosition = (VInt3 (*)(void*,Vector2,Vector2))((uintptr_t)Esp[41]);
    
    ActorLinker_IsHostPlayer = (bool (*)(void *))((uintptr_t)ActorLinkerOff[0]);     
    ActorLinker_IsHostCamp = (bool (*)(void *))((uintptr_t)ActorLinkerOff[1]);  
    ActorLinker_ActorTypeDef = (int (*)(void *))((uintptr_t)ActorLinkerOff[2]);    
    ActorLinker_COM_PLAYERCAMP = (int (*)(void *))((uintptr_t)ActorLinkerOff[3]); 
    ActorLinker_getPosition = (Vector3(*)(void *))((uintptr_t)ActorLinkerOff[4]);
    ActorLinker_get_ObjID = (int (*)(void *))((uintptr_t)ActorLinkerOff[6]); 
    ActorLinker_get_bVisible = (bool (*)(void *))((uintptr_t)ActorLinkerOff[7]);
    ActorLinker_AsHero = (void*(*)(void*))((uintptr_t)ActorLinkerOff[8]);
    ActorLinker_get_playerId = (int (*)(void *))((uintptr_t)ActorLinkerOff[9]);
    get_ValueCompChangeActor = (void* (*)(void*))((uintptr_t)ActorLinkerOff[10]);
    ValueLinkerComponent_get_actorHp = (int (*)(void *))((uintptr_t)ActorLinkerOff[11]);
    ValueLinkerComponent_get_actorHpTotal = (int (*)(void *))((uintptr_t)ActorLinkerOff[12]);
    ValueLinkerComponent_get_actorSoulLevel = (int (*)(void*))((uintptr_t)ActorLinkerOff[13]);

    LActorRoot_get_forward = (VInt3(*)(void *))((uintptr_t)LActorRootOff[0]);
    LActorRoot_get_location = (VInt3(*)(void *))((uintptr_t)LActorRootOff[1]); 
    LActorRoot_LHeroWrapper = (void* (*)(void *))((uintptr_t)LActorRootOff[2]);
    LActorRoot_COM_PLAYERCAMP = (int (*)(void *))((uintptr_t)LActorRootOff[3]); 
    LActorRoot_get_bActive = (bool (*)(void *))((uintptr_t)LActorRootOff[4]); 
    LActorRoot_get_ObjID = (int (*)(void *))((uintptr_t)LActorRootOff[5]);
    LObjWrapper_get_IsDeadState = (bool (*)(void *))((uintptr_t)LActorRootOff[6]); 
    LObjWrapper_IsAutoAI = (bool (*)(void *))((uintptr_t)LActorRootOff[7]);
    ValuePropertyComponent_get_actorHp = (int (*)(void *))((uintptr_t)LActorRootOff[8]);    
    ValuePropertyComponent_get_actorHpTotal = (int (*)(void *))((uintptr_t)LActorRootOff[9]); 
    LActorRoot_get_PlayerMovement = (void* (*)(void*))((uintptr_t)LActorRootOff[10]);
    LEquipComponent_BuyEquip = (void (*)(void*,int,bool,bool))((uintptr_t)LActorRootOff[11]);
    LEquipComponent_SellEquip = (void (*)(void*,int))((uintptr_t)LActorRootOff[12]);
    LEquipComponent_GetEquips = (void* (*)(void*))((uintptr_t)LActorRootOff[13]);    
    ValuePropertyComponent_get_actorSoulLevel = (int (*)(void *))((uintptr_t)LActorRootOff[14]); 
    ValuePropertyComponent_get_actorEp = (int (*)(void *))((uintptr_t)LActorRootOff[15]);    
    ValuePropertyComponent_get_actorEpTotal = (int (*)(void *))((uintptr_t)LActorRootOff[16]); 
    GetSkillSlot = (void* (*)(void*,int))((uintptr_t)LActorRootOff[17]);
    get_RealSkillObj = (void* (*)(void*))((uintptr_t)LActorRootOff[18]);
    get_speed = (int (*)(void*))((uintptr_t)LActorRootOff[19]);
    get_battleLogic = (void* (*)(void*))((uintptr_t)LActorRootOff[20]);


    //CBattleSystem_Update = (void* (*)(void*))((uintptr_t)LActorRootOff[21]);￼

    CBattleSystem_Update = (void* (*)(void*))((uintptr_t)LActorRootOff[21]);

    get_main = (void* (*)())((uintptr_t)Cam[0]);
    WorldToScreenPoint = (Vector3 (*)(void*, Vector3))((uintptr_t)Cam[1]);
    WorldToViewportPoint = (Vector3 (*)(void*, Vector3))((uintptr_t)Cam[2]);
    get_fieldOfView = (float (*)(void*))((uintptr_t)Cam[3]);
    set_fieldOfView = (void (*)(void*, float))((uintptr_t)Cam[4]);

    CreateReportData = (void* (*)(void*, uint, unsigned long long, bool, bool, bool))((uintptr_t)Antiban[4]);
    CreateDestroyReportData = (void (*)(void*, uint, void*, bool))((uintptr_t)Antiban[5]);
    HandleGameSettle = (void (*)(void*,bool, bool, Byte, void*))((uintptr_t)Antiban[6]);
    daloadoffset = true;
    });
}