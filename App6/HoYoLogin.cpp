#include "pch.h"
#include "HoYoLogin.h"

using namespace winrt;
using namespace Windows::Web::Http;
using namespace Windows::Web::Http::Headers;
using namespace Windows::Foundation;
using namespace winrt::Windows::Data::Json;

namespace Service::Game::Account
{
	HoYoLogin::HoYoLogin(std::string& cookies) :
		m_cookies(cookies)
	{
		initParms();
	}

	void HoYoLogin::initParms()
	{

		auto p = m_cookies.c_str(); //pcookies
		auto cookiesLength = m_cookies.length();
		auto vector1 = std::vector<int>(); // ;
		auto vector2 = std::vector<int>(); // =
		for (int i = 0; i < cookiesLength; i++)
		{
			if (*(p + i) == ';')
			{
				vector1.push_back(i);
			}
			else if (*(p + i) == '=')
			{
				vector2.push_back(i);
			}

		}

		int size = (int)vector1.size();
		auto hashtable = std::unordered_map<std::string_view, std::string_view>();
		int k = 0;

		std::string_view sv;
		std::vector<std::pair<std::string_view, std::string_view>> paras
			= { {"stoken",sv}, {"ltoken",sv}, {"mid",sv}, {"ltuid",sv} };
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < paras.size(); j++)
			{
				if (!memcmp(p + vector1[i] + 1, paras[j].first.data(), paras[j].first.size()))
				{
					while (true)
					{
						if (p + vector1[i] < p + vector2[i + k])
						{
							paras[j].second = std::string_view(
								p + vector2[i + k] + 1,
								p + vector1[i + 1]
							);
							hashtable.emplace(paras[j].first, paras[j].second);
							paras[j] = paras.back();
							paras.pop_back();
							break;
						}
						k++;
					}
				}
			}
		}

		m_stoken = hashtable["stoken"];
		m_ltoken = hashtable["ltoken"];
		m_mid = hashtable["mid"];
		m_ltuid = hashtable["ltuid"];
		m_account_id = atoi(hashtable["ltuid"].data());
	}

	std::string& HoYoLogin::cookie()
	{
		return m_cookies;
	}

	IAsyncAction HoYoLogin::postRequest()
	{
		HttpClient httpClient;
		Uri uri{ m_url };

		//headers
		httpClient.DefaultRequestHeaders().Append(
			L"Host",
			L"passport-api.mihoyo.com"
		);
		httpClient.DefaultRequestHeaders().Append(
			L"x-rpc-app_id",
			L"ddxf5dufpuyo"
		);
		httpClient.DefaultRequestHeaders().Append(
			L"User-Agent",
			L"HYPContainer/1.1.4.133"
		);
		httpClient.DefaultRequestHeaders().Append(
			L"x-rpc-client_type",
			L"3"
		);


		// cookies
		auto ltokenCookiePair = HttpCookiePairHeaderValue(
			L"ltoken",
			winrt::to_hstring(m_ltoken)
		);
		auto ltuidCookiePair = HttpCookiePairHeaderValue(
			L"ltuid",
			winrt::to_hstring(m_ltuid)
		);

		httpClient.DefaultRequestHeaders().Cookie().Append(ltokenCookiePair);
		httpClient.DefaultRequestHeaders().Cookie().Append(ltuidCookiePair);


		// body

		JsonObject postJson;
		postJson.Insert(L"game_biz", JsonValue::CreateStringValue(L"hk4e_cn"));
		postJson.Insert(L"mid", JsonValue::CreateStringValue(winrt::to_hstring(m_mid)));
		postJson.Insert(L"stoken", JsonValue::CreateStringValue(winrt::to_hstring(m_stoken)));
		postJson.Insert(L"uid", JsonValue::CreateNumberValue(m_account_id));
		HttpStringContent content(
			postJson.Stringify(),
			Windows::Storage::Streams::UnicodeEncoding::Utf8,
			L"application/json; charset=utf-8"
		);
		auto response = co_await httpClient.PostAsync(uri, content);
		hstring body = co_await response.Content().ReadAsStringAsync();
		auto responseJson = JsonObject::Parse(body);
		m_ticket = winrt::to_string(
			responseJson.GetNamedObject(L"data").GetNamedString(L"ticket")
		);
	}


}

