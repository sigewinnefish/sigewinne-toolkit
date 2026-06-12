#include "pch.h"
#include "IslandPage.xaml.h"
#if __has_include("IslandPage.g.cpp")
#include "IslandPage.g.cpp"
#endif

#include "Settings.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;
using namespace Windows::Foundation;
using namespace Service::Settings;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::App6::implementation
{
	IslandPage::IslandPage()
	{
		this->NavigationCacheMode(Microsoft::UI::Xaml::Navigation::NavigationCacheMode::Required);
		DispatcherQueue().TryEnqueue(
			[this]()
			{
				if (pappsettings->islandrestrictionsoverride() && pappsettings->frameratelimitoverride())
				{

					this->IslandTargetFpsValue().Maximum(pappsettings->frameratelimitvalue());
				}
				else
				{
					this->IslandTargetFpsValue().Maximum(120);
				}

			});

		// Xaml objects should not call InitializeComponent during construction.
		// See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
	}

}
