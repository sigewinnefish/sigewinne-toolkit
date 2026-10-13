#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif

#include <Settings.h>
#include <App.xaml.h>
#include "GUID.h"

using namespace Service::Settings;
using namespace Service::GlobalConst::GUID;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::App6::implementation
{

	MainWindow::MainWindow()
	{
		InitWindow();

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

	enum class PlacementRestorationBehavior : std::uint32_t
	{
		None = 0,
		AllowShowMaximized = 0x1,
		AllowShowFullScreen = 0x2,
		AllowShowArranged = 0x4,
		UseStartupInfoForFirstWindow = 0x8,
		All = 0xffffffff,
	};

	struct  __declspec(novtable) IAppWindowExperimental : public ::IInspectable
	{
		virtual HRESULT STDMETHODCALLTYPE get_PersistedStateId() = 0; // not use
		virtual HRESULT STDMETHODCALLTYPE put_PersistedStateId(__int64) = 0;
		virtual HRESULT STDMETHODCALLTYPE get_PlacementRestorationBehavior() = 0; // not use
		virtual HRESULT STDMETHODCALLTYPE put_PlacementRestorationBehavior(PlacementRestorationBehavior) = 0;
		virtual HRESULT STDMETHODCALLTYPE GetCurrentPlacement() = 0; // not use
		virtual HRESULT STDMETHODCALLTYPE SaveCurrentPlacement() = 0;
		
	};

    void MainWindow::Exp1()
	{

		winrt::com_ptr<IAppWindowExperimental> com_IAppWindowExperimental;
		//winrt::com_ptr<IAppWindowExperimental> com_IAppWindowExperimental;
		auto guid_MainWindowGUID = guid{ MainWindowGUID };
		auto guid_Reference = Windows::Foundation::IReference{ guid_MainWindowGUID };
		this->AppWindow().try_as<IUnknown>()->QueryInterface(guid{ iid_IAppWindowExperimental }, com_IAppWindowExperimental.put_void());
		com_IAppWindowExperimental->put_PersistedStateId(*(__int64*)&guid_Reference);
		com_IAppWindowExperimental->put_PlacementRestorationBehavior(PlacementRestorationBehavior::None);

	}

	void MainWindow::Exp2()
	{
		winrt::com_ptr<IAppWindowExperimental> com_IAppWindowExperimental;
		this->AppWindow().try_as<IUnknown>()->QueryInterface(guid{ iid_IAppWindowExperimental }, com_IAppWindowExperimental.put_void());
		com_IAppWindowExperimental->SaveCurrentPlacement();
	}

	void MainWindow::InitWindow()
	{
		// TitleBar

		this->ExtendsContentIntoTitleBar(true); // this should be first
		this->AppWindow().TitleBar().PreferredHeightOption(TitleBarHeightOption::Tall);
		//this->AppWindow().TitleBar().PreferredTheme(TitleBarTheme::UseDefaultAppMode);
		this->AppWindow().SetIcon(L"Assets\\Logo.ico");

		// WindowId
		m_windowId = this->AppWindow().Id();

		// Window

		UINT dpi = GetDpiForWindow(GetWindowHandle());
		THROW_HR_IF(E_INVALIDARG, 0 == dpi);
		auto scale = floorf(dpi * 100.0f / 96.0f + 0.5f) / 100.0f;
		this->AppWindow().Presenter().try_as<OverlappedPresenter>().PreferredMinimumWidth(static_cast<int32_t>(1000 * scale));
		this->AppWindow().Presenter().try_as<OverlappedPresenter>().PreferredMinimumHeight(static_cast<int32_t>(600 * scale));

		// Window Closing Callback

		this->AppWindow().Closing([this](auto sender, AppWindowClosingEventArgs args)
			{
                switch (pappsettings->closebehavior())
                {
                case 0:
					Application::Current().Exit();
					break;
                case 1:
					App::mainWindow = nullptr;
					break;
                default:
					App::mainWindow = nullptr;
					break;
                }

			});

		// ShowWindow

		this->Exp1();
		this->Activate();

	}

	void MainWindow::Window_Closed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::WindowEventArgs const& args)
	{
		Exp2();
	}
}


