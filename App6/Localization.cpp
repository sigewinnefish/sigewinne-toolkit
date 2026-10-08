#include "pch.h"
#include "Localization.h"
#include "Utils.h"
#include <Settings.h>

using namespace winrt::Microsoft::Windows::Globalization;
using namespace Service::Settings;
using namespace Service::Utils;

namespace Service::Localization
{
    void Init()
    {
        if (pappsettings->langoverride())
        {
            try
            {
                const auto& wstr = str2wstr(pappsettings->lang());
                const auto& lang = Languages.at(wstr);
                ApplicationLanguages::PrimaryLanguageOverride(lang);
            }
            catch (...)
            {
                ShowMessageBox(L"MBPrimaryLanguageOverride", Utils::Message::Error);
                pappsettings->set_langoverride(false);
            }
            
        }
    }

    int GetLangIndex()
    {
        const auto& wstr = str2wstr(pappsettings->lang());
        const auto& it = Languages.find(wstr);
        if (it == Languages.end())
        {
            return -1; // not found
        }
        auto index = std::distance(Languages.begin(), it);
        return index;
    }

    void SetLang(int index)
    {
        if (index < 0)
        {
            return;
        }
        auto it = std::next(Languages.begin(), index);
        const auto str = wstr2str(it->first);
        pappsettings->set_lang(str);
    }

}
