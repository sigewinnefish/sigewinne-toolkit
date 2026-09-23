#pragma once

#include "NotifyIconContextMenu.g.h"

namespace winrt::App6::implementation
{
    struct NotifyIconContextMenu : NotifyIconContextMenuT<NotifyIconContextMenu>
    {
        NotifyIconContextMenu()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        void Window_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void Exit_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void Launch_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::App6::factory_implementation
{
    struct NotifyIconContextMenu : NotifyIconContextMenuT<NotifyIconContextMenu, implementation::NotifyIconContextMenu>
    {
    };
}
