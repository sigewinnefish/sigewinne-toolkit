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
}
