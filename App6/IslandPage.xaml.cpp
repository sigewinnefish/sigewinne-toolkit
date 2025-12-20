#include "pch.h"
#include "IslandPage.xaml.h"
#if __has_include("IslandPage.g.cpp")
#include "IslandPage.g.cpp"
#endif

#include "Settings.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;
using namespace Windows::Foundation;
using namespace Service::Settings;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::App6::implementation
{
	IslandPage::IslandPage()
	{
		this->NavigationCacheMode(Microsoft::UI::Xaml::Navigation::NavigationCacheMode::Required);
		// Xaml objects should not call InitializeComponent during construction.
		// See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
	}

	float IslandPage::FieldOfView()
	{
		return pisland->fieldofview();
	}

	void IslandPage::FieldOfView(float value)
	{
		pisland->set_fieldofview(value);
		penv->FieldOfView = value;
	}

	uint32_t IslandPage::TargetFrameRate()
	{
		return pisland->targetframerate();
	}

	void IslandPage::TargetFrameRate(uint32_t value)
	{
		pisland->set_targetframerate(value);
		penv->TargetFrameRate = value;
	}

	bool IslandPage::EnableSetFieldOfView()
	{
		return pisland->enablesetfieldofview();
	}

	void IslandPage::EnableSetFieldOfView(bool value)
	{
		pisland->set_enablesetfieldofview(value);
		penv->EnableSetFieldOfView = value;
	}

	bool IslandPage::FixLowFovScene()
	{
		return pisland->fixlowfovscene();
	}

	void IslandPage::FixLowFovScene(bool value)
	{
		pisland->set_fixlowfovscene(value);
		penv->FixLowFovScene = value;
	}

	bool IslandPage::DisableFog()
	{
		return pisland->disablefog();
	}

	void IslandPage::DisableFog(bool value)
	{
		pisland->set_disablefog(value);
		penv->DisableFog = value;
	}

	bool IslandPage::EnableSetTargetFrameRate()
	{
		return pisland->enablesettargetframerate();
	}

	void IslandPage::EnableSetTargetFrameRate(bool value)
	{
		pisland->set_enablesettargetframerate(value);
		penv->EnableSetTargetFrameRate = value;
	}

	bool IslandPage::RemoveOpenTeamProgress()
	{
		return pisland->removeopenteamprogress();
	}

	void IslandPage::RemoveOpenTeamProgress(bool value)
	{
		pisland->set_removeopenteamprogress(value);
		penv->RemoveOpenTeamProgress = value;
	}

	bool IslandPage::HideQuestBanner()
	{
		return pisland->hidequestbanner();
	}

	void IslandPage::HideQuestBanner(bool value)
	{
		pisland->set_hidequestbanner(value);
		penv->HideQuestBanner = value;
	}

	bool IslandPage::DisableEventCameraMove()
	{
		return pisland->disableeventcameramove();
	}

	void IslandPage::DisableEventCameraMove(bool value)
	{
		pisland->set_disableeventcameramove(value);
		penv->DisableEventCameraMove = value;
	}

	bool IslandPage::DisableShowDamageText()
	{
		return pisland->disableshowdamagetext();
	}

	void IslandPage::DisableShowDamageText(bool value)
	{
		pisland->set_disableshowdamagetext(value);
		penv->DisableShowDamageText = value;
	}

	bool IslandPage::UsingTouchScreen()
	{
		return pisland->usingtouchscreen();
	}

	void IslandPage::UsingTouchScreen(bool value)
	{
		pisland->set_usingtouchscreen(value);
		penv->UsingTouchScreen = value;
	}

	bool IslandPage::RedirectCombineEntry()
	{
		return pisland->redirectcombineentry();
	}

	void IslandPage::RedirectCombineEntry(bool value)
	{
		pisland->set_redirectcombineentry(value);
		penv->RedirectCombineEntry = value;
	}

	bool IslandPage::ResinListItemAllowOriginalResin()
	{
		return 1;
	}

	void IslandPage::ResinListItemAllowOriginalResin(bool value)
	{

	}

	bool IslandPage::ResinListItemAllowPrimogem()
	{
		return 1;
	}

	void IslandPage::ResinListItemAllowPrimogem(bool value)
	{
	}

	bool IslandPage::ResinListItemAllowFragileResin()
	{
		return 1;
	}

	void IslandPage::ResinListItemAllowFragileResin(bool value)
	{
	}

	bool IslandPage::ResinListItemAllowTransientResin()
	{
		return 1;
	}

	void IslandPage::ResinListItemAllowTransientResin(bool value)
	{
	}

	bool IslandPage::ResinListItemAllowCondensedResin()
	{
		return 1;
	}

	void IslandPage::ResinListItemAllowCondensedResin(bool value)
	{

	}

	

}
