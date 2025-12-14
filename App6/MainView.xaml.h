#pragma once

#include "MainView.g.h"

namespace winrt::App6::implementation
{
    struct MainView : MainViewT<MainView>
    {
        MainView()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }


        void NavView_ItemInvoked(winrt::Microsoft::UI::Xaml::Controls::NavigationView const& sender, winrt::Microsoft::UI::Xaml::Controls::NavigationViewItemInvokedEventArgs const& args);
        void MainView_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::App6::factory_implementation
{
    struct MainView : MainViewT<MainView, implementation::MainView>
    {
    };
}
