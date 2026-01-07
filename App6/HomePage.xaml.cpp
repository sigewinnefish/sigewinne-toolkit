#include "pch.h"
#include "LaunchGame.h"
#include "HomePage.xaml.h"
#if __has_include("HomePage.g.cpp")
#include "HomePage.g.cpp"
#endif
#include <winrt/Windows.UI.Xaml.Interop.h>
#include <winrt/Microsoft.UI.Xaml.Media.Animation.h>
#include "Settings.h"
#include <google/protobuf/util/json_util.h>

using namespace winrt;
using namespace winrt::Microsoft::UI::Xaml;
using namespace winrt::Windows::UI::Xaml::Interop;
using namespace winrt::Microsoft::UI::Xaml::Media::Animation;
using namespace Service::LaunchGame;
using namespace Service::Settings;
// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::App6::implementation
{
	HomePage::HomePage()
	{
		this->NavigationCacheMode(Microsoft::UI::Xaml::Navigation::NavigationCacheMode::Disabled); // a bug in here might from Microsoft, NavigationCacheMode::Disabled is default
		// Xaml objects should not call InitializeComponent during construction.
		// See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
	}

	void HomePage::Button_KillProcess_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        TerminateProcess(GetCurrentProcess(), 0);
    }

    void HomePage::Button_Click_Game(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        g_path;
        Launch();
    }

    void HomePage::SelectorBar2_SelectionChanged(winrt::Microsoft::UI::Xaml::Controls::SelectorBar const& sender, winrt::Microsoft::UI::Xaml::Controls::SelectorBarSelectionChangedEventArgs const& args)
    {
        auto item = sender.SelectedItem();
        uint32_t currentSelectedIndex;
        sender.Items().IndexOf(item, currentSelectedIndex);
        SlideNavigationTransitionInfo slideInfo{};

        if (currentSelectedIndex >= m_selected_index)
        {
	        if (currentSelectedIndex == m_selected_index)
	        {
				//not user select from Selector bar, default animation
                //slideInfo.Effect(SlideNavigationTransitionEffect::FromBottom);
	        }
	        else
	        {
                slideInfo.Effect(SlideNavigationTransitionEffect::FromRight);
	        }
        }
        else
        {
            slideInfo.Effect(SlideNavigationTransitionEffect::FromLeft);
        }

        switch (currentSelectedIndex)
        {
        case 0:
        	contentFrame().Navigate(xaml_typename<App6::LaunchGamePage>(), nullptr, slideInfo);
            break;
        case 1:
        	contentFrame().Navigate(xaml_typename<App6::IslandPage>(), nullptr, slideInfo);
            break;
        default:
            break;
        }

        m_selected_index = currentSelectedIndex;
    }


}

