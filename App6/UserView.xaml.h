#pragma once

#include "UserView.g.h"
#include "UserViewModel.h"
#include <wil/cppwinrt_authoring.h>

namespace winrt::App6::implementation
{
    struct UserView : UserViewT<UserView>
    {
        UserView()
        {
			wil::single_threaded_property<App6::UserViewModel> ViewModel;
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
