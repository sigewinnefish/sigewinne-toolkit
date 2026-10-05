#include "pch.h"
#include "Utils.h"
#include <winrt/Microsoft.Windows.ApplicationModel.Resources.h>

using namespace winrt;
using namespace Microsoft::Windows::ApplicationModel::Resources;

namespace Service::Utils
{
    namespace Message
    {
		void ShowMessageBox(const wchar_t* message, Severity level)
		{
			hstring text = ResourceGetString(message);
			hstring caption;
			switch (level)
			{
			case Info:
				caption = ResourceGetString(const_cast<wchar_t*>(L"MBInfo"));
				MessageBoxW(0, text.c_str(), caption.c_str(), MB_OK | MB_ICONINFORMATION);
				break;
			case Warn:
				caption = ResourceGetString(const_cast<wchar_t*>(L"MBWarn"));
				MessageBoxW(0, text.c_str(), caption.c_str(), MB_OK | MB_ICONWARNING);
				break;
			case Error:
				caption = ResourceGetString(const_cast<wchar_t*>(L"MBError"));
				MessageBoxW(0, text.c_str(), caption.c_str(), MB_OK | MB_ICONERROR);
				break;
			default:
				break;
			}

		}
    }


	hstring ResourceGetString(const wchar_t* resourceId)
	{
		//https://stackoverflow.com/questions/73628384/winui-3-c-winrt-loading-string-resources
		//ResourceManager rm{};
		//auto str = rm.MainResourceMap().GetValue(L"Resources/String1").ValueAsString();
	    ResourceLoader loader;
		hstring hstr = loader.GetString(resourceId);
		return hstr;
	}



	std::wstring str2wstr(const std::string_view str)
    {
		auto hs = to_hstring(str);
		auto ws = std::wstring(hs.begin(), hs.end());
		return ws;
    }

	std::string wstr2str(const std::wstring_view wstr)
	{
		auto s = to_string(wstr);
		return s;
	}

}
