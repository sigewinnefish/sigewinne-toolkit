#pragma once
#include "NotifyIconContextMenu.xaml.h"


using namespace winrt::Microsoft::UI;
using namespace winrt::Microsoft::UI::Xaml::Hosting;
using namespace winrt::Microsoft::UI::Xaml::Controls;
using namespace winrt::App6::implementation;

namespace Service::NotifyIcon
{
    class Controller
    {
    public:
        Controller() = default;
        void Init();
        void InitPopupWindowContents();
        void ShowPopupWindow();
        void DeleteNotifyIcon();

    private:
        void AddNotifyIcon();
        void CreateNotifyIconHostWindow();
        void InitMessage();
        void SetCallback();

        Dispatching::DispatcherQueue m_dispatcherQueue{ nullptr };
        HWND m_hwnd{};
        WindowId m_windowId{};
        DesktopWindowXamlSource m_xamlSource = nullptr;
        Border m_anchor = nullptr;
        winrt::App6::NotifyIconContextMenu m_flyout = nullptr;

        UINT m_NotifyIconCallbackMessage{};
        UINT m_TaskbarCreatedMessage{};
        bool m_iconAdded = 0;

    };
}
