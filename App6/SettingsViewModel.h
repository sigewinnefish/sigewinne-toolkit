#pragma once
#include "Settings.h"
#include "SettingsViewModel.g.h"
#include <winrt/Microsoft.UI.Xaml.Data.h>
#include <wil/cppwinrt_authoring.h>

using namespace Service::Settings;
namespace winrt::App6::implementation
{
    struct SettingsViewModel : SettingsViewModelT<SettingsViewModel>, wil::notify_property_changed_base<SettingsViewModel>
    {
		SettingsViewModel() = default;

        bool StealthMode();
        void StealthMode(bool value);

        void RestrictedTokens(bool value);
        bool RestrictedTokens();

        bool LangOverride();
        void LangOverride(bool value);

        auto GamePath() const noexcept {
            return m_GamePath;
        }
        auto& GamePath(hstring value) {
            if (m_GamePath != value) {
                pappsettings->set_gamepath(to_string(value));
                m_GamePath = std::move(value);
                RaisePropertyChanged(L"GamePath");
            }
            return *this;
        };

	private:
        hstring m_GamePath{ to_hstring(pappsettings->gamepath()) };

    };
}

namespace winrt::App6::factory_implementation
{
    struct SettingsViewModel : SettingsViewModelT<SettingsViewModel, implementation::SettingsViewModel>
    {
    };
}