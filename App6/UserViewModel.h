#pragma once

#include "UserViewModel.g.h"
#include <winrt/Microsoft.UI.Xaml.Data.h>
#include <wil/cppwinrt_authoring.h>
#include <winrt/Microsoft.UI.Xaml.Input.h>

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Input;
namespace winrt::App6::implementation
{
    struct UserViewModel : UserViewModelT<UserViewModel>, wil::notify_property_changed_base<UserViewModel>
    {
        UserViewModel() = default;
        ICommand AddUserCommand()
        {
            return 0;
        }
    };
}

namespace winrt::App6::factory_implementation
{
    struct UserViewModel : UserViewModelT<UserViewModel, implementation::UserViewModel>
    {
    };
}