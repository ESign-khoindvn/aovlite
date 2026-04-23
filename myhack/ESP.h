#include <iomanip>
#include "patches.h"
#include "mylib/anhvu.h"
#include "auto_offsets.h"
#import <Metal/Metal.h>
id<MTLTexture> logo_texture = nil;
void (*ForceSetVisible)(void *instance, bool bVisible);
void (*SyncActiveView)(void *instance);
MonoString *(*ToStringUnity)(void *instance);
Array<void *> *(*FindObjectsOfType)(void *type);
Array<void *> *(*FindObjectsOfTypeAll)(void *type);
void *(*FindObjectOfType)(void *type);
void *(*GetTypeName)(MonoString *stringname);
void *(*assemblyLoad)(MonoString *stringname);
void *(*assemblyGetType)(void *assembly, MonoString *stringname);
MonoString *(*Object_get_name)(void *instance);
bool (*get_activeInHierarchy)(void *instance);
Array<void *> *(*GetComponents)(void *instance, void *type, bool useSearchTypeAsArrayReturnType, bool recursive, bool includeInactive, bool reverse, void *resultList);
void *(*GetComponent)(void *instance, void *type);
void *(*GetComponentInChildren)(void *instance, void *type);
void *(*GetComponentInParent)(void *instance, void *type);
int (*GetOffsetOfInstanceIDInCPlusPlusObject)();
MonoString *(*get_text)(void *instance);
void *(*GetInstanceID)(void *instance);
void *(*CBattleSystem_Update)(void *instance);
void *(*get_battleLogic)(void *instance);
void *(*GetCurLvelContext)(void *instance);
int (*GetGameRoomType)(void *instance);
void *(*get_TheMinimapSys)(void *instance);
Vector2 (*CvtWorld2UISM)(void *instance, Vector3 pos);
Vector2 (*CvtWorld2UIBM)(void *instance, Vector3 pos);
MonoString *(*GetHero_Icon)(void *instance, int heroID, int SkinID);
void *(*set_actorSoulLevel)(void *instance, int32_t value);
void (*SendEmojiDanceCommandByIndex)(void *instance, int index);
int SkillSlotType = 0;
int MyHeroID = 0;
Vector3 myPos = Vector3::zero();

void *(*get_actorManager)();
void *(*get_playerCenter)();
void *(*get_VHostLogic)();
int (*GetSelfCamp)(void *instance);
int (*GetGameTime)(void *instance);
List<void **> *(*GetTeamHeroCommonInfoList)(void *instance, int camp);
int (*ActorLinker_COM_PLAYERCAMP)(void *instance);
bool (*ActorLinker_IsHostPlayer)(void *instance);
bool (*ActorLinker_IsHostCamp)(void *instance);
int (*ActorLinker_get_playerId)(void *instance);
int (*ActorLinker_ActorTypeDef)(void *instance);
void *(*get_ValueCompChangeActor)(void *instance);
Vector3 (*ActorLinker_getPosition)(void *instance);
int (*ActorLinker_get_ObjID)(void *instance);
int (*ActorLinker_get_ConfigID)(void *instance);
bool (*ActorLinker_get_bVisible)(void *instance);
void *(*ActorLinker_AsHero)(void *instance);

VInt3 (*LActorRoot_get_location)(void *instance);
VInt3 (*LActorRoot_get_forward)(void *instance);
void *(*LActorRoot_LHeroWrapper)(void *instance);
int (*LActorRoot_COM_PLAYERCAMP)(void *instance);
bool (*LActorRoot_get_bActive)(void *instance);
int (*LActorRoot_get_ObjID)(void *instance);
bool (*LObjWrapper_get_IsDeadState)(void *instance);
bool (*LObjWrapper_IsAutoAI)(void *instance);
int (*ValuePropertyComponent_get_actorHp)(void *instance);
int (*ValuePropertyComponent_get_actorHpTotal)(void *instance);
int (*ValueLinkerComponent_get_actorHp)(void *instance);
int (*ValueLinkerComponent_get_actorHpTotal)(void *instance);
int (*ValueLinkerComponent_get_actorSoulLevel)(void *instance);
void *(*LActorRoot_get_PlayerMovement)(void *instance);
int (*get_speed)(void *instance);
void (*LEquipComponent_BuyEquip)(void *instance, int equipID, bool InIsQuicklyBuy, bool InAutobuy);
void (*LEquipComponent_SellEquip)(void *instance, int equipindex);
void *(*LEquipComponent_GetEquips)(void *instance);
int (*GetTalentCDTime)(void *instance, int _talentID);
int (*GetEquipActiveSkillCD)(void *instance, int equipID);
void *(*get_talentSystem)(void *instance);
int (*GetGoldCoinInBattle)(void *instance);
void (*SendBuyEquipFrameCommand)(void *instance, int equipID, bool InIsQuicklyBuy);
void (*SendSellEquipFrameCommand)(void *instance, int equipID);
void (*SendPlayerChoseEquipSkillCommand)(void *instance, int slot);
int (*ValuePropertyComponent_get_actorEp)(void *instance);
int (*ValuePropertyComponent_get_actorEpTotal)(void *instance);
int (*ValuePropertyComponent_get_actorSoulLevel)(void *instance);
void *(*GetSkillSlot)(void *instance, int skillslottype);
void *(*get_RealSkillObj)(void *instance);
int (*get_SkillID)(void *instance);
bool (*Reqskill)(void *instance);
bool (*Reqskill2)(void *instance, bool bForce);
void *(*get_FightForm)(void *instance);
bool (*RequestUseSkillSlot)(void *instance, int slot, int mode, uint objID, int subSkillID);
bool (*CanRequestSkill)(void *instance, int slot);
bool (*get_IsCharging)(void *instance);
void *(*GetEquipInfo)(void *instance, int equipindex);
Dictionary<int, void *> *(*get_EquipPassiveSkillInfoMap)(void *instance);
void *(*get_curUpdatingDesk)(void *instance);
void *myActorLinker = nullptr;
void *myLactorRoot = nullptr;
void (*ForceKillCrystal)(int camp);
void *(*GetMasterRoleInfo)(void *instance);
void (*SetPlayerName)(void *instance, MonoString *playerName, MonoString *prefixName, bool isGuideLevel, MonoString *Customname);
void *(*get_main)();
Vector3 (*WorldToScreenPoint)(void *instance, Vector3 worldPosition);
Vector3 (*WorldToViewportPoint)(void *instance, Vector3 worldPosition);
float (*get_fieldOfView)(void *instance);
void (*set_fieldOfView)(void *instance, float fieldOfView);
VInt3 (*CalcDirectionByTouchPosition)(void *instance, Vector2 InFirstTouch, Vector2 InSecondTouch);

struct SkillInfo
{
    int skillcd;
    int skillID;
};
SkillInfo Skillcd(void *instance, int slot)
{
    SkillInfo result = {0, 0};
    void *check = GetSkillSlot(instance, slot);
    if (check != NULL)
    {
        void *check20 = get_RealSkillObj(check);
        if (check20 != NULL)
        {
            result.skillcd = GetObscuredIntValue((uintptr_t)check + LActorRootOffField[6]);
            result.skillID = *(int *)((uintptr_t)check20 + ActorLinkerOffField[25]);
        }
    }
    return result;
}
int *SkillControlAll1(void *instance)
{
    int *cooldowns = (int *)malloc(5 * sizeof(int));
    if (cooldowns == NULL)
    {
        return NULL;
    }

    SkillInfo skillInfo1 = Skillcd(instance, 1);
    SkillInfo skillInfo2 = Skillcd(instance, 2);
    SkillInfo skillInfo3 = Skillcd(instance, 3);
    SkillInfo skillInfo5 = Skillcd(instance, 5);

    cooldowns[0] = (int)ceil(skillInfo1.skillcd / 1000.0);
    cooldowns[1] = (int)ceil(skillInfo2.skillcd / 1000.0);
    cooldowns[2] = (int)ceil(skillInfo3.skillcd / 1000.0);
    cooldowns[3] = (int)ceil(skillInfo5.skillcd / 1000.0);
    cooldowns[4] = skillInfo5.skillID > 3100000 ? (skillInfo5.skillID - 3100000) : skillInfo5.skillID;

    return cooldowns;
}
int *SkillControlAll(void *instance)
{
    void *SkillControl = ActorLinker_AsHero(instance);
    int *cooldowns = (int *)malloc(5 * sizeof(int));
    if (!cooldowns)
        return NULL;
    if (SkillControl != NULL)
    {
        int skill4 = *(int *)((uintptr_t)SkillControl + ActorLinkerOffField[15]);
        uintptr_t Skill1Cd = (int)ceil(*(int *)((uintptr_t)SkillControl + ActorLinkerOffField[12] + ActorLinkerOffField[16] - 0x10) / 1000.0);
        uintptr_t Skill2Cd = (int)ceil(*(int *)((uintptr_t)SkillControl + ActorLinkerOffField[13] + ActorLinkerOffField[16] - 0x10) / 1000.0);
        uintptr_t Skill3Cd = (int)ceil(*(int *)((uintptr_t)SkillControl + ActorLinkerOffField[14] + ActorLinkerOffField[16] - 0x10) / 1000.0);
        uintptr_t Skill4Cd = (int)ceil(*(int *)((uintptr_t)SkillControl + ActorLinkerOffField[15] + ActorLinkerOffField[16] - 0x10) / 1000.0);
        cooldowns[0] = Skill1Cd;
        cooldowns[1] = Skill2Cd;
        cooldowns[2] = Skill3Cd;
        cooldowns[3] = Skill4Cd;
        cooldowns[4] = skill4 > 3100000 ? (skill4 - 3100000) : skill4;
        return cooldowns;
    }
    free(cooldowns);
    return NULL;
}
ImVec2 GetPlayerPosition(Vector3 Pos)
{
    Vector3 PosSC = WorldToViewportPoint(get_main(), Pos);
    ImVec2 Pos_Vec2 = ImVec2((kWidth - PosSC.x * kWidth), PosSC.y * kHeight);
    if (PosSC.z > 0)
    {
        Pos_Vec2 = ImVec2(PosSC.x * kWidth, (kHeight - PosSC.y * kHeight));
    }
    return Pos_Vec2;
}
void Draw3DCircle(ImDrawList *draw, Vector3 &worldPos, ImVec2 &centerScreen, float radius, int numPoints, float thickness)
{
    if (numPoints >= 200)
        return;
    static ImVec2 points[200];
    Vector3 edgeX = {worldPos.x + radius, worldPos.y, worldPos.z};
    ImVec2 edgeXScreen = GetPlayerPosition(edgeX);
    float distance1 = Vector2::Distance({centerScreen.x, centerScreen.y}, {edgeXScreen.x, edgeXScreen.y});
    float radiusX = sqrtf(
        (edgeXScreen.x - centerScreen.x) * (edgeXScreen.x - centerScreen.x) +
        (edgeXScreen.y - centerScreen.y) * (edgeXScreen.y - centerScreen.y));
    Vector3 edgeZ = {worldPos.x, worldPos.y, worldPos.z + radius};

    ImVec2 edgeZScreen = GetPlayerPosition(edgeZ);
    float distance2 = Vector2::Distance({centerScreen.x, centerScreen.y}, {edgeZScreen.x, edgeZScreen.y});
    iconradius = distance1 > distance2 ? distance2 : distance1;
    float radiusZ = sqrtf(
        (edgeZScreen.x - centerScreen.x) * (edgeZScreen.x - centerScreen.x) +
        (edgeZScreen.y - centerScreen.y) * (edgeZScreen.y - centerScreen.y));

    const float step = 6.2831f / numPoints; // 2pi/number of points
    for (int i = 0; i < numPoints; ++i)
    {
        float angle = i * step;
        float offsetX = cosf(angle) * radius;
        float offsetZ = sinf(angle) * radius;
        float screenOffsetX = cosf(angle) * radiusX;
        float screenOffsetY = sinf(angle) * radiusZ;

        points[i] = ImVec2(centerScreen.x + screenOffsetX, centerScreen.y - screenOffsetY);
    }

    draw->AddPolyline(points, numPoints, ImColor(Colorwhite), true, thickness);
}
void DrawHealthBar(ImDrawList *draw, ImVec2 rootPos_Vec2, int EnemyHp, int EnemyHpTotal, int EnemyEp, int EnemyEpTotal, string heroname, int GetLever)
{
    float scale = 0.9f;
    float nameScale = 0.8f;

    rootPos_Vec2.y -= 5.0f; // đẩy tổng thể lên 5px

    ImVec2 namePos(rootPos_Vec2.x - 45 * scale, rootPos_Vec2.y + 22 * scale);

    float backgroundWidth = 90.0f * scale;
    float healthBarWidth = (backgroundWidth - 7.2f * scale);
    float healthBarHeight = 4.3f * scale;
    float ManaBarHeight = 2.5f * scale;
    float manaBarWidth = (backgroundWidth - 6.0f * scale);

    ImVec2 nameSize = ImGui::CalcTextSize(heroname.c_str());
    nameSize.x *= nameScale;
    nameSize.y *= nameScale;

    ImVec2 levelSize = ImGui::CalcTextSize(to_string(GetLever).c_str());
    levelSize.x *= scale;
    levelSize.y *= scale;

    // Vẽ nền đen
    ImVec2 rectPos = namePos;
    ImVec2 rectSize = ImVec2(namePos.x + backgroundWidth, namePos.y + (13 + ManaBarHeight));
    draw->AddRectFilled(rectPos, rectSize, IM_COL32(0, 0, 0, 150));

    // Vẽ hình thoi và level
    ImVec2 diamondCenter(namePos.x, namePos.y + levelSize.y / 2);
    float diamondSize = 6.0f * scale;
    float borderThickness = 1.25f * scale;

    // Tên (heroname nhỏ hơn nữa)
    ImVec2 heronamePos(namePos.x + (backgroundWidth - nameSize.x) / 2, namePos.y);
    draw->AddText(NULL, ImGui::GetFontSize() * nameScale, heronamePos, IM_COL32(255, 255, 0, 255), heroname.c_str());

    // Vị trí thanh máu và năng lượng
    ImVec2 healthBarBackgroundPos(namePos.x + 7.2f * scale, namePos.y + 9.0f * scale);
    ImVec2 manaBarBackgroundPos(namePos.x + 6.0f * scale, namePos.y + 13.0f * scale);

    // Vẽ thanh máu
    draw->AddRectFilled(healthBarBackgroundPos,
                        ImVec2(healthBarBackgroundPos.x - 7.3f * scale + backgroundWidth, healthBarBackgroundPos.y + healthBarHeight),
                        IM_COL32(0, 0, 0, 150));
    draw->AddRectFilled(healthBarBackgroundPos,
                        ImVec2(healthBarBackgroundPos.x + healthBarWidth * ((float)EnemyHp / (float)EnemyHpTotal), healthBarBackgroundPos.y + healthBarHeight),
                        IM_COL32(0, 255, 0, 150));

    // Vẽ thanh năng lượng
    draw->AddRectFilled(manaBarBackgroundPos,
                        ImVec2(manaBarBackgroundPos.x - 7.3f * scale + backgroundWidth, manaBarBackgroundPos.y + ManaBarHeight),
                        IM_COL32(0, 0, 0, 150));
    if (EnemyEpTotal > 0)
    {
        draw->AddRectFilled(manaBarBackgroundPos,
                            ImVec2(manaBarBackgroundPos.x + manaBarWidth * ((float)EnemyEp / (float)EnemyEpTotal), manaBarBackgroundPos.y + ManaBarHeight),
                            IM_COL32(50, 104, 168, 255));
    }
    else
    {
        draw->AddRectFilled(manaBarBackgroundPos,
                            ImVec2(manaBarBackgroundPos.x + manaBarWidth, manaBarBackgroundPos.y + ManaBarHeight),
                            IM_COL32(255, 255, 255, 150));
    }

    // Viền hình thoi trắng
    for (float i = 0; i < borderThickness; i++)
    {
        draw->AddQuad(
            ImVec2(diamondCenter.x, diamondCenter.y - diamondSize - i),
            ImVec2(diamondCenter.x + diamondSize + i, diamondCenter.y),
            ImVec2(diamondCenter.x, diamondCenter.y + diamondSize + i),
            ImVec2(diamondCenter.x - diamondSize - i, diamondCenter.y),
            IM_COL32(255, 255, 255, 255));
    }

    // Hình thoi đen
    draw->AddQuadFilled(
        ImVec2(diamondCenter.x, diamondCenter.y - diamondSize),
        ImVec2(diamondCenter.x + diamondSize, diamondCenter.y),
        ImVec2(diamondCenter.x, diamondCenter.y + diamondSize),
        ImVec2(diamondCenter.x - diamondSize, diamondCenter.y),
        IM_COL32(0, 0, 0, 255));

    // Level
    draw->AddText(ImVec2(diamondCenter.x - levelSize.x / 2, diamondCenter.y - levelSize.y / 2), IM_COL32(255, 255, 255, 255), to_string(GetLever).c_str());
}
void DrawTextureFixed(ImDrawList *draw, ImVec2 point, Texture &tex, float scale)
{
    float width = scale;
    float height = scale;
    ImVec2 topLeft = ImVec2(point.x - width / 2, point.y - height / 2);
    draw->AddImage((ImTextureID)(intptr_t)tex.texture, topLeft, ImVec2(topLeft.x + width, topLeft.y + height), ImVec2(0, 0), ImVec2(1, 1));
}
void DrawCircleHealthMiniMap(ImDrawList *draw, ImVec2 position, int health, int max_health, float radius, float size)
{

    if (health > max_health)
    {
        health = max_health;
    }
    if (health < 0)
    {
        health = 0;
    }

    float a_max = 6.28318530718f; // 2*PI
    ImU32 healthColor = IM_COL32(200, 0, 0, 255);
    ImU32 borderColor = IM_COL32(68, 18, 20, 255);

    // Vẽ viền tròn
    draw->PathArcTo(position, radius + size / 2, 0.0f, a_max);
    draw->PathStroke(borderColor, ImDrawFlags_None, size + 1.5f);

    // Tính toán góc cho phần máu (tụt từ đỉnh xuống)
    float health_ratio = static_cast<float>(health) / max_health;
    float angle = a_max * health_ratio / 2.0f;

    // Đặt điểm bắt đầu vẽ ở đỉnh ( -PI/2 )
    float start_angle = a_max / 4.0f;

    // Vẽ phần máu
    draw->PathArcTo(position, radius + size / 2, start_angle + angle, start_angle - angle);
    draw->PathStroke(healthColor, ImDrawFlags_None, size);
}
void DrawCd(ImDrawList *draw, ImVec2 position, float size, ImU32 color, int cd)
{
    string skill_cd = "[" + to_string(cd) + "]";
    ImVec2 textSize = ImGui::CalcTextSize(skill_cd.c_str());
    ImVec2 textPos = {position.x - (textSize.x) / 2, position.y - (textSize.y) / 2};

    draw->AddText(textPos, cd > 0 ? color : IM_COL32(128, 128, 128, 128), skill_cd.c_str());
}
void DrawCircleHealth(ImVec2 position, int health, int max_health, float radius, int width)
{
    float a_max = ((3.14159265359f * 2.0f));
    ImU32 healthColor = IM_COL32(45, 180, 45, 255);
    if (health <= (max_health * 0.6))
    {
        healthColor = IM_COL32(180, 180, 45, 255);
    }
    if (health < (max_health * 0.3))
    {
        healthColor = IM_COL32(180, 45, 45, 255);
    }
    ImGui::GetForegroundDrawList()->PathArcTo(position, radius, (-(a_max / 4.0f)) + (a_max / max_health) * (max_health - health), a_max - (a_max / 4.0f));
    ImGui::GetForegroundDrawList()->PathStroke(healthColor, ImDrawFlags_None, width);
}
void DrawPlayerAlert(ImDrawList *draw, ImVec2 rootPos, int index, int hp, int maxHp, string dist)
{
    const float borderOffset = -50.0f;
    ImVec2 screenSize(kWidth, kHeight);

    ImVec2 hintPos = pushToScreenBorder(rootPos, screenSize, borderOffset);
    draw->AddCircleFilled(hintPos, 1.7f * kHeight / 39.0f, IM_COL32(0, 0, 0, 110));
    DrawCircleHealth(hintPos, hp, maxHp, ((float)1.7 * kHeight / 39.0f), 3.0f);
    if (index != -1)
    {
        DrawTextureFixed(draw, hintPos, textures[index], 2.6f * kHeight / 39.0f);
    }

    ImVec2 textSize = ImGui::CalcTextSize(dist.c_str());
    ImVec2 textPos = {
        hintPos.x - (textSize.x) / 2,
        hintPos.y - (textSize.y) / 2};
    draw->AddText(textPos, IM_COL32_WHITE, dist.c_str());
}
void DrawIconHero(ImDrawList *draw, ImVec2 HeroScreenPos, Texture &tex, float width)
{

    ImVec2 imageSize = ImVec2(width, width);
    if (iconradius > 0)
        imageSize = ImVec2(iconradius * 2 * customIconSize, iconradius * 2 * customIconSize);

    ImVec2 iconPos = ImVec2(HeroScreenPos.x - imageSize.x / 2, static_cast<float>(HeroScreenPos.y - imageSize.y / 2));

    draw->AddImage((ImTextureID)(intptr_t)tex.texture, iconPos, ImVec2(iconPos.x + imageSize.x, iconPos.y + imageSize.y));
}

