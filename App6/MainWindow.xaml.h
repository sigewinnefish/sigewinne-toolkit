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

        MainWindow();
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
