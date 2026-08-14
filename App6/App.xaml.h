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
        
		static void PresentMainWindow();
        inline static Microsoft::UI::Xaml::Window mainWindow{ nullptr };
        ~App();

	private:
        static void ToForeground();
        NotifyIcon::Controller notifyIconController;

    };
}
