#include "pch.h"
#include <Windows.h>
#include <wil/resource.h>
#include "wil/result.h"

namespace Service::Game::FileSystem
{
	void GamePathDetect(_Inout_ WCHAR* path)
	{
		HKEY hKey = NULL;
		DWORD cb;
		constexpr WCHAR subKey[] = L"Software\\miHoYo\\HYP\\1_1\\hk4e_cn";
		THROW_IF_WIN32_ERROR(RegCreateKeyExW(HKEY_CURRENT_USER, subKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_READ, NULL, &hKey, NULL));
		THROW_IF_WIN32_ERROR(RegGetValueW(hKey, NULL, L"GameInstallPath", RRF_RT_REG_SZ, NULL, path, &cb));
		THROW_IF_WIN32_ERROR(RegCloseKey(hKey));
	}
}

