#include "pch.h"
#include "App.xaml.h"

#include <Settings.h>
#include <LaunchGame.h>
#include "MainWindow.xaml.h"
#include <winrt/Microsoft.Windows.Globalization.h>


using namespace winrt;
using namespace winrt::Microsoft::UI::Xaml;
using namespace winrt::Microsoft::Windows::Globalization;
using namespace Service::Settings;
// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

int __stdcall wWinMain(HINSTANCE, HINSTANCE, PWSTR, int)
{
    HANDLE hMutex = CreateMutexW(NULL, FALSE, L"1864d952-c1dd-441a-8756-1b96fb9ff89e"); // instance guid
    if (GetLastError() == ERROR_ALREADY_EXISTS)
    {
        TerminateProcess(GetCurrentProcess(), 0);
    }
    
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
            LoadSettingsFromFile();
	    }
	    catch (...)
	    {
	    	MessageBoxW(0, L"LoadSettingsFromFile Error, ignore if FIRSTRUN", L"Warn", MB_OK | MB_ICONWARNING);
	    }
        init_environment();
	    if (pappsettings->stealthmode())
	    {
            std::string_view tmp = g_settings.mutable_home()->gamepath();
            Service::LaunchGame::g_path = std::wstring(tmp.begin(),tmp.end());
			Service::LaunchGame::Launch();

	    }

	    if (pappsettings->langoverride())
	    {
            switch (pappsettings->lang())
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

        window = make<MainWindow>();
    }

    void App::ToForeground()
    {
        assert(app != nullptr);

        HWND hwnd;
        auto windowNative{ app->window.as<IWindowNative>() };
        if (windowNative && SUCCEEDED(windowNative->get_WindowHandle(&hwnd)))
        {
            SwitchToThisWindow(hwnd, TRUE);
        }
    }

    App::~App() noexcept
    {
        try
        {
            WriteSettingsToFile();
        }
        catch (...)
        {
            MessageBoxW(0, L"WriteSettingsToFile Error", L"Warn", MB_OK | MB_ICONWARNING);
            abort();
        }
    }
}
