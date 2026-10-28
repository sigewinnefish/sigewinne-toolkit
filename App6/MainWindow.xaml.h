#pragma once

#include <microsoft.ui.xaml.window.h>
#include "MainWindow.g.h"


using namespace winrt;
using namespace winrt::Microsoft::UI::Xaml;
using namespace winrt::Microsoft::UI::Xaml::Controls;
using namespace winrt::Microsoft::UI::Windowing;



namespace winrt::App6::implementation
{
    enum class PlacementRestorationBehavior : std::uint32_t
    {
        None = 0,
        AllowShowMaximized = 0x1,
        AllowShowFullScreen = 0x2,
        AllowShowArranged = 0x4,
        UseStartupInfoForFirstWindow = 0x8,
        All = 0xffffffff,
    };

    struct MainWindow : MainWindowT<MainWindow>
    {   
    public:

        MainWindow();
        void ShowWindowWithSavedPlacement();
        void Window_Closed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::WindowEventArgs const& args);
        inline static winrt::Microsoft::UI::WindowId m_windowId;
    private:
        HWND _hwnd{ nullptr };
        UINT NotifyIconCallbackMessage;
        UINT TaskbarCreatedMessage;
        HWND GetWindowHandle();
        void InitWindow();
        void SetPlacementRestorationBehavior(PlacementRestorationBehavior behavior);
        void SaveCurrentPlacement();

    };


}

namespace winrt::App6::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
}
