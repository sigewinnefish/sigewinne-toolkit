#include "pch.h"
#include "Controller.h"
#include "resource.h"
#include "Utils.h"
#include <commctrl.h>

#include "MainWindow.xaml.h"
#include "NotifyIconContextMenu.xaml.h"

using namespace Service::Utils;
using namespace winrt::Microsoft::UI::Xaml;
using namespace winrt::Microsoft::UI::Xaml::Controls::Primitives;


namespace Service::NotifyIcon
{
    void Controller::Init()
    {
		CreateNotifyIconHostWindow();
        InitMessage();
		AddNotifyIcon();
		SetCallback();
    }

    void Controller::CreatePopupWindow()
    {
        Window notifyIconWindow = Window{};;
        //notifyIconWindow.as<IWindowNative>()->get_WindowHandle(&notifyIconWindowhwnd); // get hwnd immediately

        notifyIconWindow.Title(L"NotifyIconXamlHost");
        notifyIconWindow.AppWindow().IsShownInSwitchers(false);


        auto border = Controls::Border{};
        border.Loaded([notifyIconWindow](auto&&, auto&&) {
            auto flyout = make<winrt::App6::implementation::NotifyIconContextMenu>();
            FlyoutShowOptions options;
            options.Position(Windows::Foundation::Point{ 1,2 });
            options.Placement(FlyoutPlacementMode::Auto);
            options.ShowMode(FlyoutShowMode::Standard);
            flyout.XamlRoot(notifyIconWindow.Content().XamlRoot());
            flyout.ShowAt(notifyIconWindow.Content(), options);
            });
        notifyIconWindow.Content(border);
        notifyIconWindow.Activate();
    }

    void Controller::AddNotifyIcon()
    {
		hstring appname = ResourceGetString((L"NotifyIconName"));
		guid gNotifyIcon("21a2acbc-3a44-43c8-860a-f8e7151b2623");
		NOTIFYICONDATAW nid = {};
		nid.cbSize = sizeof(NOTIFYICONDATAW);
		nid.hWnd = m_hwnd;
		nid.uID = 0;
		nid.guidItem = gNotifyIcon;
		nid.hBalloonIcon = 0;
		nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_SHOWTIP | NIF_TIP | NIF_GUID | NIF_STATE;
		nid.uCallbackMessage = m_NotifyIconCallbackMessage;
		nid.hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		wcscpy_s(nid.szTip, appname.c_str());
		if (Shell_NotifyIconW(NIM_ADD, &nid))
		{
			Shell_NotifyIconW(NIM_SETVERSION, &nid);
		}
    }

    void Controller::CreateNotifyIconHostWindow()
    {
        constexpr WCHAR name[] = L"NotifyIconMessageWindowClass";
        WNDCLASSEXW wc{};
        wc.cbSize = sizeof(wc);
        wc.lpfnWndProc = DefWindowProcW;
        wc.hInstance = GetModuleHandleW(0);
        wc.lpszClassName = name;
		THROW_LAST_ERROR_IF(!RegisterClassExW(&wc));
        m_hwnd = CreateWindowExW(
            0,
            name,
            L"",
            0,
            0,
            0,
            0,
            0,
            NULL,
            NULL,
            wc.hInstance,
            NULL
        );
		THROW_LAST_ERROR_IF_NULL(m_hwnd);

    }

    void Controller::InitMessage()
    {

		m_TaskbarCreatedMessage = RegisterWindowMessageW(L"TaskbarCreated");
		m_NotifyIconCallbackMessage = RegisterWindowMessageW(L"SigewinneToolkitNotifyIconCallback");
    }

    void Controller::SetCallback()
    {
		SetWindowSubclass(m_hwnd,
			[](HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)->LRESULT
			{
				auto ptr = reinterpret_cast<Controller*>(dwRefData);


				if (uMsg == ptr->m_NotifyIconCallbackMessage)
				{
					if (LOWORD(lParam) == WM_RBUTTONUP || LOWORD(lParam) == WM_LBUTTONUP)
					{
                        //ptr->CreatePopupWindow();
                        make<App6::implementation::MainWindow>();
					}

				}
				if (uMsg == ptr->m_TaskbarCreatedMessage)
				{
					ptr->AddNotifyIcon();
				}
				return DefSubclassProc(hWnd, uMsg, wParam, lParam);

			},
			1, reinterpret_cast<DWORD_PTR>(this));
    }
}
