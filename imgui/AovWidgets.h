#pragma once
// ─────────────────────────────────────────────
//  AovWidgets.h
//  Custom ImGui widgets: AovToggle, AovSlider, AovCombo
//  Include once in ImGuiDrawView.mm
// ─────────────────────────────────────────────
#include "imgui.h"
#include "fontAwesome.h"
#include <map>
#include <string>

// Haptic callback – set to HapticLight() in ImGuiDrawView.mm after it is defined.
// Widgets call this instead of calling HapticLight() directly.
static void (*AovHapticFn)() = nullptr;
static inline void _AovHaptic() { if (AovHapticFn) AovHapticFn(); }

// ─── Math helpers ───────────────────────────
static inline float aov_lerp(float a, float b, float t) { return a + (b - a) * t; }
static inline float aov_clamp(float v, float lo, float hi) { return v < lo ? lo : v > hi ? hi : v; }

// ─── AovToggle ──────────────────────────────
static bool AovToggle(const char* label, bool* v) {
    const float pillW  = 44.f, pillH = 24.f;
    const float totalW = ImGui::GetContentRegionAvail().x;
    const ImGuiID id   = ImGui::GetID(label);

    static std::map<ImGuiID, float> s_knob;
    float& knob = s_knob[id];
    knob = aov_lerp(knob, *v ? 1.f : 0.f, ImGui::GetIO().DeltaTime * 14.f);

    ImVec2 pos    = ImGui::GetCursorScreenPos();
    bool pressed  = ImGui::InvisibleButton(label, ImVec2(totalW, pillH));
    if (pressed) { *v = !(*v); }

    ImDrawList* dl   = ImGui::GetWindowDrawList();
    const float kRadius = pillH * 0.5f;
    ImVec2 pillMin(pos.x + totalW - pillW, pos.y);
    ImVec2 pillMax(pillMin.x + pillW, pillMin.y + pillH);

    ImU32 bgOff = IM_COL32(35, 35, 55, 220);
    ImU32 bgOn  = IM_COL32(22, 102, 240, 255);
    auto lerp8  = [](ImU32 a, ImU32 b, int shift, float t) -> int {
        return (int)(((a >> shift) & 0xFF) * (1.f - t) + ((b >> shift) & 0xFF) * t);
    };
    ImU32 bg = IM_COL32(lerp8(bgOff, bgOn, IM_COL32_R_SHIFT, knob),
                        lerp8(bgOff, bgOn, IM_COL32_G_SHIFT, knob),
                        lerp8(bgOff, bgOn, IM_COL32_B_SHIFT, knob), 255);
    dl->AddRectFilled(pillMin, pillMax, bg, kRadius);

    // Knob
    float knobX = pillMin.x + kRadius + knob * (pillW - pillH);
    dl->AddCircleFilled(ImVec2(knobX, pillMin.y + kRadius), kRadius - 3.f,
                        IM_COL32(235, 240, 255, 255), 28);

    // Label
    ImVec2 labelSz = ImGui::CalcTextSize(label, nullptr, true);
    ImU32 txtCol   = *v ? IM_COL32(215, 228, 255, 245) : IM_COL32(155, 165, 195, 200);
    dl->AddText(ImVec2(pos.x, pos.y + (pillH - labelSz.y) * 0.5f), txtCol, label);

    return pressed;
}

