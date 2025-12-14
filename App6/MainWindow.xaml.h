#pragma once
#include <microsoft.ui.xaml.window.h>

#include <winrt/Microsoft.UI.Windowing.h>


#include "MainWindow.g.h"
#include "island.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;
using namespace Microsoft::UI::Windowing;


namespace winrt::App6::implementation
{
    struct MainWindow : MainWindowT<MainWindow>
    {   
    private:
        IslandEnvironment* penv;
    public:

        MainWindow()
        {
            
            initializeEnv();

            this->AppWindow().Closing([&](auto&&, auto&&)
                {

                    ;
				});
            this->Title(L"winui");
			this->ExtendsContentIntoTitleBar(true);
            this->AppWindow().TitleBar().PreferredHeightOption(TitleBarHeightOption::Tall);
            this->AppWindow().TitleBar().PreferredTheme(TitleBarTheme::UseDefaultAppMode);
            this->AppWindow().SetIcon(L"Assets\\Logo.ico");
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
