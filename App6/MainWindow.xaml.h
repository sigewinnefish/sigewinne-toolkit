#pragma once

#include <microsoft.ui.xaml.window.h>
#include <wil/result_macros.h>
#include <winrt/Microsoft.UI.Windowing.h>
#include "MainWindow.g.h"
#include "island.h"

using namespace winrt;
using namespace winrt::Microsoft::UI::Xaml;
using namespace winrt::Microsoft::UI::Xaml::Controls;
using namespace winrt::Microsoft::UI::Windowing;



namespace winrt::App6::implementation
{
    struct MainWindow : MainWindowT<MainWindow>
    {   
    public:

        MainWindow()
        {

            this->AppWindow().Closing([&](auto&&, auto&&)
                {

                    ;
				});
            this->Title(L"winui");
			this->ExtendsContentIntoTitleBar(true);
            this->AppWindow().TitleBar().PreferredHeightOption(TitleBarHeightOption::Tall);
            this->AppWindow().TitleBar().PreferredTheme(TitleBarTheme::UseDefaultAppMode);
            this->AppWindow().SetIcon(L"Assets\\Logo.ico");

			UINT dpi = GetDpiForWindow(GetWindowHandle());
            THROW_HR_IF(E_INVALIDARG, 0 == dpi);
            auto scale = floorf(dpi * 100.0f / 96.0f + 0.5f) / 100.0f;
            this->AppWindow().Presenter().try_as<OverlappedPresenter>().PreferredMinimumHeight(static_cast<int32_t>(600 * scale));
            this->AppWindow().Presenter().try_as<OverlappedPresenter>().PreferredMinimumWidth(static_cast<int32_t>(1000 * scale));

            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }
        void initializeEnv();


    private:
        HWND _hwnd{ nullptr };
        HWND GetWindowHandle();


    };
}

namespace winrt::App6::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
}
