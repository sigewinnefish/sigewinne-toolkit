#pragma once

#include "IslandPage.g.h"
#include "island.h"
#include "Settings.h"
#include "helper.h"

using namespace Service::Settings;

DWORD WINAPI LaunchGameProc(LPVOID lpParameter);


namespace winrt::App6::implementation
{
    struct IslandPage : IslandPageT<IslandPage>
    {
    private:

    public:
        IslandPage();
        BINDISLAND(FieldOfView, fieldofview);
        BINDISLAND(TargetFrameRate, targetframerate);
        BINDISLAND(EnableSetFieldOfView, enablesetfieldofview);
        BINDISLAND(FixLowFovScene, fixlowfovscene);
        BINDISLAND(DisableFog, disablefog);
        BINDISLAND(EnableSetTargetFrameRate, enablesettargetframerate);
        BINDISLAND(RemoveOpenTeamProgress, removeopenteamprogress);
        BINDISLAND(HideQuestBanner, hidequestbanner);
        BINDISLAND(DisableEventCameraMove, disableeventcameramove);
        BINDISLAND(DisableShowDamageText, disableshowdamagetext);
        BINDISLAND(UsingTouchScreen, usingtouchscreen);
        BINDISLAND(RedirectCombineEntry, redirectcombineentry);
        BINDISLAND(HideUid, hideuid);
        BINDISLANDITEM(ResinListItemAllowOriginalResin, 106);
        BINDISLANDITEM(ResinListItemAllowPrimogem, 201);
        BINDISLANDITEM(ResinListItemAllowFragileResin, 107009);
        BINDISLANDITEM(ResinListItemAllowTransientResin, 107012);
        BINDISLANDITEM(ResinListItemAllowCondensedResin, 220007);

    };
}

namespace winrt::App6::factory_implementation
{
    struct IslandPage : IslandPageT<IslandPage, implementation::IslandPage>
    {
    };
}
