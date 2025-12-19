#pragma once

#include "Settings.pb.h"
#include "island.h"

namespace Service::Settings
{
	void LoadSettingsFromFile();
	void WriteSettingsToFile();
	void init_environment();

	inline Service::Proto::Settings g_settings;
	inline IslandEnvironment* penv = nullptr;
	inline Service::Proto::Island* pisland = nullptr;
	inline Service::Proto::LaunchGame* plaunchgame = nullptr;
}



