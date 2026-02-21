#include "pch.h"
#include "UserView.xaml.h"
#if __has_include("UserView.g.cpp")
#include "UserView.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;
using namespace Microsoft::UI::Xaml::Controls::Primitives;
// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::App6::implementation
{
	void UserView::UserViewItem_Tapped(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::TappedRoutedEventArgs const& e)
	{
		FlyoutBase::ShowAttachedFlyout(sender.as<FrameworkElement>());
	}

}

