#pragma once

#include "LaunchGamePage.g.h"
#include "Settings.h"
#include "helper.h"

using namespace Service::Settings;

namespace winrt::App6::implementation
{
    struct LaunchGamePage : LaunchGamePageT<LaunchGamePage>
    {

        BIND(LaunchGameWindowsHDR, plaunchgame, iswindowshdrenabled);
        BIND(LaunchGameArguments, plaunchgame, arecommandlineargumentsenabled);
        BIND(LaunchGameAppearanceExclusive, plaunchgame, isexclusive);
        BIND(LaunchGameAppearanceFullscreen, plaunchgame, isfullscreen);
        BIND(LaunchGameAppearanceBorderless, plaunchgame, isborderless);
        BIND(LaunchGameAppearanceScreenWidth, plaunchgame, isscreenwidthenabled);
        BIND(LaunchGameAppearanceScreenHeight, plaunchgame, isscreenheightenabled);
        BIND(LaunchGameAppearanceScreenWidthValue, plaunchgame, screenwidth);
        BIND(LaunchGameAppearanceScreenHeightValue, plaunchgame, screenheight);

        LaunchGamePage();

    private:

    };
}

namespace winrt::App6::factory_implementation
{
    struct LaunchGamePage : LaunchGamePageT<LaunchGamePage, implementation::LaunchGamePage>
    {
    };
}
