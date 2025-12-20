#include "pch.h"
#include "LaunchGamePage.xaml.h"
#if __has_include("LaunchGamePage.g.cpp")
#include "LaunchGamePage.g.cpp"
#endif
#include "Settings.h"

using namespace Service::Settings;
using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::App6::implementation
{
	bool LaunchGamePage::LaunchGameWindowsHDR()
	{
		return plaunchgame->iswindowshdrenabled();
	}

	void LaunchGamePage::LaunchGameWindowsHDR(bool value)
	{
		plaunchgame->set_iswindowshdrenabled(value);
	}

	bool LaunchGamePage::LaunchGameArguments()
	{
		return plaunchgame->arecommandlineargumentsenabled();
	}

	void LaunchGamePage::LaunchGameArguments(bool value)
	{
		plaunchgame->set_arecommandlineargumentsenabled(value);
	}

	bool LaunchGamePage::LaunchGameAppearanceExclusive()
	{
		return plaunchgame->isexclusive();
	}

	void LaunchGamePage::LaunchGameAppearanceExclusive(bool value)
	{
		plaunchgame->set_isexclusive(value);
	}

	bool LaunchGamePage::LaunchGameAppearanceFullscreen()
	{
		return plaunchgame->isfullscreen();
	}

	void LaunchGamePage::LaunchGameAppearanceFullscreen(bool value)
	{
		plaunchgame->set_isfullscreen(value);
	}

	bool LaunchGamePage::LaunchGameAppearanceBorderless()
	{
		return plaunchgame->isborderless();
	}

	void LaunchGamePage::LaunchGameAppearanceBorderless(bool value)
	{
		plaunchgame->set_isborderless(value);
	}

	bool LaunchGamePage::LaunchGameAppearanceScreenWidth()
	{
		return plaunchgame->isscreenwidthenabled();
	}

	void LaunchGamePage::LaunchGameAppearanceScreenWidth(bool value)
	{
		plaunchgame->set_isscreenwidthenabled(value);
	}

	bool LaunchGamePage::LaunchGameAppearanceScreenHeight()
	{
		return plaunchgame->isscreenheightenabled();
	}

	void LaunchGamePage::LaunchGameAppearanceScreenHeight(bool value)
	{
		plaunchgame->set_isscreenheightenabled(value);
	}

	uint32_t LaunchGamePage::LaunchGameAppearanceScreenWidthValue()
	{
		return plaunchgame->screenwidth();
	}

	void LaunchGamePage::LaunchGameAppearanceScreenWidthValue(uint32_t value)
	{
		plaunchgame->set_screenwidth(value);
	}

	uint32_t LaunchGamePage::LaunchGameAppearanceScreenHeightValue()
	{
		return plaunchgame->screenheight();
	}

	void LaunchGamePage::LaunchGameAppearanceScreenHeightValue(uint32_t value)
	{
		plaunchgame->set_screenheight(value);
	}

	LaunchGamePage::LaunchGamePage()
	{
		this->NavigationCacheMode(Microsoft::UI::Xaml::Navigation::NavigationCacheMode::Required);
		// Xaml objects should not call InitializeComponent during construction.
		// See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
	}
}
