#pragma once

#include "SettingsCard.g.h"

namespace winrt::App6::implementation
{
    struct SettingsCard : SettingsCardT<SettingsCard>
    {
        SettingsCard()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }


    };
}

namespace winrt::App6::factory_implementation
{
    struct SettingsCard : SettingsCardT<SettingsCard, implementation::SettingsCard>
    {
    };
}
