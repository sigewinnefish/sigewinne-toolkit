#include "pch.h"
#include "SettingsViewModel.h"
#if __has_include("SettingsViewModel.g.cpp")
#include "SettingsViewModel.g.cpp"
#endif

namespace winrt::App6::implementation
{

	bool SettingsViewModel::StealthMode()
	{
		return pappsettings->stealthmode();
	}

	void SettingsViewModel::StealthMode(bool value)
	{
		pappsettings->set_stealthmode(value);
	}

	bool SettingsViewModel::RestrictedTokens()
	{
		return pappsettings->restrictedtokens();
	}

	void SettingsViewModel::RestrictedTokens(bool value)
	{
		pappsettings->set_restrictedtokens(value);
	}

	bool SettingsViewModel::LangOverride()
	{
		return pappsettings->langoverride();
	}

	void SettingsViewModel::LangOverride(bool value)
	{
		pappsettings->set_langoverride(value);
	}
	
	bool SettingsViewModel::IslandRestrictionsOverride()
	{
		return pappsettings->islandrestrictionsoverride();
	}

	void SettingsViewModel::IslandRestrictionsOverride(bool value)
	{
		pappsettings->set_islandrestrictionsoverride(value);
		if (!value)
		{
			pisland->set_targetframerate(120);
			penv->TargetFrameRate = value;
		}
	}

	bool SettingsViewModel::FrameRateLimitOverride()
	{
		return pappsettings->frameratelimitoverride();
	}

	void SettingsViewModel::FrameRateLimitOverride(bool value)
	{
		pappsettings->set_frameratelimitoverride(value);
		if (!value)
		{
			pisland->set_targetframerate(120);
			penv->TargetFrameRate = value;
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
