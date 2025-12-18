#pragma once

#include "App.xaml.g.h"
#include "SettingsCard.h"

namespace winrt::App6::implementation
{
    struct App : AppT<App>
    {
        App();

        void OnLaunched(Microsoft::UI::Xaml::LaunchActivatedEventArgs const&);
        static void ToForeground();

        ~App();
    private:
        winrt::Microsoft::UI::Xaml::Window window{ nullptr };

    };
}