void DrawIconBT(ImDrawList *draw, int index, int *cooldowns, int Heroindex, int EnemyHp, int EnemyHpTotal, bool dead)
{
    const float baseScale = (kScale == 2 && kHeight < 500 ? 12.0f : 42.0f / kScale) * customBTScale;
    const float iconScale = 1.5f * baseScale;
    if (!CustomIconBT)
    {
        CustomX = MinimapCenterX + MinimapSize.x * 0.6f;
        CustomY = iconScale / 2 + 10;
    }
    ImVec2 IconheroPos = ImVec2(CustomX + (Heroindex + 5) * iconScale + round(MinimapSize.x / 20) * Heroindex, CustomY);

    if (index != -1)
    {
        float borderThickness = 1.0f;
        ImU32 borderColor = IM_COL32(139, 0, 0, 255); // Màu đỏ
        draw->AddCircleFilled(IconheroPos, iconScale / 2 + borderThickness, borderColor, 120);
        DrawTextureFixed(draw, IconheroPos, textures[index], iconScale - 2 * borderThickness);
        if (dead)
            draw->AddCircleFilled(IconheroPos, iconScale / 2 + borderThickness, IM_COL32(0, 0, 0, 128), 120);
    }

    ImVec2 IconCenterPos = ImVec2(IconheroPos.x, (IconheroPos.y - iconScale / 2) - 2.0f);
    if (cooldowns != NULL)
    {
        float radius = iconScale / 8;
        float size = 1.0f;
        ImU32 greenColor = IM_COL32(0, 200, 0, 255);
        ImU32 borderColor = IM_COL32(175, 238, 238, 255);
        float diamondSize = radius * 1.5f;
        float borderThickness = 1.5f;
        if (cooldowns[2] > 0)
        {
            float cooldown_ratio = static_cast<float>(cooldowns[2]);

            for (float i = 0; i < borderThickness; i++)
            {
                draw->AddQuad(
                    ImVec2(IconCenterPos.x, IconCenterPos.y - diamondSize - i),
                    ImVec2(IconCenterPos.x + diamondSize + i, IconCenterPos.y),
                    ImVec2(IconCenterPos.x, IconCenterPos.y + diamondSize + i),
                    ImVec2(IconCenterPos.x - diamondSize - i, IconCenterPos.y),
                    borderColor);
            }
            draw->AddQuadFilled(
                ImVec2(IconCenterPos.x, IconCenterPos.y - diamondSize),
                ImVec2(IconCenterPos.x + diamondSize, IconCenterPos.y),
                ImVec2(IconCenterPos.x, IconCenterPos.y + diamondSize),
                ImVec2(IconCenterPos.x - diamondSize, IconCenterPos.y),
                IM_COL32(30, 30, 30, 255));

            string skill_cd = to_string(static_cast<int>(cooldowns[2]));

            ImVec2 textSize = ImGui::CalcTextSize(skill_cd.c_str());
            if (cooldowns[2] <= 9)
            {

                draw->AddText(ImVec2(IconCenterPos.x - textSize.x / 2 + 0.8f, IconCenterPos.y - textSize.y / 2), greenColor, skill_cd.c_str());
            }
        }
        else
        {

            for (float i = 0; i < borderThickness; i++)
            {
                draw->AddQuad(
                    ImVec2(IconCenterPos.x, IconCenterPos.y - diamondSize - i),
                    ImVec2(IconCenterPos.x + diamondSize + i, IconCenterPos.y),
                    ImVec2(IconCenterPos.x, IconCenterPos.y + diamondSize + i),
                    ImVec2(IconCenterPos.x - diamondSize - i, IconCenterPos.y),
                    borderColor);
            }
            draw->AddQuadFilled(
                ImVec2(IconCenterPos.x, IconCenterPos.y - diamondSize),
                ImVec2(IconCenterPos.x + diamondSize, IconCenterPos.y),
                ImVec2(IconCenterPos.x, IconCenterPos.y + diamondSize),
                ImVec2(IconCenterPos.x - diamondSize, IconCenterPos.y),
                greenColor);
        }
    }

    // Vẽ thanh máu
    float healthBarWidth = iconScale;
    float healthBarHeight = 2.75f;
    ImVec2 healthBarPos = ImVec2(IconheroPos.x - healthBarWidth / 2, IconheroPos.y + iconScale / 2 + healthBarHeight); // Điều chỉnh vị trí thanh máu

    // Vẽ nền thanh máu
    draw->AddRectFilled(healthBarPos, ImVec2(healthBarPos.x + healthBarWidth, healthBarPos.y + healthBarHeight), IM_COL32(0, 0, 0, 150));

    // Vẽ thanh máu
    if (EnemyHpTotal > 0)
    {
        float healthRatio = (float)EnemyHp / EnemyHpTotal;
        ImU32 healthColor = IM_COL32(102, 207, 252, 255);
        draw->AddRectFilled(healthBarPos, ImVec2(healthBarPos.x + healthBarWidth * healthRatio, healthBarPos.y + healthBarHeight), healthColor);
    }
    // Vẽ icon bổ trợ
    ImVec2 IconBTPos = ImVec2(IconheroPos.x, IconheroPos.y + iconScale + healthBarHeight + 2.0f);
    if (cooldowns != NULL)
    {
        if (cooldowns[4] > 0)
        {
            int indexbt = findHeroById(cooldowns[4]).index;
            if (indexbt != -1)
            {
                DrawTextureFixed(draw, IconBTPos, textures[indexbt], baseScale - 1);
            }
            if (cooldowns[3] > 0)
            {
                draw->AddCircleFilled(IconBTPos, baseScale / 2, IM_COL32(0, 0, 0, 128));
                string cooldownText = to_string(cooldowns[3]);

                ImVec2 textSize = ImGui::CalcTextSize(cooldownText.c_str());
                ImVec2 textPos = ImVec2(IconBTPos.x - textSize.x / 2, IconBTPos.y - textSize.y / 2);
                draw->AddText(textPos, IM_COL32(255, 255, 255, 255), cooldownText.c_str());
            }
        }
    }
}
void DrawSkillCD(ImDrawList *draw, ImVec2 rootPos_Vec2, void *Enemy)
{
    float boxHeight = kHeight / 10;
    float boxWidth = boxHeight * 0.375f;
    ImVec2 vStart = {rootPos_Vec2.x - boxWidth - 6.0f, rootPos_Vec2.y - boxHeight};
    ImVec2 vEnd = {vStart.x + 2 * boxWidth, vStart.y + boxHeight};
    void *SkillControl = *(void **)((uintptr_t)Enemy + LActorRootOffField[4]);
    if (SkillControl != NULL)
    {
        int *cooldowns = SkillControlAll1(SkillControl);
        if (cooldowns != NULL)
        {
            float size = boxHeight / 8;
            ImVec2 position = ImVec2(vStart.x - size - boxWidth + 20.0f, vStart.y + (size / 2));

            ImVec2 position2 = ImVec2(vStart.x - size - boxWidth + 20.0f, position.y + size * 2);

            ImVec2 position3 = ImVec2(vStart.x - size - boxWidth + 20.0f, position2.y + size * 2);

            ImVec2 position4 = ImVec2(vStart.x - size - boxWidth + 20.0f, vEnd.y - size / 2);

            ImU32 color = ImColor(1.0f, 0.5f, 0.0f, 1.0f);
            int cd1 = cooldowns[0];
            int cd2 = cooldowns[1];
            int cd3 = cooldowns[2];
            int cd4 = cooldowns[3];
            DrawCd(draw, position, size, color, cd1);
            DrawCd(draw, position2, size, color, cd2);
            DrawCd(draw, position3, size, color, cd3);
            DrawCd(draw, position4, size, color, cd4);
        }
        free(cooldowns);
    }
}
ImVec2 calMinimapPos(Vector3 EnemyPos)
{
    ImVec2 enemyiconPos = {0, 0};
    float scalemapX = 109;
    float scalemapY = scalemapX;
    if (roomtype == 5)
    { // map 1v1
        if (MapType == 1)
        {
            scalemapX = 82.5;
            scalemapY = 78.8;
        }
        else if (MapType == 2)
        {
            scalemapX = 84;
            scalemapY = 87.5;
        }
    }
    if (MinimapSize.x > 1.5 * MinimapSize.y)
    { // map 3v3
        if (MapType == 1)
        {
            scalemapX = 135;
            scalemapY = scalemapX / 3;
        }
        else if (MapType == 2)
        {
            scalemapX = 130;
            scalemapY = scalemapX / 3;
        }
    }
    if (MapType == 1) // minimap
    {
        enemyiconPos = {
            MinimapX + EnemyPos.x * MinimapSizeX / scalemapX,
            MinimapY - EnemyPos.z * MinimapSizeY / scalemapY};
        if (myTeam == 2)
        {
            enemyiconPos.x = MinimapX - EnemyPos.x * MinimapSizeX / scalemapX;
            enemyiconPos.y = MinimapY + EnemyPos.z * MinimapSizeY / scalemapY;
        }
        if (MinimapSize.x > 1.5 * MinimapSize.y && myTeam == 2)
        {
            enemyiconPos.x = MinimapX - EnemyPos.x * MinimapSizeX / scalemapX;
            enemyiconPos.y = MinimapY - EnemyPos.z * MinimapSizeY / scalemapY;
        }
        return enemyiconPos;
    }
    else if (MapType == 2) // bigmap
    {
        enemyiconPos = {
            BigmapCenterX + EnemyPos.x * BigmapSize.x / scalemapX,
            BigmapCenterY - EnemyPos.z * BigmapSize.y / scalemapY};
        if (myTeam == 2)
        {
            enemyiconPos.x = BigmapCenterX - EnemyPos.x * BigmapSize.x / scalemapX;
            enemyiconPos.y = BigmapCenterY + EnemyPos.z * BigmapSize.y / scalemapY;
        }
        if (MinimapSize.x > 1.5 * MinimapSize.y && myTeam == 2)
        {
            enemyiconPos.x = BigmapCenterX - EnemyPos.x * BigmapSize.x / scalemapX;
            enemyiconPos.y = BigmapCenterY - EnemyPos.z * BigmapSize.y / scalemapY;
        }
    }
    return enemyiconPos;
}
void DrawIconMap(ImDrawList *draw, Vector3 EnemyPos, int index, int EnemyHp, int EnemyHpTotal)
{
    float scaleicon = 42.0f / kScale;
    if (kScale == 2 && kHeight < 500)
    {
        scaleicon = 14;
    }
    ImVec2 enemyiconPos = calMinimapPos(EnemyPos);
    if (MapType == 1) // minimap
    {
        if (index != -1)
        {
            DrawCircleHealthMiniMap(ImGui::GetForegroundDrawList(), enemyiconPos, EnemyHp, EnemyHpTotal, scaleicon / 2, 1.4f);
            DrawTextureFixed(ImGui::GetForegroundDrawList(), enemyiconPos, textures[index], scaleicon);
        }
    }
    else if (MapType == 2) // bigmap
    {
        if (index != -1)
        {
            DrawCircleHealthMiniMap(ImGui::GetForegroundDrawList(), enemyiconPos, EnemyHp, EnemyHpTotal, scaleicon, kScale); // Thay đổi ở đây
            DrawTextureFixed(ImGui::GetForegroundDrawList(), enemyiconPos, textures[index], 2 * scaleicon);
        }
    }
}
void DrawIconMapMonster(ImDrawList *draw, Vector3 EnemyPos, int EnemyHp, int ConfigID)
{
    ImVec2 enemyiconPos = calMinimapPos(EnemyPos);
    if (MapType == 1) // minimap
    {
        if (ConfigID == 7010 || ConfigID == 7011 || ConfigID == 7012 || ConfigID == 70093 || ConfigID == 70092 || ConfigID == 7024 || ConfigID == 7009)
            draw->AddCircleFilled(enemyiconPos, (float)kHeight / 150, ImColor(255, 0, 0));
        else
            draw->AddCircleFilled(enemyiconPos, (float)kHeight / 300, ImColor(255, 0, 0));
    }
    else if (MapType == 2) // bigmap
    {
        if (ConfigID == 7010 || ConfigID == 7011 || ConfigID == 7012 || ConfigID == 70093 || ConfigID == 70092 || ConfigID == 7024 || ConfigID == 7009)
            draw->AddCircleFilled(enemyiconPos, (float)kHeight / 70, ImColor(255, 0, 0));
        else
            draw->AddCircleFilled(enemyiconPos, (float)kHeight / 150, ImColor(255, 0, 0));
    }
}

struct BugSkillInfo
{
    int skillID;
    float rangeOrigin;
    float rangeFuture;
};

