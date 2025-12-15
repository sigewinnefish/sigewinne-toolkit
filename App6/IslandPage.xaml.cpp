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

	void IslandPage::make_environment()
	{
		if (!penv)
		{
			HANDLE h = OpenFileMapping(FILE_MAP_READ | FILE_MAP_WRITE, FALSE, L"4F3E8543-40F7-4808-82DC-21E48A6037A7"); //4F3E8543-40F7-4808-82DC-21E48A6037A7

			if (h)
			{
				penv = (IslandEnvironment*)MapViewOfFile(_Notnull_ h, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);
				return;
			}

			h = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_EXECUTE_READWRITE, 0, 1024, L"4F3E8543-40F7-4808-82DC-21E48A6037A7");
			penv = (IslandEnvironment*)MapViewOfFile(_Notnull_ h, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);
			ZeroMemory(penv, sizeof(IslandEnvironment));

			DWORD array[] = {
				0xc4007c0, 0x5e0d680, 0x3e87b0, 0x7728b90, 0, 0x10407c0, 0x14f2cb90, 0x125a050, 0x14f18ea0, 0xb8dcfa0,
				0xb8e5fb0, 0x954f230, 0xdbb1320, 0x14f1bf20, 0x14f1bc60, 0xe076e80, 0xfea2160, 0xab06670, 0xa0a2d00,
				0x84fb720, 0, 0, 0, 0, 0
			};

			memcpy(reinterpret_cast<char*>(&penv) + 16u, &array, sizeof(array));
		}
	}

}