// ─── AovHint ────────────────────────────────
// Inline ⓘ icon that shows a tooltip on hover.
// Usage: AovHint("tip text"); ImGui::SameLine(0,4.f); AovToggle(...);
// Pass a unique id string if you use multiple hints on the same frame.
static void AovHint(const char* text, const char* id = "##_aovhint") {
    float fh  = ImGui::GetFrameHeight();
    float sz  = fh * 0.72f;
    ImVec2 p  = ImGui::GetCursorScreenPos();
    ImVec2 cp = ImVec2(p.x + sz * 0.5f, p.y + fh * 0.5f);
    bool hov  = ImGui::IsMouseHoveringRect(p, ImVec2(p.x + sz, p.y + fh));
    ImDrawList* dl = ImGui::GetWindowDrawList();
    // Circle background
    dl->AddCircleFilled(cp, sz * 0.5f,
        hov ? IM_COL32(55, 130, 230, 210) : IM_COL32(30, 50, 100, 140));
    // "i" letter centered
    ImVec2 iSz = ImGui::CalcTextSize("i");
    dl->AddText(ImVec2(cp.x - iSz.x * 0.5f, cp.y - iSz.y * 0.5f),
        hov ? IM_COL32(255, 255, 255, 255) : IM_COL32(160, 200, 255, 200), "i");
    ImGui::InvisibleButton(id, ImVec2(sz, fh));
    if (hov) {
        ImGui::SetNextWindowBgAlpha(0.88f);
        ImGui::SetTooltip("%s", text);
    }
}

// ─── AovSlider ──────────────────────────────
static bool AovSlider(const char* label, float* v, float vMin, float vMax, const char* fmt = "%.1f") {
    const float totalW = ImGui::GetContentRegionAvail().x;
    const float trackH = 6.f;
    const float labelH = ImGui::GetTextLineHeight();
    const ImGuiID id   = ImGui::GetID(label);

    static std::map<ImGuiID, float> s_grab;
    static std::map<ImGuiID, float> s_prevV;
    float& grabR  = s_grab[id];
    float& prevV  = s_prevV[id];

    ImVec2 pos = ImGui::GetCursorScreenPos();
    ImGui::Dummy(ImVec2(totalW, labelH + 5.f));   // label row placeholder

    ImVec2 trackPos = ImGui::GetCursorScreenPos();
    ImGui::SetCursorScreenPos(ImVec2(trackPos.x, trackPos.y - 4.f));
    ImGui::InvisibleButton(label, ImVec2(totalW, trackH + 12.f));
    bool active  = ImGui::IsItemActive();
    bool hovered = ImGui::IsItemHovered();

    bool changed = false;
    if (active) {
        float t    = aov_clamp((ImGui::GetIO().MousePos.x - trackPos.x) / totalW, 0.f, 1.f);
        float newV = vMin + t * (vMax - vMin);
        // Only flag changed (and fire haptic) when the value actually moves
        if (fabsf(newV - prevV) > (vMax - vMin) * 0.001f) {
            *v    = newV;
            prevV = newV;
            changed = true;
            _AovHaptic();
        } else {
            *v = newV;
        }
    } else {
        prevV = *v; // keep in sync while not dragging
    }
    ImGui::SetCursorScreenPos(ImVec2(pos.x, trackPos.y + trackH + 8.f));
    ImGui::Dummy(ImVec2(0, 0));

    grabR = aov_lerp(grabR, active ? 9.f : hovered ? 8.f : 7.f, ImGui::GetIO().DeltaTime * 16.f);

    ImDrawList* dl = ImGui::GetWindowDrawList();

    // Label + value
    char valueBuf[32];
    snprintf(valueBuf, sizeof(valueBuf), fmt, *v);
    ImVec2 valSz = ImGui::CalcTextSize(valueBuf);
    dl->AddText(ImVec2(pos.x, pos.y),                          IM_COL32(175, 195, 230, 220), label);
    dl->AddText(ImVec2(pos.x + totalW - valSz.x, pos.y),      IM_COL32(100, 155, 255, 200), valueBuf);

    // Track
    ImVec2 trackMin(trackPos.x, trackPos.y);
    ImVec2 trackMax(trackPos.x + totalW, trackPos.y + trackH);
    dl->AddRectFilled(trackMin, trackMax, IM_COL32(30, 32, 52, 210), trackH * 0.5f);

    float t    = (vMax > vMin) ? aov_clamp((*v - vMin) / (vMax - vMin), 0.f, 1.f) : 0.f;
    float fillX = trackMin.x + t * totalW;
    if (fillX > trackMin.x)
        dl->AddRectFilled(trackMin, ImVec2(fillX, trackMax.y), IM_COL32(22, 102, 240, 215), trackH * 0.5f);

    // Knob
    float grabCX = aov_clamp(fillX, trackMin.x + grabR, trackMax.x - grabR);
    float grabCY = trackMin.y + trackH * 0.5f;
    dl->AddCircleFilled(ImVec2(grabCX, grabCY), grabR,    IM_COL32(220, 232, 255, 255), 24);
    dl->AddCircle      (ImVec2(grabCX, grabCY), grabR,    IM_COL32(22, 102, 240, 185),  24, 1.5f);

    return changed;
}

