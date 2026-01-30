#pragma once

#include "UserView.g.h"

namespace winrt::App6::implementation
{
    struct UserView : UserViewT<UserView>
    {
        UserView()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        void UserViewItem_Tapped(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::TappedRoutedEventArgs const& e);
    };
}

namespace winrt::App6::factory_implementation
{
    struct UserView : UserViewT<UserView, implementation::UserView>
    {
    };
}
