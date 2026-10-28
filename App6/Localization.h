#pragma once

namespace Service::Localization
{
    const std::map<std::wstring_view, std::wstring_view> Languages
    {
       {L"AppLanguageDefault",                        L"en-US"},
       {L"AppLanguageCommunitySimplifiedChinese",     L"zh-CN"},
       {L"AppLanguageCommunityTraditionalChinese",    L"zh-TW"},
       {L"AppLanguageCommunityFrench",                L"fr-FR"},
       {L"AppLanguageCommunityGerman",                L"de-DE"},
       {L"AppLanguageCommunityIndonesian",            L"id-ID"},
       {L"AppLanguageCommunityItalian",               L"it-IT"},
       {L"AppLanguageCommunityJapanese",              L"ja-JP"},
       {L"AppLanguageCommunityKorean",                L"ko-KR"},
       {L"AppLanguageCommunityPortuguese",            L"pt-PT"},
       {L"AppLanguageCommunityRussian",               L"ru-RU"},
       {L"AppLanguageCommunitySpanish",               L"es-ES"},
       {L"AppLanguageCommunityThai",                  L"th-TH"},
       {L"AppLanguageCommunityTurkish",               L"tr-TR"},
       {L"AppLanguageCommunityVietnamese",            L"vi-VN"}

    };
    void Init();
    int  GetLangIndex();
    void SetLang(int index);

}