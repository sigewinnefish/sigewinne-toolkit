#pragma once

#include "LaunchGamePage.g.h"

namespace winrt::App6::implementation
{
    struct LaunchGamePage : LaunchGamePageT<LaunchGamePage>
    {

        bool LaunchGameWindowsHDR();
        void LaunchGameWindowsHDR(bool value);

        bool LaunchGameArguments();
        void LaunchGameArguments(bool value);

        bool LaunchGameAppearanceExclusive();
        void LaunchGameAppearanceExclusive(bool value);

        bool LaunchGameAppearanceFullscreen();
        void LaunchGameAppearanceFullscreen(bool value);

        bool LaunchGameAppearanceBorderless();
        void LaunchGameAppearanceBorderless(bool value);

        bool LaunchGameAppearanceScreenWidth();
        void LaunchGameAppearanceScreenWidth(bool value);

        bool LaunchGameAppearanceScreenHeight();
        void LaunchGameAppearanceScreenHeight(bool value);

        uint32_t LaunchGameAppearanceScreenWidthValue();
        void LaunchGameAppearanceScreenWidthValue(uint32_t value);

        uint32_t LaunchGameAppearanceScreenHeightValue();
        void LaunchGameAppearanceScreenHeightValue(uint32_t value);

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
