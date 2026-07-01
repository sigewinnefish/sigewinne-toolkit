#include "pch.h"
#include "App.xaml.h"
#include <wil/resource.h>
#include <Settings.h>
#include <LaunchGame.h>
#include "MainWindow.xaml.h"
#include <winrt/Microsoft.Windows.Globalization.h>
#include "tlhelp32.h"
#include "DbgHelp.h"
#include <filesystem>


#include "Utils.h"
using namespace Service::Utils::Message;
using namespace Service::Game::Launching;

// TLS Callback to ensure single instance
VOID WINAPI tls_callback1(
    PVOID DllHandle,
    DWORD Reason,
    PVOID Reserved)
{
    if (Reason == DLL_PROCESS_ATTACH) //PROCESS start
    {
        HANDLE hMutex = CreateMutexW(NULL, FALSE, L"1864d952-c1dd-441a-8756-1b96fb9ff89e"); // instance GUID
        if (GetLastError() == ERROR_ALREADY_EXISTS)
        {
            wil::unique_handle hSnapshot(CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0));

            if (hSnapshot.get() != INVALID_HANDLE_VALUE)
            {
                wchar_t buffer[MAX_PATH];
                GetModuleFileNameW(NULL, buffer, MAX_PATH);
				std::filesystem::path path(buffer);

                DWORD pid = GetCurrentProcessId();
                PROCESSENTRY32W pe{};
                pe.dwSize = sizeof(PROCESSENTRY32W);
                if (Process32FirstW(hSnapshot.get(), &pe))
                {
                    do
                    {
                        if (_wcsicmp(pe.szExeFile, path.filename().c_str()) == 0 && pid != pe.th32ProcessID)
                        {
                            wil::unique_handle hOpenProcess(OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe.th32ProcessID));
                            THROW_LAST_ERROR_IF(!hOpenProcess);
                            HANDLE process = hOpenProcess.get();
                            wil::unique_handle hRemoteThread(CreateRemoteThread(
                                process,
                                NULL,
                                NULL,
                                (LPTHREAD_START_ROUTINE)LaunchIfStealthMode,
                                NULL,
                                NULL,
                                NULL
                            ));
                            THROW_LAST_ERROR_IF(!hRemoteThread);
                            break;
                        }
                    } while (Process32NextW(hSnapshot.get(), &pe));
                }
			}

            TerminateProcess(GetCurrentProcess(), 0);
        }
    }
}

#pragma comment (linker, "/INCLUDE:_tls_used")
#pragma comment (linker, "/INCLUDE:p_tls_callback1")
#pragma const_seg(push)
#pragma const_seg(".CRT$XLAAA")
EXTERN_C const PIMAGE_TLS_CALLBACK p_tls_callback1 = tls_callback1;
#pragma const_seg(pop)

using namespace winrt;
using namespace winrt::Microsoft::UI::Xaml;
using namespace winrt::Microsoft::Windows::Globalization;
using namespace Service;
// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

int __stdcall wWinMain(HINSTANCE, HINSTANCE, PWSTR, int)
{
    SetUnhandledExceptionFilter([](_EXCEPTION_POINTERS* pException) ->LONG
    {
        WCHAR buffer[MAX_PATH];
        GetTempPath2W(MAX_PATH, buffer);
        wcscat_s(buffer, MAX_PATH, L"toolkit.dmp");
        wil::unique_handle hFile{
            CreateFileW(buffer,
                GENERIC_READ | GENERIC_WRITE,
                0,
                NULL,
                CREATE_ALWAYS,
                FILE_ATTRIBUTE_NORMAL,
                NULL
        ) };

        if (hFile)
        {
            MINIDUMP_EXCEPTION_INFORMATION exInfo = {};
            exInfo.ThreadId = GetCurrentThreadId();
            exInfo.ExceptionPointers = pException;
            exInfo.ClientPointers = FALSE;

            MiniDumpWriteDump(
                GetCurrentProcess(),
                GetCurrentProcessId(),
                hFile.get(),
                MiniDumpNormal,
                &exInfo,
                NULL,
                NULL
            );
            ShowMessageBox(L"MBAppCrash", Error);
        }

        return EXCEPTION_EXECUTE_HANDLER;
    });

    winrt::init_apartment(winrt::apartment_type::single_threaded);
    ::winrt::Microsoft::UI::Xaml::Application::Start(
        [](auto&&)
        {
            ::winrt::make<::winrt::App6::implementation::App>();
        });

    return 0;
}

namespace winrt::App6::implementation
{
    static App* app{ nullptr };
    /// <summary>
    /// Initializes the singleton application object.  This is the first line of authored code
    /// executed, and as such is the logical equivalent of main() or WinMain().
    /// </summary>
    App::App()
    {
		
        // Xaml objects should not call InitializeComponent during construction.
        // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent

#if defined _DEBUG && !defined DISABLE_XAML_GENERATED_BREAK_ON_UNHANDLED_EXCEPTION
        UnhandledException([](IInspectable const&, UnhandledExceptionEventArgs const& e)
        {
            if (IsDebuggerPresent())
            {
                auto errorMessage = e.Message();
                __debugbreak();
            }
        });
#endif
        app = this;
    }

    /// <summary>
    /// Invoked when the application is launched.
    /// </summary>
    /// <param name="e">Details about the launch request and process.</param>
    void App::OnLaunched([[maybe_unused]] LaunchActivatedEventArgs const& e)
    {
	    try
	    {
            Settings::LoadSettingsFromFile();
	    }
	    catch (...)
	    {
            ShowMessageBox(L"MBLoadSettingsFromFileWarn", Warn);
	    }

        Settings::Init();
        Island::Init();

        LaunchIfStealthMode();

	    if (Settings::pappsettings->langoverride())
	    {
            switch (Settings::pappsettings->lang())
            {
            case 0:
                ApplicationLanguages::PrimaryLanguageOverride(L"en-us");
                break;
            case 1:
                ApplicationLanguages::PrimaryLanguageOverride(L"zh-cn");
                break;
            default:
                break;
            }
	    }

        mainWindow = make<MainWindow>();
        
    }

    void App::ToForeground()
    {
        assert(app != nullptr);

        HWND hwnd;
        auto windowNative{ app->mainWindow.as<IWindowNative>() };
        if (windowNative && SUCCEEDED(windowNative->get_WindowHandle(&hwnd)))
        {
            SwitchToThisWindow(hwnd, TRUE);
        }
    }

    App::~App() noexcept
    {
        try
        {
            Settings::WriteSettingsToFile();
        }
        catch (...)
        {
            MessageBoxW(0, L"WriteSettingsToFile Error", L"Warn", MB_OK | MB_ICONWARNING);
            abort();
        }
    }
}
