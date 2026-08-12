#pragma once
#include "Settings.h"
#include "SettingsViewModel.g.h"
#include <winrt/Microsoft.UI.Xaml.Data.h>
#include <wil/cppwinrt_authoring.h>
#include "helper.h"

using namespace Service::Settings;
namespace winrt::App6::implementation
{
    struct SettingsViewModel : SettingsViewModelT<SettingsViewModel>, wil::notify_property_changed_base<SettingsViewModel>
    {

        SettingsViewModel();
        // default bind
        BIND(StealthMode, pappsettings, stealthmode);
        BIND(RestrictedTokens, pappsettings, restrictedtokens);
        BIND(LangOverride, pappsettings, langoverride);
        BIND(CloseBehaviorIndex, pappsettings, closebehavior);
        
        // others
        bool IslandRestrictionsOverride();
        void IslandRestrictionsOverride(bool value);

        bool FrameRateLimitOverride();
        void FrameRateLimitOverride(bool value);

        uint32_t FrameRateLimitValue();
        void FrameRateLimitValue(uint32_t value);

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
        }

        wil::single_threaded_property<Windows::Foundation::Collections::IObservableVector<hstring>> CloseBehaviors = winrt::single_threaded_observable_vector<hstring>();
        wil::single_threaded_property<Windows::Foundation::Collections::IObservableVector<hstring>> Languages = winrt::single_threaded_observable_vector<hstring>();

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