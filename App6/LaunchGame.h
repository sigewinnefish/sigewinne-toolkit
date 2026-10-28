#pragma once
#include <string>
#include <filesystem>


namespace Service::Game::Launching
{

	static void LaunchGameImpl(const std::filesystem::path& fs_path);

	static void GetLaunchGameParms(std::wstring& w_path);

	static void SetIfHDROn();

	void Launch();

} 