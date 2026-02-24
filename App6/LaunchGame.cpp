#include "pch.h"
#include <Windows.h>
#include <string>
#include <filesystem>
#include "LaunchGame.h"
#include <wil/resource.h>
#include "wil/result.h"
#include "Settings.h"
#include "Utils.h"
using namespace Service::Utils::Message;
using namespace Service::Settings;

namespace Service::Game::Launching
{
	
	static void LaunchGameImpl()
	{
		WCHAR filename[MAX_PATH];
		DWORD len = GetModuleFileNameW(NULL, filename, MAX_PATH);
		THROW_HR_IF(HRESULT_FROM_WIN32(GetLastError()), len == 0);
		std::filesystem::path appname(filename);
		appname = appname.parent_path();
		appname += L"\\toolkit_fulltrust.exe";

		g_path = std::wstring(
			pappsettings->gamepath().begin(),
			pappsettings->gamepath().end()
		);
		SetIfHDROn();
		GetLaunchGameParms();
		// Launch the process in a suspended state
		STARTUPINFOW si{};
		PROCESS_INFORMATION pi{};
		si.cb = sizeof(si);
		std::filesystem::path fs_path(g_path);
		auto work_dir = fs_path.parent_path();
		BOOL started = CreateProcessW(
			appname.c_str(),
			const_cast<LPWSTR>(g_path.c_str()),
			NULL,
			NULL,
			FALSE,
			NULL,
			NULL,
			work_dir.c_str(),
			&si,
			&pi
		);
		THROW_IF_WIN32_BOOL_FALSE(started);
		wil::unique_handle hProcess{ pi.hProcess };
		wil::unique_handle hThread{ pi.hThread };
		
	}

	static void GetLaunchGameParms()
	{
		wchar_t width[10];
		wchar_t height[10];
		auto params_arr = std::vector<std::pair<const wchar_t*, const wchar_t*>>();

		if (plaunchgame->arecommandlineargumentsenabled())
		{
			if (plaunchgame->isexclusive())
			{
				auto ExclusiveParm = std::pair{ L"-window-mode", L"exclusive" };
				params_arr.emplace_back(ExclusiveParm);
			}
			if (plaunchgame->isfullscreen())
			{
				auto FullScreenParm = std::pair{ L"-screen-fullscreen", L"" };
				params_arr.emplace_back(FullScreenParm);
			}
			if (plaunchgame->isborderless())
			{
				auto BorderlessParm = std::pair{ L"-popupwindow", L"" };
				params_arr.emplace_back(BorderlessParm);
			}
			if (plaunchgame->isscreenwidthenabled())
			{
				_itow_s(plaunchgame->screenwidth(), width, 10);
				auto ScreenWidthParm = std::pair{ L"-screen-width", width };
				params_arr.emplace_back(ScreenWidthParm);
			}
			if (plaunchgame->isscreenheightenabled())
			{
				_itow_s(plaunchgame->screenheight(), height, 10);
				auto ScreenHeightParm = std::pair{ L"-screen-height", height };
				params_arr.emplace_back(ScreenHeightParm);
			}

			for (const auto& arg : params_arr)
			{
				g_path += L" ";
				g_path += arg.first;
				if (*arg.second != 0)
				{
					g_path += L" ";
					g_path += arg.second;
				}

			}
		}

	}

	void SetIfHDROn()
	{
		if (plaunchgame->iswindowshdrenabled())
		{
			HKEY hKey = NULL;
			uint32_t value = 1;
			constexpr WCHAR subKey[] = L"Software\\miHoYo\\\u539f\u795e";
			THROW_IF_WIN32_ERROR(RegCreateKeyExW(HKEY_CURRENT_USER, subKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, NULL));
			THROW_IF_WIN32_ERROR(RegSetValueExW(hKey, L"WINDOWS_HDR_ON_h3132281285", NULL, REG_DWORD, (BYTE*)&value, sizeof(value)));
			THROW_IF_WIN32_ERROR(RegCloseKey(hKey));
		}

	}

	void Launch()
	{
		wil::unique_handle hThread(CreateThread(NULL, 0, [](LPVOID) -> DWORD
		{
			try
			{
				LaunchGameImpl();
			}
			catch (...)
			{
				ShowMessageBox(L"MBLaunchGameError", Error);
			}
			return 0;
		}, NULL, 0, NULL));
		THROW_LAST_ERROR_IF(!hThread);
	}

	void LaunchIfStealthMode()
	{
		if (pappsettings->stealthmode())
		{
			Launch();
		}
	}
}

