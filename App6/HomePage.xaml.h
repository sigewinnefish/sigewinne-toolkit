#pragma once

#include "HomePage.g.h"
#include "island.h"
#include "Settings.h"

namespace winrt::App6::implementation
{
    struct HomePage : HomePageT<HomePage>
    {
        HomePage();

        void Button_KillProcess_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void Button_Click_Game(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void SelectorBar2_SelectionChanged(winrt::Microsoft::UI::Xaml::Controls::SelectorBar const& sender, winrt::Microsoft::UI::Xaml::Controls::SelectorBarSelectionChangedEventArgs const& args);
	private:
        uint32_t m_selected_index{0};
    };
}

namespace winrt::App6::factory_implementation
{
    struct HomePage : HomePageT<HomePage, implementation::HomePage>
    {
    };
}
