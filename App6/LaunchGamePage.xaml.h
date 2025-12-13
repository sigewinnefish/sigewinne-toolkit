#pragma once

#include "LaunchGamePage.g.h"

namespace winrt::App6::implementation
{
    struct LaunchGamePage : LaunchGamePageT<LaunchGamePage>
    {
        LaunchGamePage()
        {
            this->NavigationCacheMode(Microsoft::UI::Xaml::Navigation::NavigationCacheMode::Required);
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }


    };
}

namespace winrt::App6::factory_implementation
{
    struct LaunchGamePage : LaunchGamePageT<LaunchGamePage, implementation::LaunchGamePage>
    {
    };
}
