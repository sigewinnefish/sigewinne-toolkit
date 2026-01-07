#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif
#include <winrt/Microsoft.UI.Interop.h>
#include <winrt/Windows.UI.Xaml.Interop.h>
#include <winrt/Microsoft.Windows.ApplicationModel.Resources.h>
#include "resource.h"
#include <commctrl.h>
#include <Settings.h>

using namespace Service::Settings;
using namespace Microsoft::Windows::ApplicationModel::Resources;
// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::App6::implementation
{

	MainWindow::MainWindow()
	{
		InitWindow();
		// Xaml objects should not call InitializeComponent during construction.
		// See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
	}

    HWND MainWindow::GetWindowHandle()
    {
        if (_hwnd == nullptr)
        {
            Window window = *this;
            window.as<IWindowNative>()->get_WindowHandle(&_hwnd);
        }
        return _hwnd;
    }

    void MainWindow::AddNotifyIcon()
    {

		//https://stackoverflow.com/questions/73628384/winui-3-c-winrt-loading-string-resources
		//ResourceManager rm{};
		//auto str = rm.MainResourceMap().GetValue(L"Resources/String1").ValueAsString();
		
		ResourceLoader loader;
		hstring appname = loader.GetString(L"NotifyIconName");

		guid gNotifyIcon("21a2acbc-3a44-43c8-860a-f8e7151b2623");
		NOTIFYICONDATAW nid = {};
		nid.cbSize = sizeof(NOTIFYICONDATAW);
		nid.hWnd = GetWindowHandle();
		nid.uID = 0;
		nid.guidItem = gNotifyIcon;
		nid.hBalloonIcon = 0;
		nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_SHOWTIP | NIF_TIP | NIF_GUID | NIF_STATE;
		nid.uCallbackMessage = NotifyIconCallbackMessage;
		nid.hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		wcscpy_s(nid.szTip, appname.c_str());
		if (Shell_NotifyIconW(NIM_ADD, &nid))
		{
			Shell_NotifyIconW(NIM_SETVERSION, &nid);
		}
		
    }

    void MainWindow::Exp1()
	{
		typedef __int64(*put_PersistedStateId)(__int64 a1, __int64 a2);
		typedef __int64(*put_PlacementRestorationBehavior)(__int64 a1, __int64 a2);

		void* result{};
		guid gIAppWindowExperimental("04DB96C7-DEB6-5BE4-BFDC-1BC0361C8A12"); // IAppWindowExperimental
		this->AppWindow().try_as<IUnknown>()->QueryInterface(gIAppWindowExperimental, &result);
		auto vt = *(int64_t*)result;
		const auto k = guid{ L"{1ed4408f-9732-4543-aa46-8758439652e6}" }; // guid, per window
		auto func = reinterpret_cast<put_PlacementRestorationBehavior*>((char*)vt + 0x48);
		(*func)((__int64)result, 0);
		Windows::Foundation::IReference kk(k);
		auto func2 = reinterpret_cast<put_PersistedStateId*>((char*)vt + 0x38);
		(*func2)((__int64)result, (__int64)(*(__int64*)&kk));
		reinterpret_cast<IUnknown*>(result)->Release();
	}
	void MainWindow::Exp2()
	{
		typedef __int64(*SaveCurrentPlacement)(__int64 a1);

		void* result{};
		guid gIAppWindowExperimental("04DB96C7-DEB6-5BE4-BFDC-1BC0361C8A12"); // IAppWindowExperimental
		this->AppWindow().try_as<IUnknown>()->QueryInterface(gIAppWindowExperimental, &result);
		auto vt = *(int64_t*)result;
		auto func3 = reinterpret_cast<SaveCurrentPlacement*>((char*)vt + 0x58);
		(*func3)((__int64)result);
		reinterpret_cast<IUnknown*>(result)->Release();
	}

	void MainWindow::InitWindow()
	{
		// TitleBar

		this->ExtendsContentIntoTitleBar(true); // this should be first
		this->AppWindow().TitleBar().PreferredHeightOption(TitleBarHeightOption::Tall);
		this->AppWindow().TitleBar().PreferredTheme(TitleBarTheme::UseDefaultAppMode);
		this->AppWindow().SetIcon(L"Assets\\Logo.ico");

		// Window

		UINT dpi = GetDpiForWindow(GetWindowHandle());
		THROW_HR_IF(E_INVALIDARG, 0 == dpi);
		auto scale = floorf(dpi * 100.0f / 96.0f + 0.5f) / 100.0f;
		this->AppWindow().Presenter().try_as<OverlappedPresenter>().PreferredMinimumWidth(static_cast<int32_t>(1000 * scale));
		this->AppWindow().Presenter().try_as<OverlappedPresenter>().PreferredMinimumHeight(static_cast<int32_t>(600 * scale));

		// NotifyIcon

		this->TaskbarCreatedMessage = RegisterWindowMessageW(L"TaskbarCreated");
		this->NotifyIconCallbackMessage = RegisterWindowMessageW(L"SigewinneToolkitNotifyIconCallback");
		this->AddNotifyIcon();

		SetWindowSubclass(GetWindowHandle(),
			[](HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)->LRESULT
			{
				#define this reinterpret_cast<MainWindow*>(dwRefData)

				if (uMsg == this->NotifyIconCallbackMessage)
				{
					if (LOWORD(lParam) == WM_RBUTTONUP || LOWORD(lParam) == WM_LBUTTONUP)
					{
						reinterpret_cast<MainWindow*>(dwRefData)->Activate();

					}

				}
				if (uMsg == this->TaskbarCreatedMessage)
				{
					this->AddNotifyIcon();
				}
				return DefSubclassProc(hWnd, uMsg, wParam, lParam);

				#undef this
			},
			1, reinterpret_cast<DWORD_PTR>(this));

		//  Callback

		this->AppWindow().Closing([this](auto sender, AppWindowClosingEventArgs args)
			{
				args.Cancel(false);

			});

		// ShowWindow

		this->Exp1();
		this->Activate();
		if (pappsettings->stealthmode())
		{
			this->AppWindow().Hide();
		}

	}

	void MainWindow::Window_Closed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::WindowEventArgs const& args)
	{
		Exp2();
	}
}


