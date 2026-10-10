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

    };
}

namespace winrt::App6::factory_implementation
{
    struct NotifyIconContextMenu : NotifyIconContextMenuT<NotifyIconContextMenu, implementation::NotifyIconContextMenu>
    {
    };
}
