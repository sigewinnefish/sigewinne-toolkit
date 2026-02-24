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
    uint32_t  ResinListItemId000106Allowed : 1;
    uint32_t  ResinListItemId000201Allowed : 1;
    uint32_t  ResinListItemId107009Allowed : 1;
    uint32_t  ResinListItemId107012Allowed : 1;
    uint32_t  ResinListItemId220007Allowed : 1;
    uint32_t  HideUid : 1;
    uint32_t  reserved : 16; // 16 - 31
};

