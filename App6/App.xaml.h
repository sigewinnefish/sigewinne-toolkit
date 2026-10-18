#pragma once

#include "App.xaml.g.h"
#include <Controller.h>

using namespace Service;
using namespace winrt::Microsoft::UI::Xaml;

inline winrt::Microsoft::UI::Dispatching::DispatcherQueue g_mainthreadq{nullptr};

namespace winrt::App6::implementation
{
    struct App : AppT<App>
    {
        App();

        void OnLaunched(LaunchActivatedEventArgs const&);
        static void HandleStartupBehavior();
		static void PresentMainWindow();
        inline static Window mainWindow{ nullptr };
        ~App();

	private:
        static void ToForeground();
        NotifyIcon::Controller notifyIconController;

    };
}
