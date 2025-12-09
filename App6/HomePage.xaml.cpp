#include "pch.h"
#include "Launch_Game.h"
#include "HomePage.xaml.h"
#if __has_include("HomePage.g.cpp")
#include "HomePage.g.cpp"
#endif
#include <winrt/Windows.UI.Xaml.Interop.h>


using namespace winrt;
using namespace winrt::Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::App6::implementation
{
    void HomePage::Button_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        exit(0);
    }

    void HomePage::Button_Click_Game(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {

		static std::wstring path(Path().Text());
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Launch_Game_Proc, &path, 0, NULL);

    }
}

void winrt::App6::implementation::HomePage::SelectorBar2_SelectionChanged(winrt::Microsoft::UI::Xaml::Controls::SelectorBar const& sender, winrt::Microsoft::UI::Xaml::Controls::SelectorBarSelectionChangedEventArgs const& args)
{
    auto item = sender.SelectedItem();
    uint32_t currentSelectedIndex;
    sender.Items().IndexOf(item, currentSelectedIndex);

    switch (currentSelectedIndex)
    {
    case 0:
        contentFrame().Navigate(xaml_typename<App6::LaunchGamePage>());
        break;
    case 1:
        contentFrame().Navigate(xaml_typename<App6::IslandPage>());
        break;
    default:
        contentFrame().Navigate(xaml_typename<App6::LaunchGamePage>());
        break;
    }
    
}
