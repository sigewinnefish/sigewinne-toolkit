#include "pch.h"
#include "LaunchGamePage.xaml.h"
#if __has_include("LaunchGamePage.g.cpp")
#include "LaunchGamePage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::App6::implementation
{
	LaunchGamePage::LaunchGamePage()
	{
		this->NavigationCacheMode(Microsoft::UI::Xaml::Navigation::NavigationCacheMode::Required);
		// Xaml objects should not call InitializeComponent during construction.
		// See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
	}
}
