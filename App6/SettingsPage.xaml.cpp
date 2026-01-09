#include "pch.h"
#include "SettingsPage.xaml.h"
#include <winrt/Microsoft.Windows.Storage.Pickers.h>
#include "Settings.h"
#if __has_include("SettingsPage.g.cpp")
#include "SettingsPage.g.cpp"
#endif
#include <winrt/Microsoft.UI.Interop.h>
#include "MainWindow.xaml.h"
#include "GamePathDetect.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::Windows::Storage::Pickers;
using namespace Service::Settings;
using namespace Service::Game::FileSystem;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::App6::implementation
{
    SettingsPage::SettingsPage()
    {

        DispatcherQueue().TryEnqueue(
            [this]()
            {
                LangCombo().SelectedIndex(pappsettings->lang());
            });

        // Xaml objects should not call InitializeComponent during construction.
        // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
    }

    void SettingsPage::LangCombo_SelectionChanged(const Windows::Foundation::IInspectable& sender,
                                                  const Controls::SelectionChangedEventArgs& e)
    {
        pappsettings->set_lang(LangCombo().SelectedIndex());
    }

    void SettingsPage::SelectGamePath_Click(const Windows::Foundation::IInspectable& sender, const RoutedEventArgs& e)
    {
        selectGamePathAsync();
    }

    winrt::App6::SettingsViewModel SettingsPage::ViewModel()
    {
		return m_viewModel;
    }

    winrt::fire_and_forget SettingsPage::selectGamePathAsync()
    {
        
        FileOpenPicker picker = FileOpenPicker(MainWindow::m_windowId);
        picker.SuggestedStartLocation(PickerLocationId::ComputerFolder);
        picker.FileTypeFilter().Append(L".exe");
        auto result{ co_await picker.PickSingleFileAsync() };

        if (result)
        {
            m_viewModel.GamePath(result.Path());
        }
    }

    void SettingsPage::GamePathAutoDetect_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {

        wchar_t path[MAX_PATH];

        try
        {
            GamePathDetect(path);
        }
        catch (...)
        {
            MessageBoxW(0, L"GamePath Detect Error", L"Error", MB_OK | MB_ICONERROR);
            return;
        }

        m_viewModel.GamePath(to_hstring(path) + L"\\YuanShen.exe");
        
    }

}


