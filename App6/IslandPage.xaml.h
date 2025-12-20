#pragma once

#include "IslandPage.g.h"
#include "island.h"
#include "Settings.h"


DWORD WINAPI LaunchGameProc(LPVOID lpParameter);


namespace winrt::App6::implementation
{
    struct IslandPage : IslandPageT<IslandPage>
    {

    private:

    public:
        IslandPage();

        float FieldOfView();
        void FieldOfView(float value);

        uint32_t TargetFrameRate();
        void TargetFrameRate(uint32_t value);

        bool EnableSetFieldOfView();
        void EnableSetFieldOfView(bool value);

        bool FixLowFovScene();
        void FixLowFovScene(bool value);

        bool DisableFog();
        void DisableFog(bool value);

        bool EnableSetTargetFrameRate();
        void EnableSetTargetFrameRate(bool value);

        bool RemoveOpenTeamProgress();
        void RemoveOpenTeamProgress(bool value);

        bool HideQuestBanner();
        void HideQuestBanner(bool value);

        bool DisableEventCameraMove();
        void DisableEventCameraMove(bool value);

        bool DisableShowDamageText();
        void DisableShowDamageText(bool value);

        bool UsingTouchScreen();
        void UsingTouchScreen(bool value);

        bool RedirectCombineEntry();
        void RedirectCombineEntry(bool value);

        bool ResinListItemAllowOriginalResin();
        void ResinListItemAllowOriginalResin(bool value);

        bool ResinListItemAllowPrimogem();
        void ResinListItemAllowPrimogem(bool value);

        bool ResinListItemAllowFragileResin();
        void ResinListItemAllowFragileResin(bool value);

        bool ResinListItemAllowTransientResin();
        void ResinListItemAllowTransientResin(bool value);

        bool ResinListItemAllowCondensedResin();
        void ResinListItemAllowCondensedResin(bool value);


    };
}

namespace winrt::App6::factory_implementation
{
    struct IslandPage : IslandPageT<IslandPage, implementation::IslandPage>
    {
    };
}
