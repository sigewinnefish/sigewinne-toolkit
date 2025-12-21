#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif
#include <winrt/Microsoft.UI.Interop.h>
#include <winrt/Windows.UI.Xaml.Interop.h>


// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::App6::implementation
{
	MainWindow::MainWindow()
	{
		Exp1();
		this->ExtendsContentIntoTitleBar(true);
		this->AppWindow().TitleBar().PreferredHeightOption(TitleBarHeightOption::Tall);
		this->AppWindow().TitleBar().PreferredTheme(TitleBarTheme::UseDefaultAppMode);
		this->AppWindow().SetIcon(L"Assets\\Logo.ico");
		UINT dpi = GetDpiForWindow(GetWindowHandle());
		THROW_HR_IF(E_INVALIDARG, 0 == dpi);
		auto scale = floorf(dpi * 100.0f / 96.0f + 0.5f) / 100.0f;
		this->AppWindow().Presenter().try_as<OverlappedPresenter>().PreferredMinimumWidth(static_cast<int32_t>(1000 * scale));
		this->AppWindow().Presenter().try_as<OverlappedPresenter>().PreferredMinimumHeight(static_cast<int32_t>(600 * scale));
		//this->AppWindow().Resize({ static_cast<int32_t>(1600 * scale), static_cast<int32_t>(1000 * scale) });
		//this->AppWindow().Move({ 700, 450 });

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
	void MainWindow::Exp1()
	{
		typedef __int64(__fastcall* put_PersistedStateId)(__int64 a1, __int64 a2);
		typedef __int64(__fastcall* put_PlacementRestorationBehavior)(__int64 a1, __int64 a2);

		void* result{};
		guid gIAppWindowExperimental("04DB96C7-DEB6-5BE4-BFDC-1BC0361C8A12"); // IAppWindowExperimental
		this->AppWindow().try_as<IUnknown>()->QueryInterface(gIAppWindowExperimental, &result);
		auto vt = *(int64_t*)result;
		const auto k = guid{ L"{1ed4408f-9732-4543-aa46-8758439652e6}" }; // App guid
		auto func = reinterpret_cast<put_PlacementRestorationBehavior*>((char*)vt + 0x48);
		(*func)((__int64)result, 0);
		Windows::Foundation::IReference kk(k);
		auto func2 = reinterpret_cast<put_PersistedStateId*>((char*)vt + 0x38);
		(*func2)((__int64)result, (__int64)(*(__int64*)&kk));
		reinterpret_cast<IUnknown*>(result)->Release();
	}
	void MainWindow::Exp2()
	{
		typedef __int64(__fastcall* SaveCurrentPlacement)(__int64 a1);

		void* result{};
		guid gIAppWindowExperimental("04DB96C7-DEB6-5BE4-BFDC-1BC0361C8A12"); // IAppWindowExperimental
		this->AppWindow().try_as<IUnknown>()->QueryInterface(gIAppWindowExperimental, &result);
		auto vt = *(int64_t*)result;
		auto func3 = reinterpret_cast<SaveCurrentPlacement*>((char*)vt + 0x58);
		(*func3)((__int64)result);
		reinterpret_cast<IUnknown*>(result)->Release();
	}
}

void winrt::App6::implementation::MainWindow::Window_Closed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::WindowEventArgs const& args)
{
	Exp2();
}
