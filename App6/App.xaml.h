#pragma once

#include "App.xaml.g.h"
#include <Controller.h>

using namespace Service;

namespace winrt::App6::implementation
{
    struct App : AppT<App>
    {
        App();

        void OnLaunched(Microsoft::UI::Xaml::LaunchActivatedEventArgs const&);
        static void ToForeground();

        ~App();

	private:
        winrt::Microsoft::UI::Xaml::Window mainWindow{nullptr};
        winrt::Microsoft::UI::Xaml::Window notifyIconWindow{ nullptr };
        HWND notifyIconWindowhwnd{0};
        NotifyIcon::Controller notifyIconController;

    };
}
