#pragma once

#include "SettingsPage.g.h"

namespace winrt::App6::implementation
{
    struct SettingsPage : SettingsPageT<SettingsPage>
    {
        SettingsPage();

        bool StealthMode();
        void StealthMode(bool value);

        void RestrictedTokens(bool value);
        bool RestrictedTokens();

        bool LangOverride();
        void LangOverride(bool value);

        void LangCombo_SelectionChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& e);
    };
}

namespace winrt::App6::factory_implementation
{
    struct SettingsPage : SettingsPageT<SettingsPage, implementation::SettingsPage>
    {
    };
}
