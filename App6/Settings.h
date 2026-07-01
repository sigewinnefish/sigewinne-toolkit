#pragma once

#include "Settings.pb.h"
#include "island.h"

namespace Service::Settings
{
	void LoadSettingsFromFile();
	void WriteSettingsToFile();
	void Init();
	inline Service::Proto::Settings g_settings;
	
	inline Service::Proto::Island* pisland = nullptr;
	inline Service::Proto::LaunchGame* plaunchgame = nullptr;
	inline Service::Proto::AppSettings* pappsettings = nullptr;
	inline uint64_t oldHash{};
	inline uint64_t newHash{};
}
