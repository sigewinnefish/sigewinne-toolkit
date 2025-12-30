#include "pch.h"
#include "SettingsPage.xaml.h"

#include "Settings.h"
#if __has_include("SettingsPage.g.cpp")
#include "SettingsPage.g.cpp"
#endif


using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Service::Settings;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::App6::implementation
{
	SettingsPage::SettingsPage()
	{
		DispatcherQueue().TryEnqueue(
			[this]()
			{
				LangCombo().SelectedIndex(pappsettings->lang());

			});
		
		// Xaml objects should not call InitializeComponent during construction.
		// See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
	}

	bool SettingsPage::StealthMode()
	{
		return pappsettings->stealthmode();
	}

	void SettingsPage::StealthMode(bool value)
	{
		pappsettings->set_stealthmode(value);
	}

	bool SettingsPage::RestrictedTokens()
	{
		return pappsettings->restrictedtokens();
	}

	void SettingsPage::RestrictedTokens(bool value)
	{
		pappsettings->set_restrictedtokens(value);
	}

	bool SettingsPage::LangOverride()
	{
		return pappsettings->langoverride();
	}

	void SettingsPage::LangOverride(bool value)
	{
		pappsettings->set_langoverride(value);
	}
}

void winrt::App6::implementation::SettingsPage::LangCombo_SelectionChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& e)
{
	pappsettings->set_lang(LangCombo().SelectedIndex());
}
