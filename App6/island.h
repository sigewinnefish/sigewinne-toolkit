#pragma once
#include <Windows.h>

struct IslandEnvironment
{
    CHAR  Reserved[76];
    float FieldOfView;
    uint32_t  TargetFrameRate;
    uint32_t  EnableSetFieldOfView : 1;
    uint32_t  FixLowFovScene : 1;
    uint32_t  DisableFog : 1;
    uint32_t  EnableSetTargetFrameRate : 1;
    uint32_t  RemoveOpenTeamProgress : 1;
    uint32_t  HideQuestBanner : 1;
    uint32_t  DisableEventCameraMove : 1;
    uint32_t  DisableShowDamageText : 1;
    uint32_t  UsingTouchScreen : 1;
    uint32_t  RedirectCombineEntry : 1;
    uint32_t  ResinListItemAllowOriginalResin : 1;
    uint32_t  ResinListItemAllowPrimogem : 1;
    uint32_t  ResinListItemAllowFragileResin : 1;
    uint32_t  ResinListItemAllowTransientResin : 1;
    uint32_t  ResinListItemAllowCondensedResin : 1;
    uint32_t  HideUid : 1;
    uint32_t  reserved : 16; // 16 - 31
};

