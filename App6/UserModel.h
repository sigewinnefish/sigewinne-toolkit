// UserModel.h
#pragma once
#include "UserModel.g.h"
#include <wil/cppwinrt_authoring.h>

namespace winrt::App6::implementation
{
    struct UserModel : UserModelT<UserModel>, wil::notify_property_changed_base<UserModel>
    {
        UserModel() = default;
        WIL_NOTIFYING_PROPERTY(winrt::hstring, User, L"");
        WIL_NOTIFYING_PROPERTY(uint32_t, UID, 0);


    };
}
namespace winrt::App6::factory_implementation
{
    struct UserModel : UserModelT<UserModel, implementation::UserModel>
    {
    };
}