static inline BugSkillInfo GetEnemySkillRangeByID(int id)
{
    switch (id)
    {
    case 106:
        return {2, 6.99f, 8.79f}; // Krixi
    case 107:
        return {3, 6.40f, 7.00f}; // Zephys
    case 110:
        return {1, 7.98f, 8.88f}; // Kahli
    case 111:
        return {2, 8.99f, 10.79f}; // Violet
    case 118:
        return {1, 8.98f, 9.88f}; // Alice   (FIX skillID)
    case 119:
        return {1, 7.49f, 9.49f}; // Mganga
    case 123:
        return {3, 11.90f, 13.19f}; // Maloch
    case 124:
        return {2, 7.99f, 8.69f}; // Ignis
    case 127:
        return {1, 8.99f, 10.99f}; // Azzenka
    case 135:
        return {2, 3.49f, 7.69f}; // Thane
    case 137:
        return {3, 19.90f, 21.99f}; // Paine
    case 144:
        return {1, 6.40f, 8.00f}; // Taara
    case 146:
        return {2, 6.90f, 7.69f}; // Zill
    case 148:
        return {2, 7.98f, 8.75f}; // Preyta
    case 149:
        return {2, 5.90f, 6.49f}; // Xeniel
    case 150:
        return {1, 5.49f, 7.09f}; // Nakroth
    case 152:
        return {1, 7.98f, 8.68f}; // Điêu Thuyền (FIX skillID)
    case 156:
        return {2, 7.98f, 8.68f}; // Aleister
    case 162:
        return {3, 6.90f, 7.50f}; // Kriknak
    case 169:
        return {2, 5.90f, 6.39f}; // Slimz
    case 170:
        return {3, 7.50f, 8.18f}; // Moren
    case 171:
        return {2, 6.49f, 7.09f}; // Cresht
    case 173:
        return {3, 8.98f, 9.70f}; // Fennik
    case 177:
        return {2, 10.98f, 12.07f}; // Lindis
    case 187:
        return {2, 6.98f, 7.68f}; // Arum
    case 191:
        return {3, 8.00f, 8.50f}; // Rouie
    case 192:
        return {2, 8.99f, 9.79f}; // Celica
    case 503:
        return {3, 5.49f, 7.69f}; // Zuka
    case 510:
        return {1, 8.00f, 8.75f}; // Liliana
    case 519:
        return {1, 8.99f, 10.99f}; // Annette
    case 522:
        return {3, 8.00f, 10.40f}; // Enzo/Enrroll
    case 523:
        return {2, 8.99f, 10.99f}; // D'Arcy
    case 526:
        return {3, 7.90f, 8.60f}; // Ishar
    case 530:
        return {2, 10.40f, 11.50f}; // Dirak
    case 531:
        return {1, 4.90f, 7.09f}; // Keera
    case 534:
        return {2, 6.48f, 7.08f}; // Dextra
    case 535:
        return {2, 8.40f, 9.20f}; //
    case 536:
        return {1, 5.40f, 7.19f}; // Aoi
    case 539:
        return {1, 8.99f, 11.49f}; // Lorion
    case 541:
        return {2, 9.48f, 9.88f}; // Bonnie
    case 542:
        return {3, 7.90f, 8.80f}; // Tachi
    default:
        return {0, 0.f, 0.f};
    }
}

void DrawBugSkill(ImDrawList *draw)
{
    if (!BugSkillDistance || myPos == Vector3::zero() || MyHeroID == 0)
        return;

    BugSkillInfo info = GetEnemySkillRangeByID(MyHeroID);
    if (info.skillID < 1 || info.skillID > 3)
        return;

    // Chỉ xử lý khi slot đang chọn đúng slot bug
    if (SkillSlotType != info.skillID)
        return;

    void *skillSlotPtr = (SkillSlotType == 1 ? Req1 : (SkillSlotType == 2 ? Req2 : Req3));
    if (!skillSlotPtr)
        return;

    void *indicator = *(void **)((uintptr_t)skillSlotPtr + ActorLinkerOffField[7]);
    if (!indicator)
        return;

    void* ResSkillCfgInfo = *(void**)((uintptr_t)indicator + ActorLinkerOffField[22]);
    if (!ResSkillCfgInfo)
        return;
    if (ResSkillCfgInfo && BugSkillDistance)
    {
        float iGuideDistance = info.rangeFuture * 1000.0f;
        *(int*)((uintptr_t)ResSkillCfgInfo + ActorLinkerOffField[23]) = iGuideDistance;
        *(int*)((uintptr_t)ResSkillCfgInfo + ActorLinkerOffField[24]) = iGuideDistance;
    }

    const uintptr_t offUseOffset = (uintptr_t)indicator + ActorLinkerOffField[20];
    const uintptr_t offUseSkill = (uintptr_t)indicator + ActorLinkerOffField[21];

    Vector3 useOffset = *(Vector3 *)offUseOffset;

    float len2 = useOffset.x * useOffset.x + useOffset.z * useOffset.z;
    float r0 = info.rangeOrigin;
    float r1 = info.rangeFuture - debugDistanceSub;
    if (r1 < 0.f)
        r1 = 0.f;

    Vector3 newOffset = useOffset;
    float r0_sq = r0 * r0;

    if (len2 > r0_sq)
    {
        float len = sqrtf(len2);
        if (len > 1e-5f)
        {
            float scale = r1 / len;
            newOffset.x *= scale;
            newOffset.y *= scale;
            newOffset.z *= scale;
        }
    }

    Vector3 targetPos = myPos + newOffset;

    static Vector3 lastWrote = {FLT_MAX, FLT_MAX, FLT_MAX};
    Vector3 delta = targetPos - lastWrote;
    float diff2 = delta.x * delta.x + delta.z * delta.z;
    if (diff2 > 0.0001f)
    {
        *(Vector3 *)offUseSkill = targetPos;
        lastWrote = targetPos;
    }

    ImVec2 p0 = GetPlayerPosition(myPos);
    ImVec2 p1 = GetPlayerPosition(targetPos);
    
}

bool isMoving = false;
void (*_SkillButtonDown)(void *instance, void *formScript, int skillSlot, Vector2 downScreenPosition);
void SkillButtonDown(void *instance, void *formScript, int skillSlot, Vector2 downScreenPosition)
{
    if (myActorLinker != nullptr)
    {
        isMoving = *(bool *)((uintptr_t)myActorLinker + EspField[20]);
    }
    if (instance != nullptr && skillSlot == 2 && MyHeroID == 196 && CancelAnimationElsu && !isMoving)
    {
        Vector2 newPos = downScreenPosition;
        newPos.x += 100.0;
        newPos.y += 100.0;
        unhook_one_point(Skill[5]);
        _SkillButtonDown(instance, formScript, skillSlot, newPos);
        hook_one_point(Skill[5], (void *)SkillButtonDown);
    }
    unhook_one_point(Skill[5]);
    _SkillButtonDown(instance, formScript, skillSlot, downScreenPosition);
    hook_one_point(Skill[5], (void *)SkillButtonDown);
}


void Muabando()
{
    if (true)
    {
        if (CBattle_Instance != NULL && LBattleLogic != NULL)
        {

            if (ingame == false)
            {
                items = {
                    {1, EquipID::GiapHoiSinh, 2400, 1440, 0, 0, 0, -1, 0, true, 150},    // Giáp hồi sinh
                    {2, EquipID::CauBangSuong, 2200, 1320, 0, 0, 0, -1, 0, true, 75},    // Cầu băng sương
                    {3, EquipID::LiemDoatMenh, 2000, 1200, 0, 0, 0, -1, 0, true, 120},   // Liềm đoạt mệnh
                    {4, EquipID::ThuongKhungKiem, 2120, 1272, 0, 0, 0, -1, 0, true, 90}, // Thương khung kiếm
                    {5, EquipID::ThuanNhamThach, 1980, 1188, 0, 0, 0, -1, 0, true, 60},  //  thuẫn Nham thach
                    {6, EquipID::HerculesThinhNo, 2080, 1248, 0, 0, 0, -1, 0, true, 60}, // Hercules thịnh nộ
                    {7, EquipID::CungTaMa, 2250, 1350, 0, 0, 0, -1, 0, true, 60},        // huyết thương
                    {8, EquipID::XaNhatCung, 2000, 1200, 0, 0, 0, -1, 0, true, 60},      // Thiên hạ đại kiếm
                };
                solan = 0;
                lastId = -1;
            }
            else
            {

                void *actorManager = get_actorManager();
                if (actorManager == nullptr)
                    return;
                List<void **> *GetAllheros = *(List<void **> **)((uint64_t)actorManager + EspField[3]);
                if (GetAllheros == nullptr)
                    return;
                void *LGameActorMgr = *(void **)((uintptr_t)LBattleLogic + EspField[9]);
                if (!LGameActorMgr)
                    return;
                List<void **> *GetAllheros_Root = *(List<void **> **)((uint64_t)LGameActorMgr + EspField[10]);
                if (GetAllheros_Root == nullptr)
                    return;
                void ***actorLinkers = (void ***)GetAllheros->getItems();
                void ***LactorRoots = (void ***)GetAllheros_Root->getItems();
                void *myActorLinker = nullptr;
                void *myLactorRoot = nullptr;
                void *actorLinker = nullptr;
                void *LactorRoot = nullptr;
                for (int i = 0; i < GetAllheros->getSize(); i++)
                {
                    actorLinker = actorLinkers[(i * 2) + 1];
                    LactorRoot = LactorRoots[(i * 2) + 1];
                    if (ActorLinker_IsHostPlayer(actorLinker))
                    {

                        myActorLinker = actorLinker;
                        myLactorRoot = LactorRoot;
                        break;
                    }
                }
                if (myActorLinker != nullptr && myLactorRoot != nullptr)
                {
                    int currentTimer = 0;
                    void *LHeroWrapper = LActorRoot_LHeroWrapper(myLactorRoot);
                    if (LHeroWrapper)
                    {
                        void *CommunicateAgent = *(void **)((uintptr_t)LHeroWrapper + LActorRootOffField[10]);
                        if (CommunicateAgent)
                        {

                            currentTimer = GetGameTime(CommunicateAgent);
                        }
                    }
                    if (!myLactorRoot || !myActorLinker || !CBattle_Instance)
                        return;
                    void *SkillControl = *(void **)((uintptr_t)myLactorRoot + LActorRootOffField[4]);
                    void *EquipComponent = *(void **)((uint64_t)myLactorRoot + LActorRootOffField[2]);
                    void *EquipLinkerComp = *(void **)((uint64_t)myActorLinker + ActorLinkerOffField[4]);
                    void *CBattleEquipSystem = *(void **)((uint64_t)CBattle_Instance + EspField[22]);
                    if (EquipComponent != NULL && EquipLinkerComp != NULL && SkillControl != NULL && CBattleEquipSystem != NULL)
                        if (EquipComponent != NULL && EquipLinkerComp != NULL && SkillControl != NULL && CBattleEquipSystem != NULL)
                        {

                            void *TalentSystem = get_talentSystem(SkillControl);
                            if (TalentSystem != NULL)
                            {

                                int cdCauBangSuong = GetEquipActiveSkillCD(EquipLinkerComp, EquipID::CauBangSuong);       // get cooldown cầu băng sương
                                int cdThuanNhamThach = GetEquipActiveSkillCD(EquipLinkerComp, EquipID::ThuanNhamThach);   // get cooldown thuẫn nham thạch
                                int cdThuongKhungKiem = GetEquipActiveSkillCD(EquipLinkerComp, EquipID::ThuongKhungKiem); // get cooldown thương khung kiếm

                                int cdDaiDiaThanKhien = GetEquipActiveSkillCD(EquipLinkerComp, EquipID::DaiDiaThanKhien); // get cooldown đại địa thần khiên
                                int cdDaiDiaMaNhan = GetEquipActiveSkillCD(EquipLinkerComp, EquipID::DaiDiaMaNhan);       // get cooldown đại địa ma nhãn
                                int cdDaiDiaThanToc = GetEquipActiveSkillCD(EquipLinkerComp, EquipID::DaiDiaThanToc);     // get cooldown đại địa thần tốc
                                int cdDaiDiaMoTroi = GetEquipActiveSkillCD(EquipLinkerComp, EquipID::DaiDiaMoTroi);       // get cooldown đại địa mở trói
                                int cdDaiDiaHoiHuyet = GetEquipActiveSkillCD(EquipLinkerComp, EquipID::DaiDiaHoiHuyet);   // get cooldown đại địa hồi huyết

                                int cdLietHoaThanKhien = GetEquipActiveSkillCD(EquipLinkerComp, EquipID::LietHoaThanKhien); // get cooldown Liệt hỏa thần khiên
                                int cdLietHoaMaNhan = GetEquipActiveSkillCD(EquipLinkerComp, EquipID::LietHoaMaNhan);       // get cooldown Liệt hỏa ma nhãn
                                int cdLietHoaThanToc = GetEquipActiveSkillCD(EquipLinkerComp, EquipID::LietHoaThanToc);     // get cooldown Liệt hỏa thần tốc
                                int cdLietHoaMoTroi = GetEquipActiveSkillCD(EquipLinkerComp, EquipID::LietHoaMoTroi);       // get cooldown Liệt hỏa mở trói
                                int cdLietHoaHoiHuyet = GetEquipActiveSkillCD(EquipLinkerComp, EquipID::LietHoaHoiHuyet);   // get cooldown Liệt hỏa hồi huyết

                                int cdCungTaMa = GetEquipActiveSkillCD(EquipLinkerComp, EquipID::CungTaMa);     // get cooldown cung tà ma
                                int cdXaNhatCung = GetEquipActiveSkillCD(EquipLinkerComp, EquipID::XaNhatCung); // get cooldown Xạ nhật cung

                                int cdGiapHoiSinh = GetTalentCDTime(TalentSystem, 91337);     // get cooldown giáp hồi sinh
                                int cdLiemDoatMenh = GetTalentCDTime(TalentSystem, 911271);   // get cooldown giáp liềm đoạt mệnh
                                int cdHerculesThinhNo = GetTalentCDTime(TalentSystem, 91328); // get cooldown hercules thịnh nộ

                                int DaiDiaThanKhien_index = -1;
                                int DaiDiaMaNhan_index = -1;
                                int DaiDiaThanToc_index = -1;
                                int DaiDiaMoTroi_index = -1;
                                int DaiDiaHoiHuyet_index = -1;
                                int LietHoaThanKhien_index = -1;
                                int LietHoaMaNhan_index = -1;
                                int LietHoaThanToc_index = -1;
                                int LietHoaMoTroi_index = -1;
                                int LietHoaHoiHuyet_index = -1;
                                int CungTaMa_index = -1;
                                int XaNhatCung_index = -1;
                                auto ID = LEquipComponent_GetEquips(EquipComponent);
                                if (ID != NULL)
                                {

                                    memcpy(&ItemID[0], (void *)((uint64_t)ID + 0x20), sizeof(uint16_t));
                                    memcpy(&ItemID[1], (void *)((uint64_t)ID + 0x2C), sizeof(uint16_t));
                                    memcpy(&ItemID[2], (void *)((uint64_t)ID + 0x38), sizeof(uint16_t));
                                    memcpy(&ItemID[3], (void *)((uint64_t)ID + 0x44), sizeof(uint16_t));
                                    memcpy(&ItemID[4], (void *)((uint64_t)ID + 0x50), sizeof(uint16_t));
                                    memcpy(&ItemID[5], (void *)((uint64_t)ID + 0x5C), sizeof(uint16_t));
                                }
                                bool haveitem[8] = {false, false, false, false, false, false, false, false};
                                for (int i = 0; i < 6; i++)
                                {

                                    if (ItemID[i] == EquipID::GiapHoiSinh)
                                    {
                                        items[0].index = i;
                                        haveitem[0] = true;
                                        items[0].cdRemain = (int)ceil(cdGiapHoiSinh / 1000 - 1) > 0 ? (int)ceil(cdGiapHoiSinh / 1000 - 1) : 0;
                                        items[0].lastSold = currentTimer;
                                    }
                                    else if (ItemID[i] == EquipID::CauBangSuong)
                                    {
                                        items[1].index = i;
                                        haveitem[1] = true;
                                        items[1].cdRemain = (int)ceil(cdCauBangSuong / 1000 - 1) > 0 ? (int)ceil(cdCauBangSuong / 1000 - 1) : 0;
                                        items[1].lastSold = currentTimer;
                                    }
                                    else if (ItemID[i] == EquipID::LiemDoatMenh)
                                    {
                                        items[2].index = i;
                                        haveitem[2] = true;
                                        items[2].cdRemain = (int)ceil(cdLiemDoatMenh / 1000 - 1) > 0 ? (int)ceil(cdLiemDoatMenh / 1000 - 1) : 0;
                                        items[2].lastSold = currentTimer;
                                    }
                                    else if (ItemID[i] == EquipID::ThuongKhungKiem)
                                    {
                                        items[3].index = i;
                                        haveitem[3] = true;
                                        items[3].cdRemain = (int)ceil(cdThuongKhungKiem / 1000 - 1) > 0 ? (int)ceil(cdThuongKhungKiem / 1000 - 1) : 0;
                                        items[3].lastSold = currentTimer;
                                    }
                                    else if (ItemID[i] == EquipID::ThuanNhamThach)
                                    {
                                        items[4].index = i;
                                        haveitem[4] = true;
                                        items[4].cdRemain = (int)ceil(cdThuanNhamThach / 1000 - 1) > 0 ? (int)ceil(cdThuanNhamThach / 1000 - 1) : 0;
                                        items[4].lastSold = currentTimer;
                                    }
                                    else if (ItemID[i] == EquipID::HerculesThinhNo)
                                    {
                                        items[5].index = i;
                                        haveitem[5] = true;
                                        items[5].cdRemain = (int)ceil(cdHerculesThinhNo / 1000 - 1) > 0 ? (int)ceil(cdHerculesThinhNo / 1000 - 1) : 0;
                                        items[5].lastSold = currentTimer;
                                    }
                                    else if (ItemID[i] == EquipID::CungTaMa)
                                    {
                                        CungTaMa_index = i;
                                        items[6].index = i;
                                        haveitem[6] = true;
                                        items[6].cdRemain = max(0, (int)ceil(cdCungTaMa / 1000 - 1));
                                        items[6].lastSold = currentTimer;
                                    }
                                    else if (ItemID[i] == EquipID::XaNhatCung)
                                    {
                                        XaNhatCung_index = i;
                                        items[7].index = i;
                                        haveitem[7] = true;
                                        items[7].cdRemain = max(0, (int)ceil(cdXaNhatCung / 1000 - 1));
                                        items[7].lastSold = currentTimer;
                                    }
                                    else if (ItemID[i] == EquipID::DaiDiaThanKhien)
                                    {
                                        DaiDiaThanKhien_index = i;
                                    }
                                    else if (ItemID[i] == EquipID::DaiDiaMaNhan)
                                    {
                                        DaiDiaMaNhan_index = i;
                                    }
                                    else if (ItemID[i] == EquipID::DaiDiaThanToc)
                                    {
                                        DaiDiaThanToc_index = i;
                                    }
                                    else if (ItemID[i] == EquipID::DaiDiaMoTroi)
                                    {
                                        DaiDiaMoTroi_index = i;
                                    }
                                    else if (ItemID[i] == EquipID::DaiDiaHoiHuyet)
                                    {
                                        DaiDiaHoiHuyet_index = i;
                                    }
                                    else if (ItemID[i] == EquipID::LietHoaThanKhien)
                                    {
                                        LietHoaThanKhien_index = i;
                                    }
                                    else if (ItemID[i] == EquipID::LietHoaMaNhan)
                                    {
                                        LietHoaMaNhan_index = i;
                                    }
                                    else if (ItemID[i] == EquipID::LietHoaThanToc)
                                    {
                                        LietHoaThanToc_index = i;
                                    }
                                    else if (ItemID[i] == EquipID::LietHoaMoTroi)
                                    {
                                        LietHoaMoTroi_index = i;
                                    }
                                    else if (ItemID[i] == EquipID::LietHoaHoiHuyet)
                                    {
                                        LietHoaHoiHuyet_index = i;
                                    }
                                }
                                if (!haveitem[0])
                                {
                                    items[0].index = -1;
                                }
                                if (!haveitem[1])
                                {
                                    items[1].index = -1;
                                }
                                if (!haveitem[2])
                                {
                                    items[2].index = -1;
                                }
                                if (!haveitem[3])
                                {
                                    items[3].index = -1;
                                }
                                if (!haveitem[4])
                                {
                                    items[4].index = -1;
                                }
                                if (!haveitem[5])
                                {
                                    items[5].index = -1;
                                }
                                if (!haveitem[6])
                                {
                                    items[6].index = -1;
                                }
                                if (!haveitem[7])
                                {
                                    items[7].index = -1;
                                }
                                unordered_map<int, EquipSkill> equipSkillMap = {
                                    {EquipID::CauBangSuong, {EquipID::CauBangSuong, cdCauBangSuong, items[1].index}},
                                    {EquipID::ThuongKhungKiem, {EquipID::ThuongKhungKiem, cdThuongKhungKiem, items[3].index}},
                                    {EquipID::ThuanNhamThach, {EquipID::ThuanNhamThach, cdThuanNhamThach, items[4].index}},

                                    {EquipID::DaiDiaThanKhien, {EquipID::DaiDiaThanKhien, cdDaiDiaThanKhien, DaiDiaThanKhien_index}},
                                    {EquipID::DaiDiaMaNhan, {EquipID::DaiDiaMaNhan, cdDaiDiaMaNhan, DaiDiaMaNhan_index}},
                                    {EquipID::DaiDiaThanToc, {EquipID::DaiDiaThanToc, cdDaiDiaThanToc, DaiDiaThanToc_index}},
                                    {EquipID::DaiDiaMoTroi, {EquipID::DaiDiaMoTroi, cdDaiDiaMoTroi, DaiDiaMoTroi_index}},
                                    {EquipID::DaiDiaHoiHuyet, {EquipID::DaiDiaHoiHuyet, cdDaiDiaHoiHuyet, DaiDiaHoiHuyet_index}},

                                    {EquipID::LietHoaThanKhien, {EquipID::LietHoaThanKhien, cdLietHoaThanKhien, LietHoaThanKhien_index}},
                                    {EquipID::LietHoaMaNhan, {EquipID::LietHoaMaNhan, cdLietHoaMaNhan, LietHoaMaNhan_index}},
                                    {EquipID::LietHoaThanToc, {EquipID::LietHoaThanToc, cdLietHoaThanToc, LietHoaThanToc_index}},
                                    {EquipID::LietHoaMoTroi, {EquipID::LietHoaMoTroi, cdLietHoaMoTroi, LietHoaMoTroi_index}},
                                    {EquipID::LietHoaHoiHuyet, {EquipID::LietHoaHoiHuyet, cdLietHoaHoiHuyet, LietHoaHoiHuyet_index}},

                                    {EquipID::CungTaMa, {EquipID::CungTaMa, cdCungTaMa, CungTaMa_index}},
                                    {EquipID::XaNhatCung, {EquipID::XaNhatCung, cdXaNhatCung, XaNhatCung_index}},
                                };
                                int goldcoin = 0;
                                void *ValuePropertyComponent = *(void **)((uint64_t)myLactorRoot + LActorRootOffField[0]);
                                if (ValuePropertyComponent)
                                {
                                    goldcoin = GetGoldCoinInBattle(ValuePropertyComponent);
                                }
                                bool check6 = false;
                                if (fullslot)
                                {
                                    for (int i = 0; i < 6; i++)
                                    {
                                        if (ItemID[i] == 0)
                                        {
                                            check6 = true;
                                            break;
                                        }
                                    }
                                }
                                if (muaitem && !check6)
                                {
                                    auto selectedItems = BuildSelectedItemsVector(items, itemDisplayOrder, itemEnabled);
                                    static int itembuy = 0;
                                    bool isbuyed = false;
                                    for (auto &owned : selectedItems)
                                    {
                                        if (isbuyed)
                                            break;
                                        if (owned.index == -1)
                                            continue;
                                        // if(items[i].id == itemsold) break;
                                        if (currentTimer - owned.lastSold >= owned.cdRemain)
                                            continue;
                                        if (owned.cdRemain + 4 <= owned.cdmax && checktime)
                                            continue;

                                        for (auto &item : selectedItems)
                                        {
                                            if (isbuyed)
                                                break;
                                            if (solan > 1 && item.id == EquipID::GiapHoiSinh)
                                                continue;
                                            if (item.index != -1)
                                                continue;
                                            if (currentTimer - item.lastSold < item.cdRemain)
                                                continue;
                                            if (currentTimer - item.lastbuy < 1)
                                                continue;

                                            int totalGold = goldcoin + owned.sellPrice;
                                            if (totalGold < item.cost)
                                                continue;
                                            SendSellEquipFrameCommand(CBattleEquipSystem, owned.index);
                                            owned.cd = currentTimer;
                                            switch (owned.stt)
                                            {
                                            case 1:
                                                owned.cdRemain = max(0, (int)ceil(cdGiapHoiSinh / 1000 - 1));
                                                solan++;
                                                break;
                                            case 2:
                                                owned.cdRemain = max(0, (int)ceil(cdCauBangSuong / 1000 - 1));
                                                break;
                                            case 3:
                                                owned.cdRemain = max(0, (int)ceil(cdLiemDoatMenh / 1000 - 1));
                                                break;
                                            case 4:
                                                owned.cdRemain = max(0, (int)ceil(cdThuongKhungKiem / 1000 - 1));
                                                break;
                                            case 5:
                                                owned.cdRemain = max(0, (int)ceil(cdThuanNhamThach / 1000 - 1));
                                                break;
                                            case 6:
                                                owned.cdRemain = max(0, (int)ceil(cdHerculesThinhNo / 1000 - 1));
                                                break;
                                            case 7:
                                                owned.cdRemain = max(0, (int)ceil(cdCungTaMa / 1000 - 1));
                                                break;
                                            case 8:
                                                owned.cdRemain = max(0, (int)ceil(cdXaNhatCung / 1000 - 1));
                                                break;
                                            }
                                            owned.lastSold = currentTimer;
                                            owned.index = -1;
                                            for (auto &realItem : items)
                                            {
                                                if (realItem.id == owned.id)
                                                {
                                                    realItem.cd = currentTimer;
                                                    realItem.cdRemain = owned.cdRemain;
                                                    realItem.lastSold = currentTimer;
                                                    realItem.index = -1;
                                                    break;
                                                }
                                            }
                                            // Mua món mới
                                            itembuy = item.id;
                                            timer(0.15)
                                            {
                                                SendBuyEquipFrameCommand(CBattleEquipSystem, itembuy, false);
                                                for (auto &realItem : items)
                                                {
                                                    if (realItem.id == itembuy)
                                                    {
                                                        realItem.lastbuy = currentTimer;
                                                        realItem.cdRemain = 0;
                                                        break;
                                                    }
                                                }
                                            });
                                            goldcoin = totalGold - item.cost;
                                            isbuyed = true;
                                            break;
                                        }
                                    }
                                }
                                if (doiitem)
                                {
                                    vector<EquipSkill> validEquipSkills;
                                    for (const auto &entry : equipSkillMap)
                                    {
                                        const EquipSkill &equipSkill = entry.second;
                                        if (equipSkill.index != -1 && equipSkill.cooldown == 0)
                                        {
                                            validEquipSkills.push_back(equipSkill);
                                        }
                                    }
                                    sort(validEquipSkills.begin(), validEquipSkills.end(), [](const EquipSkill &a, const EquipSkill &b)
                                         { return a.index < b.index; });
                                    if (!validEquipSkills.empty() && lastId != validEquipSkills[0].id)
                                    {
                                        SendPlayerChoseEquipSkillCommand(CBattleEquipSystem, validEquipSkills[0].index);
                                        lastId = validEquipSkills[0].id;
                                    }
                                }
                            }
                        }
                }
            }
        }
    }
}

