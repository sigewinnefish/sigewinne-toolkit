#include "pch.h"
#include "Settings.h"
#include "Windows.h"
#include <wil/resource.h>
#include "wil/result.h"
#include <filesystem>

#include "xxhash.h"
#include "Utils.h"

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
				GENERIC_READ | GENERIC_WRITE,
				0, 
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
				0,
				NULL,
				CREATE_ALWAYS,
				FILE_ATTRIBUTE_NORMAL,
				NULL)
		);
		THROW_LAST_ERROR_IF(!hFile);
		THROW_IF_WIN32_BOOL_FALSE(WriteFile(hFile.get(), ptr, size, NULL, NULL));

	}

	void Init()
	{
		try
		{
			LoadSettingsFromFile();
		}
		catch (...)
		{
			ShowMessageBox(L"MBLoadSettingsFromFileWarn", Utils::Message::Warn);
		}

		plaunchgame = g_settings.mutable_home()->mutable_launchgame();
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

		// appsettings default
		if (!pappsettings->frameratelimitvalue())
		{
			pappsettings->set_frameratelimitvalue(120);
		}
	}

}

