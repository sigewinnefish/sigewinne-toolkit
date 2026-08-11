#pragma once

#include <microsoft.ui.xaml.window.h>
#include "MainWindow.g.h"


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
        void Window_Closed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::WindowEventArgs const& args);
        inline static winrt::Microsoft::UI::WindowId m_windowId;

    private:
        HWND _hwnd{ nullptr };
        UINT NotifyIconCallbackMessage;
        UINT TaskbarCreatedMessage;

        HWND GetWindowHandle();
		void Exp1();
        void Exp2();
        void InitWindow();

    };

}

namespace winrt::App6::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
}