// ========== Singleton GetInstance (thay thế Il2CppGetSingleton) ==========
static uint64_t Moudule_Base = 0;
typedef void* (*t_Singleton_GetInstance)(void* methodInfo);

static inline uintptr_t GetGameModule_Base(const char* moduleName) {
    uint32_t count = _dyld_image_count();
    for (uint32_t i = 0; i < count; i++) {
        const char* name = _dyld_get_image_name(i);
        if (name && strstr(name, moduleName)) {
            return (uintptr_t)_dyld_get_image_header(i);
        }
    }
    return (uintptr_t)_dyld_get_image_header(0);
}

void SetUpBase() {
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        Moudule_Base = GetGameModule_Base("UnityFramework");
    });
}

static inline void* GetCHeroSelectBaseSystemInstance(uint64_t MoudleBase) {
    auto GetInstance = (t_Singleton_GetInstance)(MoudleBase + OFF_Singleton_get_instance);
    void* methodInfo = *(void**)(MoudleBase + OFF_Method_Singleton_CHeroSelectBaseSystem_GetInstance);
    if (methodInfo == nullptr) return nullptr;
    return GetInstance(methodInfo);
}

static inline void* GetCHeroSelectNormalSystemInstance(uint64_t MoudleBase) {
    auto GetInstance = (t_Singleton_GetInstance)(MoudleBase + OFF_Singleton_get_instance);
    void* methodInfo = *(void**)(MoudleBase + OFF_Method_Singleton_CHeroSelectNormalSystem_GetInstance);
    if (methodInfo == nullptr) return nullptr;
    return GetInstance(methodInfo);
}

static inline void* GetCRoleInfoManagerInstance(uint64_t MoudleBase) {
    auto GetInstance = (t_Singleton_GetInstance)(MoudleBase + OFF_Singleton_get_instance);
    void* methodInfo = *(void**)(MoudleBase + OFF_Method_Singleton_CRoleInfoManager_GetInstance);
    if (methodInfo == nullptr) return nullptr;
    return GetInstance(methodInfo);
}

static inline void* GetCLadderSystemInstance(uint64_t MoudleBase) {
    auto GetInstance = (t_Singleton_GetInstance)(MoudleBase + OFF_Singleton_get_instance);
    void* methodInfo = *(void**)(MoudleBase + OFF_Method_Singleton_CLadderSystem_GetInstance);
    if (methodInfo == nullptr) return nullptr;
    return GetInstance(methodInfo);
}

static inline void* GetCBattleSystemInstance(uint64_t MoudleBase) {
    auto GetInstance = (t_Singleton_GetInstance)(MoudleBase + OFF_Singleton_get_instance);
    void* methodInfo = *(void**)(MoudleBase + OFF_Method_Singleton_CBattleSystem_GetInstance);
    if (methodInfo == nullptr) return nullptr;
    return GetInstance(methodInfo);
}

static inline void* GetGameFrameworkInstance(uint64_t MoudleBase) {
    auto GetInstance = (t_Singleton_GetInstance)(MoudleBase + OFF_MonoSingleton_get_instance);
    void* methodInfo = *(void**)(MoudleBase + OFF_Method_MonoSingleton_GameFramework_GetInstance);
    if (methodInfo == nullptr) return nullptr;
    return GetInstance(methodInfo);
}

static inline void* GetLLogicCoreInstance(uint64_t MoudleBase) {
    auto GetInstance = (t_Singleton_GetInstance)(MoudleBase + OFF_Singleton_get_instance);
    void* methodInfo = *(void**)(MoudleBase + OFF_Method_Singleton_LLogicCore_get_instance);
    if (methodInfo == nullptr) return nullptr;
    return GetInstance(methodInfo);
}

static inline void* GetBattleLogicInstance(uint64_t MoudleBase) {
    auto GetInstance = (t_Singleton_GetInstance)(MoudleBase + OFF_Singleton_get_instance);
    void* methodInfo = *(void**)(MoudleBase + OFF_Method_Singleton_BattleLogic_GetInstance);
    if (methodInfo == nullptr) return nullptr;
    return GetInstance(methodInfo);
}

static inline void* GetCameraSystemInstance(uint64_t MoudleBase) {
    auto GetInstance = (t_Singleton_GetInstance)(MoudleBase + OFF_MonoSingleton_get_instance);
    void* methodInfo = *(void**)(MoudleBase + OFF_Method_MonoSingleton_CameraSystem_GetInstance);
    if (methodInfo == nullptr) return nullptr;
    return GetInstance(methodInfo);
}
// =========================================================================