// ─── AovCombo ───────────────────────────────
static bool AovCombo(const char* label, int* current, const char* const items[], int count) {
    const float   W       = ImGui::GetContentRegionAvail().x;
    const float   rowH    = 32.f;
    const float   rnd     = 7.f;
    const int     MAX_VIS = 5;
    const float   capH    = fminf((float)count, (float)MAX_VIS) * rowH;
    const ImGuiID id      = ImGui::GetID(label);

    struct ComboState {
        bool  open           = false;
        float anim           = 0.f;
        float scroll         = 0.f, vel = 0.f;
        bool  dragging       = false;
        float dragStartY     = 0.f, dragStartScroll = 0.f;
        float dragDist       = 0.f;  // distance of the CURRENT drag (live)
        float lastDragDist   = 0.f;  // distance of the LAST completed drag — held until next drag starts
        int   lastHapticIdx  = -1;
    };
    static std::map<ImGuiID, ComboState> s_state;
    ComboState& st = s_state[id];

    float dt   = ImGui::GetIO().DeltaTime;
    st.anim    = aov_lerp(st.anim, st.open ? capH : 0.f, dt * 20.f);

    bool         changed  = false;
    const char*  preview  = (*current >= 0 && *current < count) ? items[*current] : "";
    float        listH    = (float)count * rowH;
    float        maxScroll = fmaxf(0.f, listH - capH);

    // ── Header ──
    ImVec2 p = ImGui::GetCursorScreenPos();
    ImGui::InvisibleButton(label, ImVec2(W, rowH));
    // Toggle open/close only on tap (not after a scroll gesture on the header)
    if (ImGui::IsItemClicked(0) && !st.dragging) st.open = !st.open;

    float visH = st.anim;
    if (visH > 0.5f) ImGui::Dummy(ImVec2(W, visH));

    // NOTE: combo only closes when an item is selected or the header is tapped again.
    // We intentionally removed the "close on outside release" logic because it
    // was firing immediately after a scroll gesture ended, collapsing the list.

    ImDrawList* dl = ImGui::GetWindowDrawList();

    ImDrawFlags hdrFlags = (visH > 0.5f) ? ImDrawFlags_RoundCornersTop : ImDrawFlags_RoundCornersAll;
    dl->AddRectFilled(p, ImVec2(p.x + W, p.y + rowH),
                      st.open ? IM_COL32(22, 102, 240, 32) : IM_COL32(16, 18, 40, 225),
                      rnd, hdrFlags);
    ImU32 bord = st.open ? IM_COL32(22, 102, 240, 165) : IM_COL32(50, 60, 105, 160);
    if (visH > 0.5f)
        dl->AddRect(p, ImVec2(p.x + W, p.y + rowH), bord, rnd, ImDrawFlags_RoundCornersTop);
    else
        dl->AddRect(p, ImVec2(p.x + W, p.y + rowH), bord, rnd);

    // Label (strip ##)
    const char* lEnd = strstr(label, "##");
    ImVec2 lSz = ImGui::CalcTextSize(label, nullptr, true);
    dl->AddText(ImVec2(p.x + 11.f, p.y + (rowH - lSz.y) * 0.5f),
                IM_COL32(150, 165, 200, 215), label, lEnd);

    // Preview + chevron
    const char* chev = st.open ? ICON_FA_CHEVRON_UP : ICON_FA_CHEVRON_DOWN;
    ImVec2 cSz = ImGui::CalcTextSize(chev);
    ImVec2 pSz = ImGui::CalcTextSize(preview);
    dl->AddText(ImVec2(p.x + W - cSz.x - 8.f,               p.y + (rowH - cSz.y) * 0.5f),
                IM_COL32(22, 102, 240, 215), chev);
    dl->AddText(ImVec2(p.x + W - cSz.x - pSz.x - 18.f,      p.y + (rowH - pSz.y) * 0.5f),
                IM_COL32(100, 172, 255, 235), preview);

    // ── List ──
    if (visH > 0.5f) {
        ImVec2 lo(p.x, p.y + rowH);
        ImVec2 loBR(lo.x + W, lo.y + visH);

        // Drag-to-scroll
        ImGui::SetCursorScreenPos(lo);
        ImGui::InvisibleButton((std::string(label) + "##list").c_str(), ImVec2(W, visH));
        bool listActive = ImGui::IsItemActive();

        if (listActive) {
            if (!st.dragging) {
                st.dragging         = true;
                st.dragStartY       = ImGui::GetIO().MousePos.y;
                st.dragStartScroll  = st.scroll;
                st.dragDist         = 0.f;
                // reset last drag dist at the START of a new gesture
                st.lastDragDist     = 0.f;
                st.vel              = 0.f;
            }
            float delta = st.dragStartY - ImGui::GetIO().MousePos.y;
            st.dragDist = fabsf(delta);
            st.scroll   = aov_clamp(st.dragStartScroll + delta, 0.f, maxScroll);
            // smooth velocity estimate: blend toward instantaneous px/s
            float rawVel = -ImGui::GetIO().MouseDelta.y / fmaxf(dt, 0.001f);
            st.vel = aov_lerp(st.vel, rawVel, 0.35f);
        } else {
            if (st.dragging) {
                // drag just ended — save distance BEFORE clearing so item-tap guard works
                st.lastDragDist = st.dragDist;
                st.dragging     = false;
                st.dragDist     = 0.f;
            }
            st.scroll = aov_clamp(st.scroll + st.vel * dt, 0.f, maxScroll);
            st.vel    = aov_lerp(st.vel, 0.f, dt * 9.f);
        }

        // Haptic: fire when the item centred in the visible list changes
        // Only while the user is actively dragging or list has momentum
        if (st.dragging || fabsf(st.vel) > 30.f) {
            int midItem = (int)((st.scroll + capH * 0.5f) / rowH);
            midItem = (int)aov_clamp((float)midItem, 0.f, (float)(count - 1));
            if (midItem != st.lastHapticIdx) {
                st.lastHapticIdx = midItem;
                _AovHaptic();
            }
        } else {
            // Keep lastHapticIdx in sync so there's no spurious fire on next drag start
            int midItem = (int)((st.scroll + capH * 0.5f) / rowH);
            st.lastHapticIdx = (int)aov_clamp((float)midItem, 0.f, (float)(count - 1));
        }

        // Background
        dl->AddRectFilled(lo, loBR, IM_COL32(11, 13, 30, 242), rnd, ImDrawFlags_RoundCornersBottom);
        dl->AddRect(p, loBR, IM_COL32(22, 102, 240, 150), rnd);

        dl->PushClipRect(lo, loBR, true);
        for (int i = 0; i < count; i++) {
            float  iy   = lo.y + i * rowH - st.scroll;
            ImVec2 iMin(lo.x,     iy);
            ImVec2 iMax(lo.x + W, iy + rowH);
            if (iMax.y < lo.y)   continue;
            if (iMin.y > loBR.y) break;

            bool sel = (*current == i);
            bool hov = ImGui::IsMouseHoveringRect(iMin, iMax, false) && !st.dragging;

            ImDrawFlags bF = (i == count - 1) ? ImDrawFlags_RoundCornersBottom : ImDrawFlags_RoundCornersNone;
            if (sel)
                dl->AddRectFilled(iMin, iMax, IM_COL32(22, 102, 240, 75),
                                  (i == count - 1) ? rnd : 0.f, bF);
            else if (hov)
                dl->AddRectFilled(iMin, iMax, IM_COL32(22, 102, 240, 32),
                                  (i == count - 1) ? rnd : 0.f, bF);

            if (i > 0)
                dl->AddLine(ImVec2(iMin.x + 12, iy), ImVec2(iMax.x - 12, iy),
                            IM_COL32(38, 50, 88, 95));

            ImVec2 tSz = ImGui::CalcTextSize(items[i]);
            dl->AddText(ImVec2(iMin.x + 14.f, iy + (rowH - tSz.y) * 0.5f),
                        sel ? IM_COL32(115, 185, 255, 255) : IM_COL32(175, 195, 232, 215),
                        items[i]);

            if (sel)
                dl->AddCircleFilled(ImVec2(iMax.x - 14.f, iy + rowH * 0.5f), 3.5f,
                                    IM_COL32(22, 102, 240, 255));

            // Use lastDragDist (persists after drag ends) so a scroll release never
            // accidentally triggers item selection.
            if (hov && ImGui::IsMouseReleased(0) && st.lastDragDist < 8.f) {
                *current = i; st.open = false; changed = true;
                st.lastDragDist = 0.f;
            }
        }
        dl->PopClipRect();

        // Scrollbar
        if (count > MAX_VIS) {
            const float sbW    = 3.f;
            const float sbX    = loBR.x - sbW - 3.f;
            float trackLen     = visH - 8.f;
            float thumbLen     = fmaxf(20.f, trackLen * capH / listH);
            float thumbPos     = (maxScroll > 0.f)
                                 ? (st.scroll / maxScroll) * (trackLen - thumbLen) : 0.f;
            dl->AddRectFilled(ImVec2(sbX, lo.y + 4.f),
                              ImVec2(sbX + sbW, lo.y + 4.f + trackLen),
                              IM_COL32(30, 40, 70, 120), sbW * 0.5f);
            dl->AddRectFilled(ImVec2(sbX, lo.y + 4.f + thumbPos),
                              ImVec2(sbX + sbW, lo.y + 4.f + thumbPos + thumbLen),
                              IM_COL32(22, 102, 240, 200), sbW * 0.5f);
        }

        // Fade edges
        if (st.scroll > 1.f)
            dl->AddRectFilledMultiColor(lo, ImVec2(loBR.x, lo.y + 18.f),
                IM_COL32(11,13,30,200), IM_COL32(11,13,30,200),
                IM_COL32(11,13,30,0),   IM_COL32(11,13,30,0));
        if (st.scroll < maxScroll - 1.f)
            dl->AddRectFilledMultiColor(ImVec2(lo.x, loBR.y - 18.f), loBR,
                IM_COL32(11,13,30,0),   IM_COL32(11,13,30,0),
                IM_COL32(11,13,30,200), IM_COL32(11,13,30,200));
    } else {
        st.scroll = aov_lerp(st.scroll, 0.f, dt * 10.f);
        st.vel    = 0.f;
    }

    return changed;
}
// ─── AovInputText ───────────────────────────────────────────────────────────
// Hộp nhập liệu iOS: tap vào mở UIAlertController có bàn phím native.
// buf/bufSize: buffer giống ImGui::InputText.
// title: tiêu đề hộp thoại. Trả về true khi user xác nhận.
#ifdef __OBJC__
#import <UIKit/UIKit.h>
static bool AovInputText(const char* id, char* buf, size_t bufSize,
                         const char* title = "Nhập tên",
                         const char* placeholder = nullptr,
                         float height = 38.f) {
    // Pending result from alert callback
    struct InputState {
        bool  pending = false;
        char  result[256] = {};
    };
    static std::map<std::string, InputState> s_inputStates;
    InputState& st = s_inputStates[std::string(id)];

    // Apply pending result (set by the alert callback)
    bool changed = false;
    if (st.pending) {
        strncpy(buf, st.result, bufSize - 1);
        buf[bufSize - 1] = '\0';
        st.pending = false;
        changed = true;
    }

    // Draw styled box
    const float W   = ImGui::GetContentRegionAvail().x;
    const float rnd = 7.f;
    ImVec2 pos = ImGui::GetCursorScreenPos();
    bool tapped = ImGui::InvisibleButton(id, ImVec2(W, height));
    bool hov    = ImGui::IsItemHovered();

    ImDrawList* dl = ImGui::GetWindowDrawList();
    ImVec2 bMin = pos, bMax(pos.x + W, pos.y + height);
    dl->AddRectFilled(bMin, bMax,
        hov ? IM_COL32(28, 38, 72, 240) : IM_COL32(18, 22, 48, 220), rnd);
    dl->AddRect(bMin, bMax,
        hov ? IM_COL32(22, 102, 240, 200) : IM_COL32(50, 65, 115, 160), rnd, 0, 1.2f);

    // Pencil icon + text content
    const char* ico = ICON_FA_EDIT;
    ImVec2 iSz = ImGui::CalcTextSize(ico);
    float  ty  = pos.y + (height - iSz.y) * 0.5f;
    dl->AddText(ImVec2(pos.x + 10.f, ty), IM_COL32(80, 130, 220, 200), ico);

    const char* disp = (buf && buf[0] != '\0') ? buf : (placeholder ? placeholder : "");
    ImU32 txtCol = (buf && buf[0] != '\0') ? IM_COL32(215, 230, 255, 240)
                                           : IM_COL32(110, 125, 170, 160);
    ImVec2 tSz = ImGui::CalcTextSize(disp);
    dl->PushClipRect(ImVec2(bMin.x + iSz.x + 16.f, bMin.y),
                     ImVec2(bMax.x - 8.f,           bMax.y), true);
    dl->AddText(ImVec2(pos.x + iSz.x + 18.f, pos.y + (height - tSz.y) * 0.5f),
                txtCol, disp);
    dl->PopClipRect();

    // Open iOS keyboard on tap via UIAlertController
    if (tapped) {
        NSString* titleNS       = [NSString stringWithUTF8String:title];
        NSString* currentText   = buf ? [NSString stringWithUTF8String:buf] : @"";
        NSString* placeholderNS = placeholder ? [NSString stringWithUTF8String:placeholder] : @"";
        InputState* stPtr       = &s_inputStates[std::string(id)];

        UIAlertController* alert =
            [UIAlertController alertControllerWithTitle:titleNS
                                               message:nil
                                        preferredStyle:UIAlertControllerStyleAlert];
        [alert addTextFieldWithConfigurationHandler:^(UITextField* tf) {
            tf.text               = currentText;
            tf.placeholder        = placeholderNS;
            tf.clearButtonMode    = UITextFieldViewModeWhileEditing;
            tf.returnKeyType      = UIReturnKeyDone;
            tf.autocorrectionType = UITextAutocorrectionTypeNo;
        }];
        UIAlertAction* ok = [UIAlertAction actionWithTitle:@"OK"
                                                     style:UIAlertActionStyleDefault
                                                   handler:^(UIAlertAction*) {
            NSString* input = alert.textFields.firstObject.text ?: @"";
            const char* utf = [input UTF8String];
            strncpy(stPtr->result, utf ? utf : "", sizeof(stPtr->result) - 1);
            stPtr->result[sizeof(stPtr->result) - 1] = '\0';
            stPtr->pending = true;
        }];
        UIAlertAction* cancel = [UIAlertAction actionWithTitle:@"Hủy"
                                                         style:UIAlertActionStyleCancel
                                                       handler:nil];
        [alert addAction:ok];
        [alert addAction:cancel];

        UIViewController* root = [UIApplication sharedApplication]
                                     .keyWindow.rootViewController;
        while (root.presentedViewController)
            root = root.presentedViewController;
        [root presentViewController:alert animated:YES completion:nil];
    }
    return changed;
}
#endif // __OBJC__

