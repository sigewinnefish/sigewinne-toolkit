#include "pch.h"
#include "Settings.h"
#include "Windows.h"
#include <wil/resource.h>
#include "wil/result.h"
#include <filesystem>

#include "xxhash.h"
#include "island.h"

namespace Service::Settings
{
	void LoadSettingsFromFile()
	{
		wchar_t exe_path[MAX_PATH];
		THROW_LAST_ERROR_IF(!GetModuleFileNameW(NULL, exe_path, MAX_PATH));
		std::filesystem::path tmp(exe_path);
		tmp.remove_filename() /= L"config";
		wil::unique_handle hFile(
			CreateFileW(
				tmp.c_str(),
				GENERIC_READ | GENERIC_WRITE, 0, 
				NULL,
				OPEN_EXISTING, 
				FILE_ATTRIBUTE_NORMAL,
				NULL
			)
		);
		THROW_LAST_ERROR_IF(!hFile);

		auto file = hFile.get();
		LARGE_INTEGER size;
		THROW_IF_WIN32_BOOL_FALSE(GetFileSizeEx(file, &size));

		const auto parr = std::make_unique<char[]>(size.QuadPart);
		const auto ptr = parr.get();

		BOOL isRead = ReadFile(file, ptr, size.QuadPart, NULL, NULL);
		THROW_IF_WIN32_BOOL_FALSE(isRead);
		THROW_HR_IF(E_FAIL, !g_settings.ParseFromArray(ptr, size.QuadPart));
		oldHash = XXH3_64bits(ptr, size.QuadPart);
	}

	void WriteSettingsToFile()
	{
		const int  size = static_cast<int>(g_settings.ByteSizeLong());
		const auto parr = std::make_unique<char[]>(size);
		const auto ptr = parr.get();
		g_settings.SerializeToArray(ptr, size);
		newHash = XXH3_64bits(ptr, size);
        if (newHash==oldHash)
        {
            return;
        }

		wchar_t exe_path[MAX_PATH];
		THROW_LAST_ERROR_IF(!GetModuleFileNameW(NULL, exe_path, MAX_PATH));
		std::filesystem::path tmp(exe_path);
		tmp.remove_filename() /= L"config";
		wil::unique_handle hFile(
		CreateFileW(
			tmp.c_str(),
				GENERIC_READ | GENERIC_WRITE,
				0, NULL,
				CREATE_ALWAYS,
				FILE_ATTRIBUTE_NORMAL,
				NULL)
		);
		THROW_LAST_ERROR_IF(!hFile);
		THROW_IF_WIN32_BOOL_FALSE(WriteFile(hFile.get(), ptr, size, NULL, NULL));

	}

	void init_environment()
	{
		if (!penv)
		{
			DWORD array[] = {
				0x1560ec0, 0x15b73330, 0x106a3c0, 0x106a3b0, 0xc835b70, 0x608d620, 0x406330, 0x71a6ee0, 0xe47e1b0, 0xe4851e0,
				0xfeafc10, 0x69ea500, 0x9199950, 0xa98f410, 0x1063c50, 0x1063450, 0xfa87490, 0x1084e9e0, 0x105c2c10
			};

			HANDLE h = OpenFileMapping(FILE_MAP_READ | FILE_MAP_WRITE, FALSE, L"4F3E8543-40F7-4808-82DC-21E48A6037A7"); //4F3E8543-40F7-4808-82DC-21E48A6037A7

			if (h)
			{
				penv = (IslandEnvironment*)MapViewOfFile(_Notnull_ h, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);
				goto loc_1;
			}

			h = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_EXECUTE_READWRITE, 0, 1024, L"4F3E8543-40F7-4808-82DC-21E48A6037A7");
			penv = (IslandEnvironment*)MapViewOfFile(_Notnull_ h, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);
			ZeroMemory(penv, sizeof(IslandEnvironment));

			memcpy(reinterpret_cast<char*>(penv), &array, sizeof(array));

loc_1:		plaunchgame = g_settings.mutable_home()->mutable_launchgame();
			pisland = g_settings.mutable_home()->mutable_island();
			pappsettings = g_settings.mutable_appsettings();
			
			// island default
			if (!static_cast<int>(pisland->fieldofview()))
			{
				pisland->set_fieldofview(45);
			}
			if (!pisland->targetframerate())
			{
				pisland->set_targetframerate(60);
			}

			// launchgame default
			if (!plaunchgame->screenwidth())
			{
				plaunchgame->set_screenwidth(2560);
			}

			if (!plaunchgame->screenheight())
			{
				plaunchgame->set_screenheight(1440);
			}
			
			penv->FieldOfView = pisland->fieldofview();
			penv->TargetFrameRate = pisland->targetframerate();
			penv->EnableSetFieldOfView = pisland->enablesetfieldofview();
			penv->FixLowFovScene = pisland->fixlowfovscene();
			penv->DisableFog = pisland->disablefog();
			penv->EnableSetTargetFrameRate = pisland->enablesettargetframerate();
			penv->RemoveOpenTeamProgress = pisland->removeopenteamprogress();
			penv->HideQuestBanner = pisland->hidequestbanner();
			penv->DisableEventCameraMove = pisland->disableeventcameramove();
			penv->DisableShowDamageText = pisland->disableshowdamagetext();
			penv->UsingTouchScreen = pisland->usingtouchscreen();
			penv->RedirectCombineEntry = pisland->redirectcombineentry();
			penv->HideUid = pisland->hideuid();
		}
	}
}