void DrawESP(ImDrawList *draw)
{

    int numberOfEnemies = 0;

    if (daloadoffset == false)
        return;
    SetUpBase();
    if (ManualMinimap && MenDeal)
    {
        ImVec2 topLeft(MinimapX - MinimapSizeX / 2, MinimapY - MinimapSizeY / 2);
        ImVec2 bottomRight(MinimapX + MinimapSizeX / 2, MinimapY + MinimapSizeY / 2);

        draw->AddRect(topLeft, bottomRight, IM_COL32(255, 255, 255, 255), 0.0f, 0, 2.0f);
    }

    void *CHeroSelectBaseSystem_Instance = GetCHeroSelectBaseSystemInstance(Moudule_Base);
    if (CHeroSelectBaseSystem_Instance)
    {
        m_isInHeroSelectState = *(bool *)((uintptr_t)CHeroSelectBaseSystem_Instance + ModSkinOffField[5]);
        if (m_isInHeroSelectState)
        {
            if (unlockskin)
            {
                if (!isHookedSkin && !Hacksaoenable)
                {
                    hook_no_org();
                }
            }
           
            if(Hacksaoenable)
            {
                unhook_one_point(Antiban[4]);
                unhook_one_point(Antiban[5]);
                unhook_one_point(Antiban[6]);
                Hacksaoenable = false;
            }
        }
    }
    if (!unlockskin)
    {
        if (isHookedSkin)
        {
            un_hook_no_org();
        }
    }

    void *CHeroSelectNormalSystem_Instance = GetCHeroSelectNormalSystemInstance(Moudule_Base);
    if (CHeroSelectNormalSystem_Instance)
    {
        void *HeroSelectNormalWindow = *(void **)((uintptr_t)CHeroSelectNormalSystem_Instance + ModSkinOffField[2]);
        if (HeroSelectNormalWindow)
        {
            if (unlockskin && isHookedSkin)
            {
                RefreshHeroPanel(HeroSelectNormalWindow, true, true, true);
            }
        }
    }
    if (fakerank)
    {
        if (CRoleInfoManager_Instance == nullptr)
        {
            CRoleInfoManager_Instance = GetCRoleInfoManagerInstance(Moudule_Base);
        }
        if (CRoleInfoManager_Instance)
        {
            void *MasterRoleInfo = GetMasterRoleInfo(CRoleInfoManager_Instance);
            if (MasterRoleInfo)
            {
                if (fakerank)
                {
                    //*(MonoString**)((uintptr_t)MasterRoleInfo + ModRankOffField[9]) = (MonoString*)CreateMonoString("Không Biết");
                    *(int *)((uintptr_t)MasterRoleInfo + ModRankOffField[0]) = sosao; // số lượng sao
                    *(int *)((uintptr_t)MasterRoleInfo + ModRankOffField[1]) = sosao;
                    *(uint8_t *)((uintptr_t)MasterRoleInfo + ModRankOffField[2]) = rankht; // rank hiện tại
                    *(uint8_t *)((uintptr_t)MasterRoleInfo + ModRankOffField[3]) = rankht; // rank lịch sử cao nhất
                    *(uint8_t *)((uintptr_t)MasterRoleInfo + ModRankOffField[4]) = rankht; // rank mùa này cao nhất
                    *(int *)((uintptr_t)MasterRoleInfo + ModRankOffField[5]) = dauan;         // số lượng mùa cao thủ trở lên
                    *(int *)((uintptr_t)MasterRoleInfo + ModRankOffField[6]) = topnumber;  // top thách đấu
                    *(int *)((uintptr_t)MasterRoleInfo + ModRankOffField[7]) = topnumber;  // top thách đấu
                    *(int *)((uintptr_t)MasterRoleInfo + ModRankOffField[8]) = topnumber;  // top thách đấu
                    *(int *)((uintptr_t)MasterRoleInfo + ModRankOffField[12]) = 10;  // vip level
                }
            }
        }
        void *CLadderSystem_Instance = GetCLadderSystemInstance(Moudule_Base);
        if (CLadderSystem_Instance)
        {
            void *COMDT_RANKDETAIL = *(void **)((uintptr_t)CLadderSystem_Instance + ModRankOffField[10]);
            if (COMDT_RANKDETAIL)
            {
                *(int *)((uintptr_t)COMDT_RANKDETAIL + ModRankOffField[11]) = sosao;
            }
        }
    }
    int playerID = 0;
    void *VHostLogic = get_VHostLogic();
    if (VHostLogic != nullptr)
    {
        playerID = *(int *)((uintptr_t)VHostLogic + EspField[13]);
    }
    void *playerCenter = get_playerCenter();
    if (playerCenter != nullptr)
    {
        void *listplayer = *(void **)((uintptr_t)playerCenter + EspField[0]);
        if (listplayer != nullptr)
        {
            List<void **> *GetAllPlayers = *(List<void **> **)((uint64_t)listplayer + EspField[1]);
            if (GetAllPlayers != nullptr)
            {
                for (int i = 0; i < GetAllPlayers->getSize(); i++)
                {
                    void *playerbase = GetAllPlayers->getItems()[i];
                    if (playerbase != nullptr)
                    {
                        int playbaseID = *(int *)((uintptr_t)playerbase + EspField[1]);
                        if (playbaseID == playerID)
                        {
                            if (unlocktb)
                            {
                                *(int *)((uintptr_t)playerbase + EspField[2]) = BillBoard_ID;
                            }
                            if (unlockbt) {
                            *(int*)((uintptr_t)playerbase + ModSkinOffField[6]) = personalButtonID; // public int personalButtonID; list 2
                                }

                                if (SoldierSkinID != 0) {
                                    *(int*)((uintptr_t)playerbase + ModSkinOffField[7]) = SoldierSkinID;
                                }
                        }
                    }
                }
            }
        }
    }
    void *mainCamera = get_main();
    if (mainCamera != nullptr)
    {
        if (!CBattle_Instance)
            CBattle_Instance = GetCBattleSystemInstance(Moudule_Base);
        if (CBattle_Instance)
        {
            ingame = *(bool *)((uint64_t)CBattle_Instance + EspField[15]);
        }
        if (!ingame)
        {
            CBattle_Instance = nullptr;
            LLogicCore_Instance = nullptr;
            LBattleLogic = nullptr;
            LGameActorMgr_Instance = nullptr;
            GameInput_Instance = nullptr;
            BattleLogic_Instance = nullptr;
            myActorLinker = nullptr;
            myLactorRoot = nullptr;
            isFirst = true;
            isFirstrun = true;
            CeaserOnly = false;
            currentTimer = 0;
            EnemyTarget1.Ranger = 0.0f;
            EnemyTarget1.bullettime = 0.0f;
            EnemyTarget2.Ranger = 0.0f;
            EnemyTarget2.bullettime = 0.0f;
            EnemyTarget3.Ranger = 0.0f;
            EnemyTarget3.bullettime = 0.0f;
            MyHeroID = 0;
            myPos = Vector3::zero();
            items.clear();
            solan = 0;
            lastId = -1;
            muaitem = false;
            doiitem = false;
            fullslot = false;
            checktime = false;

            if (hookaim)
            {
                unhook_one_point(Esp[37]); 
                unhook_one_point(Esp[38]);
                hookaim = false;
            }
            if (hookcamera)
            {
                unhook_one_point(offset[4]);
                hookcamera = false;
            }
            if (hookcancel)
            {
                unhook_one_point(Skill[5]);
                hookcancel = false;
            }
            
            if (!hooklsd)
            {
                hook_one_point(offset[11], (void*)_get_IsHostProfile);
                hooklsd = true;
            }

            previousEnemyPositions.clear();
            return;
        }
        if (ingame)
        {
            if (hooklsd)
            {
                unhook_one_point(offset[11]);
                hooklsd = false;
            }
            void *MinimapSys = get_TheMinimapSys(CBattle_Instance);
            void *GameFramework_Instance = GetGameFrameworkInstance(Moudule_Base);
            if (GameFramework_Instance)
            {
                settingmode = *(int *)((uintptr_t)GameFramework_Instance + MinimapOffField[6]);
            }
            if (MinimapSys != NULL)
            {
                void *CMapTransferData = *(void **)((uintptr_t)MinimapSys + MinimapOffField[0]);
                if (CMapTransferData)
                {
                    MapType = *(int *)((uintptr_t)MinimapSys + MinimapOffField[1]);
                    Vector2 mmFinalScreenSize = *(Vector2 *)((uintptr_t)CMapTransferData + MinimapOffField[2]);
                    Vector2 mmFinalScreenPos = *(Vector2 *)((uintptr_t)CMapTransferData + MinimapOffField[3]);
                    MinimapPos = mmFinalScreenPos;
                    MinimapSizeImGUi = mmFinalScreenSize;
                    if (isFirst)
                    {
                        MinimapOrg = mmFinalScreenPos;
                        isFirst = false;
                    }
                    Vector2 bmFinalScreenPos = *(Vector2 *)((uintptr_t)CMapTransferData + MinimapOffField[4]);
                    Vector2 bmFinalScreenSize = *(Vector2 *)((uintptr_t)CMapTransferData + MinimapOffField[5]);
                    BigmapPos = bmFinalScreenPos;
                    BigmapSizeImGUi = bmFinalScreenSize;
                    float newScale = FindScaleConfig(kScale, kHeight, kWidth);
                    if (mmFinalScreenPos.x > 0)
                    {
                        MinimapScale = MinimapOrg.x / mmFinalScreenPos.x;
                        if (settingmode > 0)
                        {
                            MinimapSize = mmFinalScreenSize / kScale;
                            BigmapSize = bmFinalScreenSize / kScale;
                            MinimapCenterX = mmFinalScreenPos.x * MinimapScale / kScale;
                            MinimapCenterY = kHeight - mmFinalScreenPos.y * MinimapScale / kScale;
                            BigmapCenterX = bmFinalScreenPos.x * MinimapScale / kScale;
                            BigmapCenterY = kHeight - bmFinalScreenPos.y * MinimapScale / kScale;
                            if (!ManualMinimap)
                            {
                                MinimapX = MinimapCenterX;
                                MinimapY = MinimapCenterY;
                                MinimapSizeX = MinimapSize.x;
                                MinimapSizeY = MinimapSize.y;
                            }
                        }
                        else
                        {
                            MinimapSize = mmFinalScreenSize / newScale;
                            BigmapSize = bmFinalScreenSize / newScale;
                            MinimapCenterX = mmFinalScreenPos.x / newScale;
                            MinimapCenterY = kHeight - mmFinalScreenPos.y / newScale;
                            BigmapCenterX = bmFinalScreenPos.x / newScale;
                            BigmapCenterY = kHeight - bmFinalScreenPos.y / newScale;
                            if (!ManualMinimap)
                            {
                                MinimapX = MinimapCenterX;
                                MinimapY = MinimapCenterY;
                                MinimapSizeX = MinimapSize.x;
                                MinimapSizeY = MinimapSize.y;
                            }
                        }
                    }
                }
            }
            if (isHookedSkin)
            {
                un_hook_no_org();
            }
        }
        ImVec2 MyposScreen = ImVec2(0, 0);
        void *actorManager = get_actorManager();
        if (actorManager == nullptr)
            return;
        List<void **> *GetAllheros = *(List<void **> **)((uint64_t)actorManager + EspField[3]);
        if (GetAllheros == nullptr)
            return;
        if (!LLogicCore_Instance)
            LLogicCore_Instance = GetLLogicCoreInstance(Moudule_Base);
        if (LLogicCore_Instance == nullptr)
            return;
        void *LDeskBase_Listview = *(void **)((uintptr_t)LLogicCore_Instance + EspField[7]);
        if (LDeskBase_Listview && LGameActorMgr_Instance == nullptr)
        {
            List<void **> *List_LDeskBase = *(List<void **> **)((uint64_t)LDeskBase_Listview + EspField[23]);
            if (List_LDeskBase != nullptr)
            {
                for (int i = 0; i < List_LDeskBase->getSize(); i++)
                {
                    void *LDeskBase = List_LDeskBase->getItems()[i];
                    if (LDeskBase != nullptr)
                    {
                        LBattleLogic = *(void **)((uintptr_t)LDeskBase + EspField[8]);
                        if (LBattleLogic)
                        {
                            void *LGameActorMgr = *(void **)((uintptr_t)LBattleLogic + EspField[9]);
                            if (LGameActorMgr)
                            {
                                LGameActorMgr_Instance = LGameActorMgr;
                            }
                        }
                    }
                }
            }
        }
        if (LGameActorMgr_Instance == nullptr)
            return;
        List<void **> *GetAllheros_Root = *(List<void **> **)((uint64_t)LGameActorMgr_Instance + EspField[10]);
        if (GetAllheros_Root == nullptr || GetAllheros_Root->getSize() == 0)
            return;
        if (!BattleLogic_Instance)
            BattleLogic_Instance = GetBattleLogicInstance(Moudule_Base);
        if (BattleLogic_Instance)
        {
            void *SLevelContext = GetCurLvelContext(BattleLogic_Instance);
            if (SLevelContext)
            {
                roomtype = GetGameRoomType(SLevelContext);
            }
        }
        void ***actorLinkers = (void ***)GetAllheros->getItems();
        void ***LactorRoots = (void ***)GetAllheros_Root->getItems();
        if (!actorLinkers || !LactorRoots)
            return;
        if (myLactorRoot)
        {
            void *LHeroWrapper = LActorRoot_LHeroWrapper(myLactorRoot);
            if (LHeroWrapper)
            {
                void *CommunicateAgent = *(void **)((uintptr_t)LHeroWrapper + LActorRootOffField[10]);
                if (CommunicateAgent)
                {
                    currentTimer = GetGameTime(CommunicateAgent);
                    if (currentTimer > 870) // 14p30
                    {
                        CeaserOnly = true;
                    }
                }
            }
        }
        if (myActorLinker != NULL)
        {
            if (AimbotEnable && Aimhook)
            {
                if (!hookaim)
                {
                    hook_one_point(Esp[37], (void *)_GetUseSkillPosition);
                    hook_one_point(Esp[38], (void *)_GetUseSkillDirection);
                    hookaim = true;
                }
            }
            else
            {
                if (hookaim)
                {
                    unhook_one_point(Esp[37]);
                    unhook_one_point(Esp[38]);
                    hookaim = false;
                }
            }

            if (CancelAnimationElsu)
            {
                if (!hookcancel)
                {
                    hook_one_point(Skill[5], (void *)SkillButtonDown);
                    hookcancel = true;
                }
            }
            else
            {
                if (hookcancel)
                {
                    unhook_one_point(Skill[5]);
                    hookcancel = false;
                }
            }

            if (HackSao)
            {
                if (!Hacksaoenable)
                {
                    hook_one_point(Antiban[4], (void *)_CreateReportData);
                    hook_one_point(Antiban[5], (void *)_CreateDestroyReportData);
                    hook_one_point(Antiban[6], (void *)_HandleGameSettle);
                    Hacksaoenable = true;
                }
            }
            else
            {
                if (Hacksaoenable)
                {
                    unhook_one_point(Antiban[4]);
                    unhook_one_point(Antiban[5]);
                    unhook_one_point(Antiban[6]);
                    Hacksaoenable = false;
                }
            }

            if (SliderCamera && currentTimer > 0)
            {
                if (!hookcamera)
                {
                    hook_one_point(offset[4], (void *)_GetZoomRate);
                    hookcamera = true;
                }
                if (hookcamera)
                {
                    void *CameraSystem_Instance = GetCameraSystemInstance(Moudule_Base);
                    if (CameraSystem_Instance)
                    {
                        OnCameraHeightChanged(CameraSystem_Instance);
                    }
                }
            }
            else
            {
                if (hookcamera)
                {
                    unhook_one_point(offset[4]);
                    hookcamera = false;
                }
            }
            int *skillCooldowns = SkillControlAll(myActorLinker);
            if (!skillCooldowns)
                return;
            myPos = ActorLinker_getPosition(myActorLinker);
            MyposScreen = GetPlayerPosition(myPos);
            void *skillcomponent = *(void **)((uint64_t)myActorLinker + ActorLinkerOffField[5]);
            if (skillcomponent != NULL)
            {
                void *skillslotArray = *(void **)((uint64_t)skillcomponent + ActorLinkerOffField[6]);
                if (!skillslotArray)
                {
                    return;
                }
                if (skillslotArray)
                {
                    int maxslot = *(int *)((uint64_t)skillslotArray + 0x18); // số lượng skillslot
                    if (maxslot > 9)
                    {
                        Req0 = *(void **)((uint64_t)skillslotArray + 0x20);      // đánh thường
                        Req1 = *(void **)((uint64_t)skillslotArray + 0x20 + 8);  // skill 1
                        Req2 = *(void **)((uint64_t)skillslotArray + 0x20 + 16); // skill 2
                        Req3 = *(void **)((uint64_t)skillslotArray + 0x20 + 24); // ultimate
                        Req5 = *(void **)((uint64_t)skillslotArray + 0x20 + 40); // bổ trợ
                        Req9 = *(void **)((uint64_t)skillslotArray + 0x20 + 72); // đồ
                        if (!Req1 || !Req2 || !Req3)
                            return;
                        void *skillControl1 = *(void **)((uintptr_t)Req1 + ActorLinkerOffField[7]);
                        void *skillControl2 = *(void **)((uintptr_t)Req2 + ActorLinkerOffField[7]);
                        void *skillControl3 = *(void **)((uintptr_t)Req3 + ActorLinkerOffField[7]);
                        if (!skillControl1 || !skillControl2 || !skillControl3)
                            return;
                        RangeSkill1auto = *(int *)((uintptr_t)skillControl1 + ActorLinkerOffField[8]);
                        RangeSkill2auto = *(int *)((uintptr_t)skillControl2 + ActorLinkerOffField[8]);
                        RangeSkill3auto = *(int *)((uintptr_t)skillControl3 + ActorLinkerOffField[8]);
                        useSkillDirection1 = *(Vector3 *)((uintptr_t)skillControl1 + ActorLinkerOffField[9]);
                        useSkillDirection2 = *(Vector3 *)((uintptr_t)skillControl2 + ActorLinkerOffField[9]);
                        useSkillDirection3 = *(Vector3 *)((uintptr_t)skillControl3 + ActorLinkerOffField[9]);
                    }
                }
                if (BugSkillDistance)
                {
                    DrawBugSkill(draw);
                }
            }
        }
        int index = 0;
        int lowestHp1 = 1000000000;
        int lowestHp12 = 1000000000;
        float lowestHpPercent1 = 1000000000;
        float closestEnemyDistance1 = 1000000000;
        float closestEnemyDistanceView1 = 1000000000;
        int lowestHp2 = 1000000000;
        int lowestHp22 = 1000000000;
        float lowestHpPercent2 = 1000000000;
        float closestEnemyDistance2 = 1000000000;
        float closestEnemyDistanceView2 = 1000000000;
        int lowestHp3 = 1000000000;
        int lowestHp32 = 1000000000;
        float lowestHpPercent3 = 1000000000;
        float closestEnemyDistance3 = 1000000000;
        float closestEnemyDistanceView3 = 1000000000;
        void *Entity1 = NULL;
        void *Entity2 = NULL;
        void *Entity3 = NULL;
        EnemyTarget1.bullettime = 0;
        EnemyTarget2.bullettime = 0;
        EnemyTarget3.bullettime = 0;
        EnemyTarget1.ConfigID = 0;
        EnemyTarget2.ConfigID = 0;
        EnemyTarget3.ConfigID = 0;
        EnemyTarget1.myPos = myPos;
        EnemyTarget2.myPos = myPos;
        EnemyTarget3.myPos = myPos;
        for (int i = 0; i < GetAllheros->getSize(); i++)
        {
            void *actorLinker = actorLinkers[(i * 2) + 1];
            void *LactorRoot = LactorRoots[(i * 2) + 1];
            if (!actorLinker || !LactorRoot)
                continue;
            void *ValuePropertyComponent = *(void **)((uint64_t)LactorRoot + LActorRootOffField[0]);
            void *LObjWrapper = *(void **)((uint64_t)LactorRoot + LActorRootOffField[1]);
            void *ObjLinker = *(void **)((uintptr_t)actorLinker + ActorLinkerOffField[3]);
            if (!ObjLinker)
                continue;
            int sheroID = *(int *)((uintptr_t)ObjLinker + ActorLinkerOffField[11]);
            HeroData heroData = findHeroById(sheroID);
            if (ActorLinker_IsHostPlayer(actorLinker))
            {
                myActorLinker = actorLinker;
                myLactorRoot = LactorRoot;
                MyHeroID = sheroID;
            }
            if (myActorLinker != NULL)
            {
                void *HudControl = *(void **)((uintptr_t)actorLinker + ActorLinkerOffField[1]);
                if (!HudControl)
                    continue;
                if (ChangeName)
                {
                    if (NameMode == 0) // tên gốc
                    {

                        void *playerCenter = get_playerCenter();
                        if (playerCenter != nullptr)
                        {
                            void *listplayer = *(void **)((uintptr_t)playerCenter + EspField[0]);
                            if (listplayer != nullptr)
                            {
                                List<void **> *GetAllPlayers = *(List<void **> **)((uint64_t)listplayer + EspField[1]);
                                if (GetAllPlayers != nullptr && GetAllPlayers->getSize() > i)
                                {
                                    void ***playerItems = GetAllPlayers->getItems();
                                    if (!playerItems)
                                        continue;
                                    void *playerbase = playerItems[i];
                                    if (playerbase != nullptr)
                                    {
                                        MonoString *orgName = *(MonoString **)((uint64_t)playerbase + EspField[12]);
                                        SetPlayerName(HudControl, orgName, (MonoString *)CreateMonoString(""), false, (MonoString *)CreateMonoString(""));
                                    }
                                }
                            }
                        }
                    }

                    if (NameMode == 1) // tên cooldown
                    {
                        int *skillCooldowns = SkillControlAll(actorLinker);
                        if (!skillCooldowns)
                            continue;
                        int cd1 = skillCooldowns[0];
                        int cd2 = skillCooldowns[1];
                        int cd3 = skillCooldowns[2];
                        int cd4 = skillCooldowns[3];
                        string sk1, sk2, sk3, sk4;
                        sk1 = (cd1 == 0) ? " [0] " : " [" + to_string(cd1) + "] ";
                        sk2 = (cd2 == 0) ? " [0]" : " [" + to_string(cd2) + "] ";
                        sk3 = (cd3 == 0) ? " [0] " : " [" + to_string(cd3) + "] ";
                        sk4 = (cd4 == 0) ? " [0] " : " [" + to_string(cd4) + "] ";
                        string ShowSkill = sk1 + sk2 + sk3;
                        string ShowSkill2 = sk4;
                        const char *str1 = ShowSkill.c_str();
                        const char *str2 = ShowSkill2.c_str();
                        MonoString *playerName = (MonoString *)CreateMonoString(str1);
                        MonoString *prefixName = (MonoString *)CreateMonoString(str2);
                        SetPlayerName(HudControl, playerName, prefixName, false, (MonoString *)CreateMonoString(""));
                    }
                    if (NameMode == 2) // all tên tùy chọn
                    {
                        MonoString *playerName = (MonoString *)CreateMonoString(customname.c_str());
                        MonoString *prefixName = (MonoString *)CreateMonoString("");
                        SetPlayerName(HudControl, playerName, prefixName, false, (MonoString *)CreateMonoString(""));
                    }
                    if (NameMode == 3) // all tên tướng
                    {
                        MonoString *playerName = (MonoString *)CreateMonoString(heroData.name);
                        MonoString *prefixName = (MonoString *)CreateMonoString("");
                        SetPlayerName(HudControl, playerName, prefixName, false, (MonoString *)CreateMonoString(""));
                    }
                    if (NameMode == 4 && ActorLinker_IsHostPlayer(actorLinker)) // chỉ mình
                    {
                        MonoString *playerName = (MonoString *)CreateMonoString(customname.c_str());
                        MonoString *prefixName = (MonoString *)CreateMonoString("");
                        SetPlayerName(HudControl, playerName, prefixName, false, (MonoString *)CreateMonoString(""));
                    }
                }
                myTeam = ActorLinker_COM_PLAYERCAMP(myActorLinker);
                if (AutoWin)
                {
                    ForceKillCrystal(myTeam);
                    AutoWin = false;
                }
                if (myTeam == ActorLinker_COM_PLAYERCAMP(actorLinker))
                {
                    continue;
                }
                numberOfEnemies++;
                index++;
                if (!ValuePropertyComponent)
                    continue;
                int EnemyHp = ValuePropertyComponent_get_actorHp(ValuePropertyComponent);
                int EnemyHpTotal = ValuePropertyComponent_get_actorHpTotal(ValuePropertyComponent);
                if (AutoBS) // auto băng sương
                {
                    if (!myLactorRoot)
                        continue;
                    void *myValuePropertyComponent = *(void **)((uint64_t)myLactorRoot + LActorRootOffField[0]);
                    if (!myValuePropertyComponent)
                        continue;
                    int myHp = ValuePropertyComponent_get_actorHp(myValuePropertyComponent);
                    int myHpTotal = ValuePropertyComponent_get_actorHpTotal(myValuePropertyComponent);
                    float myEpPercent = (float)myHp / myHpTotal;
                    void *FightForm = get_FightForm(CBattle_Instance);
                    void *CSkillButtonManager = nullptr;

                    if (FightForm)
                    {
                        CSkillButtonManager = *(void **)((uint64_t)FightForm + EspField[11]);
                    }
                    if (CSkillButtonManager)
                    {
                        if (myEpPercent <= AutoBSHp / 100.0f && CanRequestSkill(CSkillButtonManager, 9))
                        {
                            RequestUseSkillSlot(CSkillButtonManager, 9, 0, 0, 0);
                        }
                    }
                }
                if (!LObjWrapper)
                    continue;
                void *SkillControl = *(void **)((uint64_t)LactorRoot + LActorRootOffField[4]);
                bool dead = LObjWrapper_get_IsDeadState(LObjWrapper);
                if (SkillControl != NULL && PlayerTalent && ESPEnable)
                {
                    int *cooldowns = SkillControlAll1(SkillControl);
                    DrawIconBT(draw, heroData.index, cooldowns, index, EnemyHp, EnemyHpTotal, dead);
                    free(cooldowns);
                }
                if (dead)
                    continue;
                Vector3 HeroPos = Vector3::zero();
                VInt3 NowLocation = LActorRoot_get_location(LactorRoot);
                VInt3 forwardEnemy = LActorRoot_get_forward(LactorRoot);
                bool isVisible = ActorLinker_get_bVisible(actorLinker);
                if (isVisible)
                {
                    HeroPos = ActorLinker_getPosition(actorLinker);
                    previousEnemyPositions[(uintptr_t)LactorRoot] = HeroPos;
                }
                else
                {
                    HeroPos = VInt2Vector(NowLocation, forwardEnemy);

                    if (previousEnemyPositions.find((uintptr_t)LactorRoot) == previousEnemyPositions.end())
                    {
                        previousEnemyPositions[(uintptr_t)LactorRoot] = HeroPos;
                    }
                    HeroPos = Lerp(previousEnemyPositions[(uintptr_t)LactorRoot], HeroPos, 0.2f);
                    previousEnemyPositions[(uintptr_t)LactorRoot] = HeroPos;
                    if (showMinimap && ESPEnable)
                        DrawIconMap(draw, HeroPos, heroData.index, EnemyHp, EnemyHpTotal);
                }

                float Distance = Vector3::Distance(myPos, HeroPos);
                void *PlayerMovement = LActorRoot_get_PlayerMovement(LactorRoot);
                int speed = get_speed(PlayerMovement);
                float EpPercent = (float)EnemyHp / EnemyHpTotal;
                if (AutoBP) // bộc phá
                {
                    void *mySkillControl = *(void **)((uint64_t)myLactorRoot + LActorRootOffField[4]);
                    int *cooldowns = SkillControlAll1(mySkillControl);
                    if (EpPercent <= AutoBPHp / 100.0f && Distance < 5.1f && EnemyHp > 0 && cooldowns[4] == 80108)
                    {
                        Reqskill2(Req5, false);
                        Reqskill(Req5);
                    }
                }
                float distancess1 = ClosestDistanceEnemy(myPos, HeroPos, useSkillDirection1);
                float distancess2 = ClosestDistanceEnemy(myPos, HeroPos, useSkillDirection2);
                float distancess3 = ClosestDistanceEnemy(myPos, HeroPos, useSkillDirection3);
                if (AimbotEnable)
                {
                    if (!MANUALAIM)
                    {
                        void *myObjLinker = *(void **)((uintptr_t)myActorLinker + ActorLinkerOffField[3]);
                        int myheroID = *(int *)((uintptr_t)myObjLinker + ActorLinkerOffField[11]);
                        EnemyTarget1.ConfigID = myheroID;
                        // elsu [196]
                        if (EnemyTarget1.ConfigID == 196)
                        {
                            EnemyTarget2.Ranger = 25.0f;
                            EnemyTarget2.bullettime = 0.44f;
                        }
                        // Yue [545]
                        else if (EnemyTarget1.ConfigID == 545)
                        {
                            EnemyTarget1.Ranger = 9.0f;
                            EnemyTarget1.bullettime = 0.6f;

                            EnemyTarget2.Ranger = 13.0f;
                            EnemyTarget2.bullettime = 0.77f;
                        }
                        // Natalya [142]
                        else if (EnemyTarget1.ConfigID == 142)
                        {
                            EnemyTarget1.Ranger = 11.5f;
                            EnemyTarget1.bullettime = 0.84f;

                            EnemyTarget2.Ranger = 9.5f;
                            EnemyTarget2.bullettime = 0.87f;
                        }
                        // Krixi [106]
                        else if (EnemyTarget1.ConfigID == 106)
                        {
                            EnemyTarget1.Ranger = 11.0f;
                            EnemyTarget1.bullettime = 1.00f;

                            EnemyTarget2.Ranger = 9.5f;
                            EnemyTarget2.bullettime = 0.37f;
                        }
                        // Gildur [108]
                        else if (EnemyTarget1.ConfigID == 108)
                        {
                            EnemyTarget2.Ranger = 15.0f;
                            EnemyTarget2.bullettime = 0.8f;
                        }
                        // Violet [111]
                        else if (EnemyTarget1.ConfigID == 111)
                        {
                            EnemyTarget3.Ranger = 15.5f;
                            EnemyTarget3.bullettime = 0.8f;
                        }
                        // Alice [118]
                        else if (EnemyTarget1.ConfigID == 118)
                        {
                            EnemyTarget1.Ranger = 12.0f;
                            EnemyTarget1.bullettime = 0.87f;
                        }
                        // Marja [121]
                        else if (EnemyTarget1.ConfigID == 121)
                        {
                            EnemyTarget2.Ranger = 8.7f;
                            EnemyTarget2.bullettime = 0.57f;
                        }
                        // Ignis [124]
                        else if (EnemyTarget1.ConfigID == 124)
                        {
                            EnemyTarget1.Ranger = 9.5f;
                            EnemyTarget1.bullettime = 0.77f;

                            EnemyTarget2.Ranger = 11.5f;
                            EnemyTarget2.bullettime = 0.4f;

                            EnemyTarget3.Ranger = 12.7f;
                            EnemyTarget3.bullettime = 1.17f;
                        }
                        // Azzen'Ka [127]
                        else if (EnemyTarget1.ConfigID == 127)
                        {
                            EnemyTarget1.Ranger = 11.7f;
                            EnemyTarget1.bullettime = 0.84f;

                            EnemyTarget3.Ranger = 9.0f;
                            EnemyTarget3.bullettime = 1.12f;
                        }
                        // Airi [130]
                        else if (EnemyTarget1.ConfigID == 130)
                        {
                            EnemyTarget1.Ranger = 11.5f;
                            EnemyTarget1.bullettime = 1.04f;
                        }
                        // Ilumia [136]
                        else if (EnemyTarget1.ConfigID == 136)
                        {
                            EnemyTarget1.Ranger = 10.7f;
                            EnemyTarget1.bullettime = 1.04f;
                        }

                        // Raz [157]
                        else if (EnemyTarget1.ConfigID == 157)
                        {
                            EnemyTarget2.Ranger = 11.7f;
                            EnemyTarget2.bullettime = 0.75f;
                        }

                        // Điêu Thuyền [152]
                        else if (EnemyTarget1.ConfigID == 152)
                        {
                            EnemyTarget1.Ranger = 11.2f;
                            EnemyTarget1.bullettime = 0.37f;

                            EnemyTarget2.Ranger = 10.7f;
                            EnemyTarget2.bullettime = 1.14f;
                        }

                        // Kaine [153]
                        else if (EnemyTarget1.ConfigID == 153)
                        {
                            EnemyTarget2.Ranger = 9.5f;
                            EnemyTarget2.bullettime = 0.67f;
                        }

                        // Lumburr [168]
                        else if (EnemyTarget1.ConfigID == 168)
                        {
                            EnemyTarget3.Ranger = 12.5f;
                            EnemyTarget3.bullettime = 1.04f;
                        }

                        // Slimz [169]
                        else if (EnemyTarget1.ConfigID == 169)
                        {
                            EnemyTarget1.Ranger = 19.2f;
                            EnemyTarget1.bullettime = 1.67f;
                        }

                        // Stuart [174]
                        else if (EnemyTarget1.ConfigID == 174)
                        {
                            EnemyTarget1.Ranger = 16.0f;
                            EnemyTarget1.bullettime = 0.55f; // có nội tại
                        }

                        // Grakk [175]
                        else if (EnemyTarget1.ConfigID == 175)
                        {
                            EnemyTarget2.Ranger = 12.0f;
                            EnemyTarget2.bullettime = 0.67f;
                        }

                        // Enzo [195]
                        else if (EnemyTarget1.ConfigID == 195)
                        {
                            EnemyTarget2.Ranger = 9.7f;
                            EnemyTarget2.bullettime = 0.27f;
                        }

                        // Charlotte [206]
                        else if (EnemyTarget1.ConfigID == 206)
                        {
                            EnemyTarget1.Ranger = 12.2f;
                            EnemyTarget1.bullettime = 0.9f;
                        }

                        // Tel'Annas [501]
                        else if (EnemyTarget1.ConfigID == 501)
                        {
                            EnemyTarget2.Ranger = 12.2f;
                            EnemyTarget2.bullettime = 0.7f;

                            EnemyTarget3.Ranger = 15.5f;
                            EnemyTarget3.bullettime = 0.77f;
                        }

                        // Wonder Woman [504]
                        else if (EnemyTarget1.ConfigID == 504)
                        {
                            EnemyTarget2.Ranger = 9.5f;
                            EnemyTarget2.bullettime = 0.44f;
                        }

                        // Liliana [510]
                        else if (EnemyTarget1.ConfigID == 510)
                        {
                            EnemyTarget1.Ranger = 11.2f;
                            EnemyTarget1.bullettime = 0.4f;

                            EnemyTarget2.Ranger = 10.5f;
                            EnemyTarget2.bullettime = 0.6f;
                        }

                        // Florentino [521]
                        else if (EnemyTarget1.ConfigID == 521)
                        {
                            EnemyTarget1.Ranger = 7.7f;
                            EnemyTarget1.bullettime = 0.44f;
                        }
                        // Ishar [526]
                        else if (EnemyTarget1.ConfigID == 526)
                        {
                            EnemyTarget1.Ranger = 9.5f;
                            EnemyTarget1.bullettime = 0.7f;
                        }

                        // Volkath [529]
                        else if (EnemyTarget1.ConfigID == 529)
                        {
                            EnemyTarget2.Ranger = 10.2f;
                            EnemyTarget2.bullettime = 0.72f;
                        }

                        // Iggy [538]
                        else if (EnemyTarget1.ConfigID == 538)
                        {
                            EnemyTarget1.Ranger = 12.0f;
                            EnemyTarget1.bullettime = 0.87f;

                            // EnemyTarget3.Ranger = 20.7f;
                            // EnemyTarget3.bullettime = 1.3f;
                        }

                        // Bright [540]
                        else if (EnemyTarget1.ConfigID == 540)
                        {
                            EnemyTarget1.Ranger = 10.7f;
                            EnemyTarget1.bullettime = 0.74f;
                        }

                        // Bonnie [541]
                        else if (EnemyTarget1.ConfigID == 541)
                        {
                            // EnemyTarget1.Ranger = 11.7f;
                            // EnemyTarget1.bullettime = 0.57f;
                        }

                        // Erin [567]
                        else if (EnemyTarget1.ConfigID == 567)
                        {
                            EnemyTarget1.Ranger = 11.2f;
                            EnemyTarget1.bullettime = 0.64f;
                        }
                        // Heino [563]
                        else if (EnemyTarget1.ConfigID == 563)
                        {
                            EnemyTarget1.Ranger = 12.5f;
                            EnemyTarget1.bullettime = 0.87f;
                        }
                        else
                        {
                            EnemyTarget1.Ranger = 0.0f;
                            EnemyTarget1.bullettime = 0.0f;
                            EnemyTarget2.Ranger = 0.0f;
                            EnemyTarget2.bullettime = 0.0f;
                            EnemyTarget3.Ranger = 0.0f;
                            EnemyTarget3.bullettime = 0.0f;
                        }
                        speedSkill1 = EnemyTarget1.bullettime;
                        speedSkill2 = EnemyTarget2.bullettime;
                        speedSkill3 = EnemyTarget3.bullettime;
                        RangeSkill1 = EnemyTarget1.Ranger;
                        RangeSkill2 = EnemyTarget2.Ranger;
                        RangeSkill3 = EnemyTarget3.Ranger;
                    }
                    else
                    {
                        EnemyTarget1.bullettime = speedSkill1;
                        EnemyTarget2.bullettime = speedSkill2;
                        EnemyTarget3.bullettime = speedSkill3;
                        if (!Rangeauto && RangeSkill)
                        {
                            EnemyTarget1.Ranger = RangeSkill1;
                            EnemyTarget2.Ranger = RangeSkill2;
                            EnemyTarget3.Ranger = RangeSkill3;
                        }
                        if (Rangeauto && RangeSkill)
                        {
                            EnemyTarget1.Ranger = RangeSkill1auto;
                            EnemyTarget2.Ranger = RangeSkill2auto;
                            EnemyTarget3.Ranger = RangeSkill3auto;
                            RangeSkill1 = RangeSkill1auto;
                            RangeSkill2 = RangeSkill2auto;
                            RangeSkill3 = RangeSkill3auto;
                        }
                    }
                }
                Vector3 enemyPos = VIntVector(NowLocation);
                Vector3 V3forwardEnemy = VIntVector(forwardEnemy);
                float currentSpeed = (float)speed / 1000.0f;
                Vector3 Checkpos1 = Vector3::zero();
                Vector3 Checkpos2 = Vector3::zero();
                Vector3 Checkpos3 = Vector3::zero();
                float Distance1 = 999.0f;
                float Distance2 = 999.0f;
                float Distance3 = 999.0f;
                if (AimbotNew)
                {
                    if (EnemyTarget1.bullettime > 0.0f && AimbotEnable && (!MANUALAIM || (MANUALAIM && enableSkill1)))
                    {
                        Checkpos1 = calculateSkillPosition(myPos, enemyPos, V3forwardEnemy, currentSpeed, EnemyTarget1.bullettime, EnemyTarget1.Ranger);
                        Distance1 = Vector3::Distance(myPos, Checkpos1);
                    }
                    if (EnemyTarget2.bullettime > 0.0f && AimbotEnable && (!MANUALAIM || (MANUALAIM && enableSkill2)))
                    {
                        Checkpos2 = calculateSkillPosition(myPos, enemyPos, V3forwardEnemy, currentSpeed, EnemyTarget2.bullettime, EnemyTarget2.Ranger);
                        Distance2 = Vector3::Distance(myPos, Checkpos2);
                    }
                    if (EnemyTarget3.bullettime > 0.0f && AimbotEnable && (!MANUALAIM || (MANUALAIM && enableSkill3)))
                    {
                        Checkpos3 = calculateSkillPosition(myPos, enemyPos, V3forwardEnemy, currentSpeed, EnemyTarget3.bullettime, EnemyTarget3.Ranger);
                        Distance3 = Vector3::Distance(myPos, Checkpos3);
                    }
                }
                else
                {
                    Distance1 = Distance;
                    Distance2 = Distance;
                    Distance3 = Distance;
                }
                if (Distance1 <= EnemyTarget1.Ranger && EnemyTarget1.bullettime > 0.0f && AimbotEnable && (!MANUALAIM || (MANUALAIM && enableSkill1)))
                {
                    if (aimType == 0 && EnemyHp < lowestHp1)
                    {
                        EnemyTarget1.enemyPos = VIntVector(NowLocation);
                        EnemyTarget1.moveForward = VIntVector(forwardEnemy);
                        EnemyTarget1.currentSpeed = (float)speed / 1000.0f;
                        lowestHp1 = EnemyHp;
                        Entity1 = LactorRoot;
                    }
                    if (aimType == 1)
                    {
                        if (EpPercent < lowestHpPercent1)
                        {
                            EnemyTarget1.enemyPos = VIntVector(NowLocation);
                            EnemyTarget1.moveForward = VIntVector(forwardEnemy);
                            EnemyTarget1.currentSpeed = (float)speed / 1000.0f;
                            lowestHpPercent1 = EpPercent;
                            Entity1 = LactorRoot;
                        }

                        if (EpPercent == lowestHpPercent1 && EnemyHp < lowestHp12)
                        {
                            EnemyTarget1.enemyPos = VIntVector(NowLocation);
                            EnemyTarget1.moveForward = VIntVector(forwardEnemy);
                            EnemyTarget1.currentSpeed = (float)speed / 1000.0f;
                            lowestHp12 = EnemyHp;
                            lowestHpPercent1 = EpPercent;
                            Entity1 = LactorRoot;
                        }
                    }

                    if (aimType == 2 && Distance < closestEnemyDistance1)
                    {
                        EnemyTarget1.enemyPos = VIntVector(NowLocation);
                        EnemyTarget1.moveForward = VIntVector(forwardEnemy);
                        EnemyTarget1.currentSpeed = (float)speed / 1000.0f;
                        closestEnemyDistance1 = Distance;
                        Entity1 = LactorRoot;
                    }

                    if (aimType == 3 && distancess1 < closestEnemyDistanceView1)
                    {
                        EnemyTarget1.enemyPos = VIntVector(NowLocation);
                        EnemyTarget1.moveForward = VIntVector(forwardEnemy);
                        EnemyTarget1.currentSpeed = (float)speed / 1000.0f;
                        closestEnemyDistanceView1 = distancess1;
                        Entity1 = LactorRoot;
                    }
                }
                if (Distance2 <= EnemyTarget2.Ranger && EnemyTarget2.bullettime > 0.0f && AimbotEnable && (!MANUALAIM || (MANUALAIM && enableSkill2)))
                {
                    if (aimType == 0 && EnemyHp < lowestHp2)
                    {
                        EnemyTarget2.enemyPos = VIntVector(NowLocation);
                        EnemyTarget2.moveForward = VIntVector(forwardEnemy);
                        EnemyTarget2.currentSpeed = (float)speed / 1000.0f;
                        lowestHp2 = EnemyHp;
                        Entity2 = LactorRoot;
                    }
                    if (aimType == 1)
                    {
                        if (EpPercent < lowestHpPercent2)
                        {
                            EnemyTarget2.enemyPos = VIntVector(NowLocation);
                            EnemyTarget2.moveForward = VIntVector(forwardEnemy);
                            EnemyTarget2.currentSpeed = (float)speed / 1000.0f;
                            lowestHpPercent2 = EpPercent;
                            Entity2 = LactorRoot;
                        }

                        if (EpPercent == lowestHpPercent2 && EnemyHp < lowestHp22)
                        {
                            EnemyTarget2.enemyPos = VIntVector(NowLocation);
                            EnemyTarget2.moveForward = VIntVector(forwardEnemy);
                            EnemyTarget2.currentSpeed = (float)speed / 1000.0f;
                            lowestHp22 = EnemyHp;
                            lowestHpPercent2 = EpPercent;
                            Entity2 = LactorRoot;
                        }
                    }

                    if (aimType == 2 && Distance < closestEnemyDistance2)
                    {
                        EnemyTarget2.enemyPos = VIntVector(NowLocation);
                        EnemyTarget2.moveForward = VIntVector(forwardEnemy);
                        EnemyTarget2.currentSpeed = (float)speed / 1000.0f;
                        closestEnemyDistance2 = Distance;
                        Entity2 = LactorRoot;
                    }

                    if (aimType == 3 && distancess2 < closestEnemyDistanceView2)
                    {
                        EnemyTarget2.enemyPos = VIntVector(NowLocation);
                        EnemyTarget2.moveForward = VIntVector(forwardEnemy);
                        EnemyTarget2.currentSpeed = (float)speed / 1000.0f;
                        closestEnemyDistanceView2 = distancess2;
                        Entity2 = LactorRoot;
                    }
                }
                if (Distance3 <= EnemyTarget3.Ranger && EnemyTarget3.bullettime > 0.0f && AimbotEnable && (!MANUALAIM || (MANUALAIM && enableSkill3)))
                {
                    if (aimType == 0 && EnemyHp < lowestHp3 && EnemyHp > 0)
                    {
                        EnemyTarget3.enemyPos = VIntVector(NowLocation);
                        EnemyTarget3.moveForward = VIntVector(forwardEnemy);
                        EnemyTarget3.currentSpeed = (float)speed / 1000.0f;
                        lowestHp3 = EnemyHp;
                        Entity3 = LactorRoot;
                    }
                    if (aimType == 1)
                    {
                        if (EpPercent < lowestHpPercent3 && EnemyHp > 0)
                        {
                            EnemyTarget3.enemyPos = VIntVector(NowLocation);
                            EnemyTarget3.moveForward = VIntVector(forwardEnemy);
                            EnemyTarget3.currentSpeed = (float)speed / 1000.0f;
                            lowestHpPercent3 = EpPercent;
                            Entity3 = LactorRoot;
                        }

                        if (EpPercent == lowestHpPercent3 && EnemyHp < lowestHp32 && EnemyHp > 0)
                        {
                            EnemyTarget3.enemyPos = VIntVector(NowLocation);
                            EnemyTarget3.moveForward = VIntVector(forwardEnemy);
                            EnemyTarget3.currentSpeed = (float)speed / 1000.0f;
                            lowestHp32 = EnemyHp;
                            lowestHpPercent3 = EpPercent;
                            Entity3 = LactorRoot;
                        }
                    }

                    if (aimType == 2 && Distance < closestEnemyDistance3 && EnemyHp > 0)
                    {
                        EnemyTarget3.enemyPos = VIntVector(NowLocation);
                        EnemyTarget3.moveForward = VIntVector(forwardEnemy);
                        EnemyTarget3.currentSpeed = (float)speed / 1000.0f;
                        closestEnemyDistance3 = Distance;
                        Entity3 = LactorRoot;
                    }

                    if (aimType == 3 && distancess3 < closestEnemyDistanceView3 && EnemyHp > 0)
                    {
                        EnemyTarget3.enemyPos = VIntVector(NowLocation);
                        EnemyTarget3.moveForward = VIntVector(forwardEnemy);
                        EnemyTarget3.currentSpeed = (float)speed / 1000.0f;
                        closestEnemyDistanceView3 = distancess3;
                        Entity3 = LactorRoot;
                    }
                }
                if (IgnoreInvisible && isVisible)
                {
                    continue;
                }

                int EnemyEp = ValuePropertyComponent_get_actorEp(ValuePropertyComponent);
                int EnemyEpTotal = ValuePropertyComponent_get_actorEpTotal(ValuePropertyComponent);
                int GetLever = ValuePropertyComponent_get_actorSoulLevel(ValuePropertyComponent);
                ImVec2 HeroScreenPos = GetPlayerPosition(HeroPos);
                string heroname;
                heroname = string(heroData.name);
                bool outscreen = isOutsideScreen(ImVec2(HeroScreenPos.x, HeroScreenPos.y), ImVec2(kWidth, kHeight));
                bool isBoxDrawn = false;
                Vector3 headPos3D = HeroPos + Vector3(0, 2, 0);
                ImVec2 feetPixel = HeroScreenPos;
                ImVec2 headPixel = GetPlayerPosition(headPos3D);
                float boxHeightScreen = abs(headPixel.y - feetPixel.y);
                boxWidthScreen = boxHeightScreen * 0.75f;
                ImVec2 boxTopLeft = ImVec2(feetPixel.x - boxWidthScreen / 2.0f, headPixel.y);
                ImVec2 boxBottomRight = ImVec2(feetPixel.x + boxWidthScreen / 2.0f, headPixel.y + boxHeightScreen);
                float boxHeight = kHeight / 8;
                float boxWidth1 = boxHeight * 0.55f;
                ImVec2 vStart = {HeroScreenPos.x - (boxWidth1 / 2), HeroScreenPos.y};
                ImVec2 vEnd = {vStart.x + boxWidth1, vStart.y - boxHeight};

                if (PlayerBox && !outscreen && ESPEnable)
                {
                    ImU32 boxColor = IM_COL32(255, 255, 255, 255);
                    float boxThickness = 0.5f;
                    
                    float boxWidth = boxBottomRight.x - boxTopLeft.x;
                    float boxHeight = boxBottomRight.y - boxTopLeft.y;
                    float cornerSize = std::min(boxWidth, boxHeight) * 0.25f;
                    
                    // Top left corner
                    draw->AddLine(
                        ImVec2(boxTopLeft.x, boxTopLeft.y + cornerSize),
                        ImVec2(boxTopLeft.x, boxTopLeft.y),
                        boxColor, boxThickness);
                    draw->AddLine(
                        ImVec2(boxTopLeft.x, boxTopLeft.y),
                        ImVec2(boxTopLeft.x + cornerSize, boxTopLeft.y),
                        boxColor, boxThickness);
                    
                    // Top right corner
                    draw->AddLine(
                        ImVec2(boxBottomRight.x - cornerSize, boxTopLeft.y),
                        ImVec2(boxBottomRight.x, boxTopLeft.y),
                        boxColor, boxThickness);
                    draw->AddLine(
                        ImVec2(boxBottomRight.x, boxTopLeft.y),
                        ImVec2(boxBottomRight.x, boxTopLeft.y + cornerSize),
                        boxColor, boxThickness);
                    
                    // Bottom left corner
                    draw->AddLine(
                        ImVec2(boxTopLeft.x, boxBottomRight.y - cornerSize),
                        ImVec2(boxTopLeft.x, boxBottomRight.y),
                        boxColor, boxThickness);
                    draw->AddLine(
                        ImVec2(boxTopLeft.x, boxBottomRight.y),
                        ImVec2(boxTopLeft.x + cornerSize, boxBottomRight.y),
                        boxColor, boxThickness);
                    
                    // Bottom right corner
                    draw->AddLine(
                        ImVec2(boxBottomRight.x - cornerSize, boxBottomRight.y),
                        ImVec2(boxBottomRight.x, boxBottomRight.y),
                        boxColor, boxThickness);
                    draw->AddLine(
                        ImVec2(boxBottomRight.x, boxBottomRight.y),
                        ImVec2(boxBottomRight.x, boxBottomRight.y - cornerSize),
                        boxColor, boxThickness);
                    
                    isBoxDrawn = true;
                }
                if (PlayerLine && ESPEnable)
                {

                    if (isBoxDrawn)
                    {
                        draw->AddLine(ImVec2(ImGui::GetIO().DisplaySize.x / 2, 38), ImVec2((boxTopLeft.x + boxBottomRight.x) / 2.0f, boxTopLeft.y), ImColor(Colorwhite), 0.1f);
                    }
                    else
                    {
                        draw->AddLine(ImVec2(ImGui::GetIO().DisplaySize.x / 2, 38), HeroScreenPos, ImColor(Colorwhite), 0.1f);
                    }
                // std::string enemyCount = "Enemies [" + std::to_string(numberOfEnemies) + "]";
                    std::string enemyCount = "Anhvu.cc";

                    ImVec2 textSize = ImGui::CalcTextSize(enemyCount.c_str());

                    float paddingX = 10.0f;
                    float paddingY = 6.0f;
                    float logoSize = textSize.y + 4.0f; // Kích thước logo
                    float totalWidth = logoSize + 8.0f + textSize.x; // logo + khoảng cách + text

                    ImVec2 topLeft = ImVec2(ImGui::GetIO().DisplaySize.x / 2 - (totalWidth / 2) - paddingX,
                                            38 - textSize.y - paddingY);
                    ImVec2 bottomRight = ImVec2(ImGui::GetIO().DisplaySize.x / 2 + (totalWidth / 2) + paddingX,
                                                38 + paddingY);
                    
                    // Nền đen với độ trong suốt cao
                    draw->AddRectFilled(topLeft, bottomRight, IM_COL32(15, 15, 15, 240), 8.0f);

                    // Vị trí logo bên trái
                    ImVec2 logoCenter = ImVec2(topLeft.x + paddingX + logoSize / 2, 
                                               topLeft.y + (bottomRight.y - topLeft.y) / 2);
                    
                    if (logo_texture != nil)
                    {
                        float logoImgSize = logoSize * 0.8f;
                        ImVec2 logoTopLeft = ImVec2(logoCenter.x - logoImgSize / 2, logoCenter.y - logoImgSize / 2);
                        ImVec2 logoBottomRight = ImVec2(logoCenter.x + logoImgSize / 2, logoCenter.y + logoImgSize / 2);
                        draw->AddImage((ImTextureID)(intptr_t)logo_texture, logoTopLeft, logoBottomRight);
                    }
                    

                    float textX = logoCenter.x + logoSize / 2 + 8.0f;
                    float textY = 38 - textSize.y;
                    draw->AddText(NULL, ((float)kHeight / 28.0f),
                                  ImVec2(textX, textY),
                                  IM_COL32(255, 255, 255, 255), enemyCount.c_str());
                }
                if (Circle3D && !outscreen && ESPEnable)
                {
                    Draw3DCircle(draw, HeroPos, HeroScreenPos, 0.8f, 100, 0.2f);
                }
                ostringstream oss;
                oss << fixed << setprecision(1) << Distance << "m";
                string strDistance = oss.str();
                auto textSize1 = ImGui::CalcTextSize(strDistance.c_str());
                if (PlayerDistance && !outscreen && ESPEnable)
                {
                    draw->AddText({HeroScreenPos.x - (float)(textSize1.x / 2), HeroScreenPos.y + 5}, IM_COL32(255, 255, 255, 255), strDistance.c_str());
                }
                if (PlayerName && !outscreen && ESPEnable)
                {
                    DrawHealthBar(draw, HeroScreenPos, EnemyHp, EnemyHpTotal, EnemyEp, EnemyEpTotal, heroname, GetLever);
                }
                if (hiencooldowns && !outscreen && ESPEnable)
                    DrawSkillCD(draw, HeroScreenPos, LactorRoot);
                if (Drawicon && !outscreen && ESPEnable && heroData.index != -1)
                {
                    ImVec2 HeroScreenpos1 = HeroScreenPos;
                    if (isBoxDrawn)
                    {
                        float icondrawsize = boxWidthScreen * 0.75;
                        float minIconSize = 1.0f;
                        if (icondrawsize < minIconSize)
                            icondrawsize = minIconSize;
                        icondrawsize = icondrawsize * customIconSize;
                        ImVec2 boxCenter = ImVec2((boxTopLeft.x + boxBottomRight.x) / 2.0f, (boxTopLeft.y + boxBottomRight.y) / 2.0f);

                        ImVec2 iconTopLeft = ImVec2(boxCenter.x - icondrawsize / 2.0f, boxCenter.y - icondrawsize / 2.0f);
                        ImVec2 iconBottomRight = ImVec2(boxCenter.x + icondrawsize / 2.0f, boxCenter.y + icondrawsize / 2.0f);
                        if (!customIcon)
                            draw->AddImage((ImTextureID)(intptr_t)textures[heroData.index].texture, iconTopLeft, iconBottomRight);
                        else
                        {
                            HeroScreenpos1 = GetPlayerPosition({HeroPos.x, HeroPos.y + customIconPOS, HeroPos.z});
                            DrawIconHero(draw, HeroScreenpos1, textures[heroData.index], icondrawsize);
                        }
                    }
                    else
                    {
                        float icondrawsize = boxWidthScreen * 0.75;
                        float minIconSize = 1.0f;
                        if (icondrawsize < minIconSize)
                            icondrawsize = minIconSize;
                        icondrawsize = icondrawsize * customIconSize;
                        if (customIcon)
                            HeroScreenpos1 = GetPlayerPosition({HeroPos.x, HeroPos.y + customIconPOS, HeroPos.z});
                        DrawIconHero(draw, HeroScreenpos1, textures[heroData.index], icondrawsize);
                    }
                }
                if (PlayerAlert && outscreen && ESPEnable)
                    DrawPlayerAlert(draw, HeroScreenPos, heroData.index, EnemyHp, EnemyHpTotal, strDistance);
            }
        }
        void *FightForm = get_FightForm(CBattle_Instance);
        void *CSkillButtonManager = nullptr;
        if (FightForm)
        {
            CSkillButtonManager = *(void **)((uintptr_t)FightForm + EspField[11]);
        }
        if (CSkillButtonManager)
        {
            SkillSlotType = *(int *)((uintptr_t)CSkillButtonManager + EspField[16]);
        }
        if (EnemyTarget1.bullettime > 0.0f && Entity1 && AimbotEnable && (!MANUALAIM || (MANUALAIM && enableSkill1)))
        {
            Vector3 skillposition = calculateSkillPosition(myPos, EnemyTarget1.enemyPos, EnemyTarget1.moveForward, EnemyTarget1.currentSpeed, EnemyTarget1.bullettime, EnemyTarget1.Ranger);
            if (!Aimhook)
            {
                void *skillControl1 = *(void **)((uintptr_t)Req1 + ActorLinkerOffField[7]);
                *(Vector3 *)((uintptr_t)skillControl1 + ActorLinkerOffField[9]) = calculateSkillDirection(myPos, EnemyTarget1.enemyPos, EnemyTarget1.moveForward, EnemyTarget1.currentSpeed, EnemyTarget1.bullettime, EnemyTarget1.Ranger);
                *(Vector3 *)((uintptr_t)skillControl1 + ActorLinkerOffField[10]) = skillposition;
            }
            if ((SkillSlotType == 1 && drawType == 2) || drawType == 1)
            {
                ImVec2 ScreenPosFuture = GetPlayerPosition(skillposition);
                draw->AddLine(MyposScreen, ScreenPosFuture, ImColor(200, 200, 200, 100), 0.1f);
            }
        }
        else
        {
            if (Aimhook)
            {
                EnemyTarget1.enemyPos = Vector3::zero();
                EnemyTarget1.moveForward = Vector3::zero();
            }
        }
        if (EnemyTarget2.bullettime > 0.0f && Entity2 && AimbotEnable && (!MANUALAIM || (MANUALAIM && enableSkill2)))
        {
            Vector3 skillposition = calculateSkillPosition(myPos, EnemyTarget2.enemyPos, EnemyTarget2.moveForward, EnemyTarget2.currentSpeed, EnemyTarget2.bullettime, EnemyTarget2.Ranger);
            if (!Aimhook)
            {
                void *skillControl2 = *(void **)((uintptr_t)Req2 + ActorLinkerOffField[7]);
                *(Vector3 *)((uintptr_t)skillControl2 + ActorLinkerOffField[9]) = calculateSkillDirection(myPos, EnemyTarget2.enemyPos, EnemyTarget2.moveForward, EnemyTarget2.currentSpeed, EnemyTarget2.bullettime, EnemyTarget2.Ranger);
                *(Vector3 *)((uintptr_t)skillControl2 + ActorLinkerOffField[10]) = skillposition;
            }
            if ((SkillSlotType == 2 && drawType == 2) || drawType == 1)
            {
                ImVec2 ScreenPosFuture = GetPlayerPosition(skillposition);
                draw->AddLine(MyposScreen, ScreenPosFuture, ImColor(200, 200, 200, 100), 0.1f);
            }
        }
        else
        {
            if (Aimhook)
            {
                EnemyTarget2.enemyPos = Vector3::zero();
                EnemyTarget2.moveForward = Vector3::zero();
            }
        }
        if (EnemyTarget3.bullettime > 0.0f && Entity3 && AimbotEnable && (!MANUALAIM || (MANUALAIM && enableSkill3)))
        {
            Vector3 skillposition = calculateSkillPosition(myPos, EnemyTarget3.enemyPos, EnemyTarget3.moveForward, EnemyTarget3.currentSpeed, EnemyTarget3.bullettime, EnemyTarget3.Ranger);
            if (!Aimhook)
            {
                void *skillControl3 = *(void **)((uintptr_t)Req3 + ActorLinkerOffField[7]);
                *(Vector3 *)((uintptr_t)skillControl3 + ActorLinkerOffField[9]) = calculateSkillDirection(myPos, EnemyTarget3.enemyPos, EnemyTarget3.moveForward, EnemyTarget3.currentSpeed, EnemyTarget3.bullettime, EnemyTarget3.Ranger);
                *(Vector3 *)((uintptr_t)skillControl3 + ActorLinkerOffField[10]) = skillposition;
            }
            if ((SkillSlotType == 3 && drawType == 2) || drawType == 1)
            {
                ImVec2 ScreenPosFuture = GetPlayerPosition(skillposition);
                draw->AddLine(MyposScreen, ScreenPosFuture, ImColor(200, 200, 200, 100), 0.1f);
            }
        }
        else
        {
            if (Aimhook)
            {
                EnemyTarget3.enemyPos = Vector3::zero();
                EnemyTarget3.moveForward = Vector3::zero();
            }
        }
        if (EspMonster || AutoTT)
        {
            if (!myActorLinker)
                return;
            List<void **> *GetAllMonster = *(List<void **> **)((uintptr_t)actorManager + EspField[6]);
            List<void **> *GetAllmonster_Root = *(List<void **> **)((uintptr_t)LGameActorMgr_Instance + EspField[19]);
            if (GetAllmonster_Root == nullptr)
                return;
            if (GetAllMonster == nullptr)
                return;
            void ***LactorrootMonstersm = (void ***)GetAllmonster_Root->getItems();
            void ***actorLinkersm = (void ***)GetAllMonster->getItems();
            void *ValueLinkerComponent1 = *(void **)((uintptr_t)myActorLinker + ActorLinkerOffField[0]);
            for (int i = 0; i < GetAllmonster_Root->getSize(); i++)
            {
                void *LactorrootMonster = LactorrootMonstersm[(i * 2) + 1];
                void *actorLinkerMonster = actorLinkersm[(i * 2) + 1];
                if (LactorrootMonster == nullptr)
                    continue;
                if (actorLinkerMonster == nullptr)
                    continue;
                void *ValuePropertyComponent = *(void **)((uintptr_t)LactorrootMonster + LActorRootOffField[0]);
                void *LObjWrapper = *(void **)((uintptr_t)LactorrootMonster + LActorRootOffField[1]);
                void *ObjLinker = *(void **)((uintptr_t)actorLinkerMonster + ActorLinkerOffField[3]);
                void *LVActorLinker = *(void **)((uintptr_t)LactorrootMonster + LActorRootOffField[5]);
                int ConfigID = *(int *)((uintptr_t)ObjLinker + ActorLinkerOffField[11]);
                if (ConfigID >= 7300 && ConfigID <= 70000)
                    continue;
                if (VipMon && !(ConfigID == 7010 || ConfigID == 7011 || ConfigID == 7012 || ConfigID == 70093 || ConfigID == 70092 || ConfigID == 7024 || ConfigID == 7009))
                    continue;
                int MonsterHp = ValuePropertyComponent_get_actorHp(ValuePropertyComponent);
                if (MonsterHp < 1)
                    continue;
                Vector3 MonPos = Vector3::zero();
                VInt3 NowLocation = LActorRoot_get_location(LactorrootMonster);
                VInt3 forwardEnemy = LActorRoot_get_forward(LactorrootMonster);
                bool isVisible = ActorLinker_get_bVisible(actorLinkerMonster);
                if (isVisible)
                {
                    MonPos = ActorLinker_getPosition(actorLinkerMonster);
                    previousEnemyPositions[(uintptr_t)LactorrootMonster] = MonPos;
                }
                else
                {
                    MonPos = VInt2Vector(NowLocation, forwardEnemy);

                    if (previousEnemyPositions.find((uintptr_t)LactorrootMonster) == previousEnemyPositions.end())
                    {
                        previousEnemyPositions[(uintptr_t)LactorrootMonster] = MonPos;
                    }
                    MonPos = Lerp(previousEnemyPositions[(uintptr_t)LactorrootMonster], MonPos, 0.2f);
                    previousEnemyPositions[(uintptr_t)LactorrootMonster] = MonPos;
                    if (showMinimapMon)
                        DrawIconMapMonster(draw, MonPos, MonsterHp, ConfigID);
                }
                int *skillCooldowns = SkillControlAll(myActorLinker);
                if (AutoTT && (skillCooldowns[4] == 80104 || skillCooldowns[4] == 80116) && skillCooldowns[3] == 0) // auto Trừng Trị
                {
                    bool isBuff1 = false;
                    bool isBuff2 = false;
                    void *BuffLinkerComponent = *(void **)((uintptr_t)myActorLinker + ActorLinkerOffField[17]);
                    if (BuffLinkerComponent != NULL)
                    {
                        List<void **> *SpawnedBuffList = *(List<void **> **)((uint64_t)BuffLinkerComponent + ActorLinkerOffField[18]);
                        if (SpawnedBuffList != NULL)
                        {
                            if (SpawnedBuffList->getSize() > 0)
                            {
                                for (int i = 0; i < SpawnedBuffList->getSize(); i++)
                                {
                                    void *BuffSkill = SpawnedBuffList->getItems()[i];
                                    if (BuffSkill != NULL)
                                    {
                                        int skillID = get_SkillID(BuffSkill);
                                        if (skillID == 7012920 || skillID == 7012921) // bùa hại 1
                                        {
                                            isBuff1 = true;
                                        }
                                        if (skillID == 7024910 || skillID == 7024930 || skillID == 7012930) // bùa hại 2
                                        {
                                            isBuff2 = true;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    if (ConfigID == 7010 || ConfigID == 7011) // xanh đỏ
                    {
                        float distance = Vector3::Distance(myPos, MonPos);
                        if (distance <= 5.0f)
                        {
                            int level = ValueLinkerComponent_get_actorSoulLevel(ValueLinkerComponent1) - 1;
                            if (MonsterHp <= (1350 + 100 * level) && Req5 && !CeaserOnly && !rongta)
                            {
                                Reqskill2(Req5, false);
                                Reqskill(Req5);
                            }
                        }
                    }
                    else if (ConfigID == 7012 || ConfigID == 70093) // 7012: rồng // 70093: caesar
                    {
                        float distance = Vector3::Distance(myPos, MonPos);
                        if (distance <= 5.0f)
                        {
                            int level = ValueLinkerComponent_get_actorSoulLevel(ValueLinkerComponent1) - 1;
                            if (((MonsterHp <= (1350 + 100 * level) && !isBuff1) || (2 * MonsterHp <= (1350 + 100 * level) && isBuff1) && Req5))
                            {
                                Reqskill2(Req5, false);
                                Reqskill(Req5);
                            }
                        }
                    }
                    else if (ConfigID == 70092 || ConfigID == 7024 || ConfigID == 7009) // 70092: bạo chúa // 7024: rồng ánh sáng // 7009: caesar hắc ám
                    {
                        float distance = Vector3::Distance(myPos, MonPos);
                        if (distance <= 5.0f)
                        {
                            int level = ValueLinkerComponent_get_actorSoulLevel(ValueLinkerComponent1) - 1;
                            if (((MonsterHp <= (1350 + 100 * level) && !isBuff2) || (2 * MonsterHp <= (1350 + 100 * level) && isBuff2) && Req5))
                            {
                                Reqskill2(Req5, false);
                                Reqskill(Req5);
                            }
                        }
                    }
                }
                if (IgnoreInvisibleMon && isVisible)
                    continue;

                ImVec2 MonScreenPos = GetPlayerPosition({MonPos.x, MonPos.y, MonPos.z});
                if (ConfigID == 7012 || ConfigID == 70093 || ConfigID == 70092 || ConfigID == 7024 || ConfigID == 7009 || ConfigID == 7010 || ConfigID == 7011)
                    MonScreenPos = GetPlayerPosition({MonPos.x, MonPos.y + 2.0f, MonPos.z});
                bool outscreen = isOutsideScreen(MonScreenPos, ImVec2(kWidth, kHeight));
                if (EspMonster)
                {
                    if (ConfigID == 7012 || ConfigID == 70093 || ConfigID == 70092 || ConfigID == 7024 || ConfigID == 7009)
                        draw->AddCircleFilled(MonScreenPos, (float)kHeight / 100, ImColor(255, 0, 0));
                    else if (ConfigID == 7010 || ConfigID == 7011)
                        draw->AddCircleFilled(MonScreenPos, (float)kHeight / 150, ImColor(255, 0, 0));
                    else
                        draw->AddCircleFilled(MonScreenPos, (float)kHeight / 200, ImColor(255, 0, 0));
                }
                if (showMonsterHp && EspMonster && !outscreen)
                {
                    float boxHeight = 30;
                    float boxWidth1 = boxHeight * 0.55f;
                    ImVec2 vStart = {MonScreenPos.x - (boxWidth1 / 2), MonScreenPos.y};
                    ImVec2 vEnd = {vStart.x + boxWidth1, vStart.y - boxHeight};
                    string strHp = to_string(MonsterHp);
                    ImVec2 textSize2 = ImGui::CalcTextSize(strHp.c_str());
                    ImVec2 topCenter = {vStart.x + (boxWidth1 / 2), vEnd.y};
                    ImU32 colorEspMonster = IM_COL32(255, 255, 255, 255);
                    if (ConfigID == 7012 || ConfigID == 7024)
                        draw->AddText(nullptr, ImGui::GetFontSize() * 1.0f, {topCenter.x - (float)(textSize2.x), topCenter.y - 5.0f}, colorEspMonster, strHp.c_str());
                    else if (ConfigID == 70093 || ConfigID == 70092 || ConfigID == 7009)
                        draw->AddText(nullptr, ImGui::GetFontSize() * 1.5f, {topCenter.x - (float)(textSize2.x * 0.75f), topCenter.y - 5.0f}, colorEspMonster, strHp.c_str());
                    else if (ConfigID == 7010 || ConfigID == 7011)
                        draw->AddText(nullptr, ImGui::GetFontSize() * 1.5f, {topCenter.x - (float)(textSize2.x * 0.75f), topCenter.y - 5.0f}, colorEspMonster, strHp.c_str());
                    else
                        draw->AddText({topCenter.x - (float)(textSize2.x / 2), topCenter.y - 5.0f}, colorEspMonster, strHp.c_str());
                }
            }
        }
    }
}