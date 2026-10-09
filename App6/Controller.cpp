#include "pch.h"
#include "Controller.h"
#include "Utils.h"
#include <commctrl.h>
#include <shellapi.h>

#include "App.xaml.h"
#include "resource.h"

using namespace Service::Utils;
using namespace winrt::Microsoft::UI::Xaml;
using namespace winrt::Microsoft::UI::Xaml::Controls::Primitives;
using namespace winrt::App6::implementation;

namespace Service::NotifyIcon
{
    void Controller::Init()
    {
        m_dispatcherQueue = Microsoft::UI::Dispatching::DispatcherQueue::GetForCurrentThread();
        CreateNotifyIconHostWindow();
        InitPopupWindowContents();
        InitMessage();
        AddNotifyIcon();
        SetCallback();
    }

    void Controller::InitPopupWindowContents()
    {
        m_dispatcherQueue.TryEnqueue(
            [this]()
            {
                m_xamlSource = DesktopWindowXamlSource{};
                m_flyout = make<NotifyIconContextMenu>();
                m_anchor = Border{};
                m_anchor.Loaded([this](auto&&, auto&&) {
                    m_flyout.XamlRoot(m_anchor.XamlRoot());
                    });
                m_xamlSource.Initialize(m_windowId);
                m_xamlSource.Content(m_anchor);

                m_flyout.Closed([this](auto&&, auto&&)
                    {
                        ShowWindow(m_hwnd, SW_HIDE);
                    });
            });
    }

    void Controller::ShowPopupWindow()
    {
        ShowWindow(m_hwnd, SW_SHOWNOACTIVATE);

        FlyoutShowOptions options;
        NOTIFYICONIDENTIFIER id{};
        id.guidItem = winrt::guid("21a2acbc-3a44-43c8-860a-f8e7151b2623");
        id.cbSize = sizeof(NOTIFYICONIDENTIFIER);
        RECT rect;
        Shell_NotifyIconGetRect(&id, &rect);
        auto dpi_scale = m_anchor.XamlRoot().RasterizationScale();

        options.Position(Windows::Foundation::Point{ static_cast<float>(rect.left / dpi_scale - 8),static_cast<float>(rect.top / dpi_scale - 24) });
        options.Placement(FlyoutPlacementMode::Auto);
        options.ShowMode(FlyoutShowMode::Auto);
        m_flyout.ShowAt(m_anchor, options);
        SetForegroundWindow(m_hwnd);
    }

    void Controller::DeleteNotifyIcon()
    {
        if (m_iconAdded)
        { 
            NOTIFYICONDATAW nid{};
            nid.cbSize = sizeof(NOTIFYICONDATAW);
            nid.hWnd = m_hwnd;
            nid.uID = 0;
            nid.guidItem = winrt::guid("21a2acbc-3a44-43c8-860a-f8e7151b2623");
            nid.uFlags = NIF_GUID;
            if (Shell_NotifyIconW(NIM_DELETE, &nid))
            {
                m_iconAdded = 0;
            }
        }
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
            m_iconAdded = 1;
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
            WS_EX_LAYERED |
            WS_EX_TOOLWINDOW |
            WS_EX_NOACTIVATE |
            WS_EX_TOPMOST
            ,
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
        THROW_LAST_ERROR_IF(
            !SetLayeredWindowAttributes(
                m_hwnd,
                0,
                0,
                LWA_ALPHA
            )
        );
        m_windowId = GetWindowIdFromWindow(m_hwnd);

    }

    void Controller::InitMessage()
    {
        /*
        Taskbar Creation Notification
        When the taskbar is created, it registers a message with the TaskbarCreated string and then broadcasts this message to all top - level windows.
        */
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
                    if (LOWORD(lParam) == WM_RBUTTONUP)
                    {
                        ptr->ShowPopupWindow();
                    }

                    if (LOWORD(lParam) == WM_LBUTTONUP)
                    {
                        App::PresentMainWindow();
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
