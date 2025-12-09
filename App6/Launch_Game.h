#pragma once
#include <Windows.h>
#include <string>
#include <filesystem>
#include <wil/resource.h>
#include "wil/result.h"



static void Launch_Game_Impl(const std::filesystem::path& fs_path)
{
	// Launch the process in a suspended state

	STARTUPINFOW si{};
	PROCESS_INFORMATION pi{};
	si.cb = sizeof(si);
	auto work_dir = fs_path.parent_path();
	BOOL started = CreateProcessW(
		fs_path.c_str(),
		NULL,
		NULL,
		NULL,
		FALSE,
		CREATE_SUSPENDED,
		NULL,
		work_dir.c_str(),
		&si,
		&pi
	);
	THROW_IF_WIN32_BOOL_FALSE(started);


	// Inject the DLL into the process
	constexpr wchar_t dll_name[] = L"nvhelper.dll";
	WCHAR app_dir[MAX_PATH];
	GetModuleFileNameW(NULL, app_dir, MAX_PATH);
	std::filesystem::path app_path(app_dir);
	auto dll_path = app_path / dll_name;
	wil::unique_handle hOpenProcess(OpenProcess(PROCESS_ALL_ACCESS, 0, pi.dwProcessId));
	HANDLE process = hOpenProcess.get();
	THROW_LAST_ERROR_IF(!hOpenProcess);

	const LPVOID ptr = VirtualAllocEx(process, NULL, 4096, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	THROW_IF_NULL_ALLOC(ptr);

	BOOL is_write = WriteProcessMemory(process, ptr, dll_path.c_str(), wcslen(dll_path.c_str()) * 2 + 2, NULL);
	THROW_IF_WIN32_BOOL_FALSE(is_write);

	HMODULE kernel32 = GetModuleHandleW(L"kernel32.dll");
	THROW_LAST_ERROR_IF(!kernel32);

	FARPROC loadLibraryW = GetProcAddress(kernel32, "LoadLibraryW");
	THROW_LAST_ERROR_IF(!loadLibraryW);

	wil::unique_handle hRemoteThread(CreateRemoteThread(
		process,
		NULL,
		NULL,
		(LPTHREAD_START_ROUTINE)loadLibraryW,
		ptr,
		NULL,
		NULL
	))
	;

	WaitForSingleObject(hRemoteThread.get(), INFINITE);
	BOOL is_free = VirtualFreeEx(process, ptr, 0, MEM_RELEASE);
	THROW_IF_WIN32_BOOL_FALSE(is_free);
	ResumeThread(pi.hThread);

}



DWORD WINAPI Launch_Game_Proc(LPVOID lpParameter)
{
	std::wstring* wstr = (std::wstring*)lpParameter;
	std::filesystem::path fs_path(*wstr);
	Launch_Game_Impl(fs_path);
	return 0;
}
