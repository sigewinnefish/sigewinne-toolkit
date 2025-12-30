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
        void AddNotifyIcon();
		void Exp1();
        void Exp2();

    public:
        void Window_Closed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::WindowEventArgs const& args);
    };
    LRESULT CALLBACK NotifyIconProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);
}

namespace winrt::App6::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
}
