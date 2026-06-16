#include "pch.h"
#include "SettingsViewModel.h"
#if __has_include("SettingsViewModel.g.cpp")
#include "SettingsViewModel.g.cpp"
#endif
#include "Utils.h"

using namespace Service::Utils;
namespace winrt::App6::implementation
{
	SettingsViewModel::SettingsViewModel()
	{
		CloseBehaviors.Append(ResourceGetString(L"ViewPageSettingsCloseButtonBehaviorExit"));
		CloseBehaviors.Append(ResourceGetString(L"ViewPageSettingsCloseButtonBehaviorMinimize"));
		
	}

	bool SettingsViewModel::IslandRestrictionsOverride()
	{
		return pappsettings->islandrestrictionsoverride();
	}

	void SettingsViewModel::IslandRestrictionsOverride(bool value)
	{
		pappsettings->set_islandrestrictionsoverride(value);
		if (!value && pappsettings->frameratelimitvalue() > 120)
		{
			pisland->set_targetframerate(120);
			penv->TargetFrameRate = 120;
		}
	}

	bool SettingsViewModel::FrameRateLimitOverride()
	{
		return pappsettings->frameratelimitoverride();
	}

	void SettingsViewModel::FrameRateLimitOverride(bool value)
	{
		pappsettings->set_frameratelimitoverride(value);
		if (!value && pappsettings->frameratelimitvalue() > 120 )
		{
			pisland->set_targetframerate(120);
			penv->TargetFrameRate = 120;
		}
	}

	uint32_t SettingsViewModel::FrameRateLimitValue()
	{
		return pappsettings->frameratelimitvalue();
	}

	void SettingsViewModel::FrameRateLimitValue(uint32_t value)
	{
		pappsettings->set_frameratelimitvalue(value);
		if (pappsettings->frameratelimitvalue() < pisland->targetframerate())
		{
			pisland->set_targetframerate(value);
			penv->TargetFrameRate = value;
		}
	}

}
