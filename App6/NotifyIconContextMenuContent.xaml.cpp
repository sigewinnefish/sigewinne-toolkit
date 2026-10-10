#include "pch.h"
#include "NotifyIconContextMenuContent.xaml.h"
#if __has_include("NotifyIconContextMenuContent.g.cpp")
#include "NotifyIconContextMenuContent.g.cpp"
#endif

#include <LaunchGame.h>
#include <App.xaml.h>

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Service::Game::Launching;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::App6::implementation
{
	void NotifyIconContextMenuContent::Window_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{
		App::PresentMainWindow();
	}

	void NotifyIconContextMenuContent::Launch_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{
		Launch();
	}

	void NotifyIconContextMenuContent::Exit_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{
		DispatcherQueue().TryEnqueue([this]
			{
				Application::Current().Exit();
			}
		);
	}

}

