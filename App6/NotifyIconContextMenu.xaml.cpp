#include "pch.h"
#include "NotifyIconContextMenu.xaml.h"
#if __has_include("NotifyIconContextMenu.g.cpp")
#include "NotifyIconContextMenu.g.cpp"
#endif

#include "MainWindow.xaml.h"
#include <LaunchGame.h>
#include <App.xaml.h>

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Service::Game::Launching;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::App6::implementation
{
	void NotifyIconContextMenu::Window_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{
        if (App::mainWindow)
        {
			App::ToForeground();
        }
        else
        {
			App::mainWindow = make<MainWindow>();
        }
		
	}

	void NotifyIconContextMenu::Exit_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{
		DispatcherQueue().TryEnqueue([this]
			{
				Application::Current().Exit();
			}
		);
		
	}

	void NotifyIconContextMenu::Launch_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{
		Launch();
	}


}