// ─── AovButton ──────────────────────────────
// Styled action button with optional FA icon.
// style: 0 = Primary (blue), 1 = Danger (red), 2 = Success (green)
static bool AovButton(const char* label, const char* icon = nullptr,
                      int style = 0, ImVec2 size = ImVec2(0.f, 36.f)) {
    float W = (size.x > 0.f) ? size.x : ImGui::GetContentRegionAvail().x;
    float H = (size.y > 0.f) ? size.y : 36.f;
    const float rnd = 7.f;
    const ImGuiID id = ImGui::GetID(label);

    static std::map<ImGuiID, float> s_btnAnim;
    float& anim = s_btnAnim[id];

    ImVec2 pos = ImGui::GetCursorScreenPos();
    bool pressed = ImGui::InvisibleButton(label, ImVec2(W, H));
    bool hovered = ImGui::IsItemHovered();
    bool active  = ImGui::IsItemActive();

    float dt = ImGui::GetIO().DeltaTime;
    anim = aov_lerp(anim, active ? 1.3f : hovered ? 1.f : 0.f, dt * 14.f);
    float t = aov_clamp(anim, 0.f, 1.f);

    // Accent RGB per style
    float ar, ag, ab;
    switch (style) {
        case 1:  ar = 225; ag = 55;  ab = 55;  break;
        case 2:  ar = 40;  ag = 190; ab = 80;  break;
        default: ar = 22;  ag = 102; ab = 240; break;
    }

    ImDrawList* dl = ImGui::GetWindowDrawList();
    ImVec2 bMin = pos, bMax(pos.x + W, pos.y + H);

    // Background – dark base with subtle accent tint on hover
    dl->AddRectFilled(bMin, bMax,
        IM_COL32((int)(16  + t * ar * 0.12f),
                 (int)(18  + t * ag * 0.10f),
                 (int)(38  + t * ab * 0.06f),
                 active ? 250 : 225), rnd);

    // Border – morphs from subtle grey to accent color
    dl->AddRect(bMin, bMax,
        IM_COL32((int)(45  + t * (ar - 45)),
                 (int)(55  + t * (ag - 55)),
                 (int)(95  + t * (ab - 95)),
                 (int)(130 + t * 90)), rnd, 0, 1.2f);

    // Outer glow on hover
    if (t > 0.05f)
        dl->AddRect(ImVec2(bMin.x - 1, bMin.y - 1),
                    ImVec2(bMax.x + 1, bMax.y + 1),
                    IM_COL32((int)ar, (int)ag, (int)ab, (int)(t * 30)),
                    rnd + 1, 0, 1.5f);

    // ── Text layout (icon + label, centered) ──
    const char* hash = strstr(label, "##");
    ImVec2 tSz = ImGui::CalcTextSize(label, hash, true);
    float iconGap = 0.f;
    ImVec2 iSz(0, 0);
    if (icon) { iSz = ImGui::CalcTextSize(icon); iconGap = iSz.x + 7.f; }
    float totalCW = tSz.x + iconGap;
    float cx = bMin.x + (W - totalCW) * 0.5f;
    float ty = bMin.y + (H - tSz.y)   * 0.5f;

    if (icon) {
        dl->AddText(ImVec2(cx, bMin.y + (H - iSz.y) * 0.5f),
                    IM_COL32((int)ar, (int)ag, (int)ab, (int)(175 + t * 80)),
                    icon);
        cx += iconGap;
    }
    dl->AddText(ImVec2(cx, ty),
        IM_COL32((int)(180 + t * 55),
                 (int)(195 + t * 40),
                 (int)(230 + t * 25), 240),
        label, hash);

    return pressed;
}