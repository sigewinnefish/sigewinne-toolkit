#include "pch.h"
#include "MainView.xaml.h"
#if __has_include("MainView.g.cpp")
#include "MainView.g.cpp"
#endif
#include <winrt/Windows.UI.Xaml.Interop.h>

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::App6::implementation
{
	MainView::MainView()
	{
		DispatcherQueue().TryEnqueue(
			[this]()
			{
				NavView().SelectedItem(NavView().MenuItems().GetAt(0));

			});
		// Xaml objects should not call InitializeComponent during construction.
		// See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
	}

	void winrt::App6::implementation::MainView::NavView_SelectionChanged(winrt::Microsoft::UI::Xaml::Controls::NavigationView const& sender, winrt::Microsoft::UI::Xaml::Controls::NavigationViewSelectionChangedEventArgs const& args)
	{
		auto item = args.SelectedItemContainer().as<NavigationViewItem>();
		if (auto headerText = item.Content().try_as<winrt::hstring>())
		{
			HeaderText().Text(to_hstring(*headerText));
		}
		if (args.IsSettingsSelected())
		{
			contentFrame().Navigate(xaml_typename<SettingsPage>());
			return;
		}
		contentFrame().Navigate(xaml_typename<HomePage>());
	}

}

