#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;
// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::App6::implementation
{


    void MainWindow::Button_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        exit(0);
    }

    void MainWindow::Button_Click_Game(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        auto str = winrt::to_string(Path().Text());
        launchGame((char*)str.c_str());

    }

    void MainWindow::TargetFovHotSwitch(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        penv->EnableSetFieldOfView = sender.try_as<ToggleSwitch>().IsOn();
    }

    void MainWindow::DisableFog(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        penv->DisableFog = sender.try_as<ToggleSwitch>().IsOn();
    }

    void MainWindow::TargetFpsToggleSwitch(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        penv->EnableSetTargetFrameRate = sender.try_as<ToggleSwitch>().IsOn();
    }

    void MainWindow::TargetFps(winrt::Microsoft::UI::Xaml::Controls::NumberBox const& sender, winrt::Microsoft::UI::Xaml::Controls::NumberBoxValueChangedEventArgs const& args)
    {
        penv->TargetFrameRate = sender.Value();
    }

    void MainWindow::TargetFov(winrt::Microsoft::UI::Xaml::Controls::NumberBox const& sender, winrt::Microsoft::UI::Xaml::Controls::NumberBoxValueChangedEventArgs const& args)
    {
        penv->FieldOfView = sender.Value();
    }

    void MainWindow::FixLowFovSceneToggleSwitch(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        penv->FixLowFovScene = sender.try_as<ToggleSwitch>().IsOn();

    }


    void MainWindow::RemoveOpenTeamProgress(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        penv->RemoveOpenTeamProgress = sender.try_as<ToggleSwitch>().IsOn();
    }

    void MainWindow::EventCameraMoveHotSwitch(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        penv->DisableEventCameraMove = sender.try_as<ToggleSwitch>().IsOn();
    }

    void MainWindow::DisableShowDamageText(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        penv->DisableShowDamageText = sender.try_as<ToggleSwitch>().IsOn();
    }

    void MainWindow::RedirectCombineEntryToggleSwitch(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        penv->RedirectCombineEntry = sender.try_as<ToggleSwitch>().IsOn();
    }

    void MainWindow::UsingTouchScreen(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        penv->UsingTouchScreen = sender.try_as<ToggleSwitch>().IsOn();
    }

    void MainWindow::ResinListItemAllowOriginalResin(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        penv->ResinListItemId000106Allowed = sender.try_as<ToggleSwitch>().IsOn();
    }

    void MainWindow::ResinListItemAllowPrimogem(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        penv->ResinListItemId000201Allowed = sender.try_as<ToggleSwitch>().IsOn();
    }

    void MainWindow::ResinListItemAllowFragileResin(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        penv->ResinListItemId107009Allowed = sender.try_as<ToggleSwitch>().IsOn();
    }


    void MainWindow::ResinListItemAllowTransientResin(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        penv->ResinListItemId107012Allowed = sender.try_as<ToggleSwitch>().IsOn();
    }

    void MainWindow::ResinListItemAllowCondensedResin(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        penv->ResinListItemId220007Allowed = sender.try_as<ToggleSwitch>().IsOn();
    }

    void MainWindow::HideQuestBanner(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        penv->HideQuestBanner = sender.try_as<ToggleSwitch>().IsOn();
    }

    void MainWindow::loadConfig()
    {
        pConfig pconfig = new Config();
        ZeroMemory(pconfig, sizeof(Config));
        auto h = CreateFile(L"config", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        if (h == INVALID_HANDLE_VALUE) {
            return;
        }
        LPVOID ptr = nullptr;
        ReadFile(h, pconfig, sizeof(Config), NULL, NULL);
        Path().Text(winrt::to_hstring(pconfig->gamePath));
        TargetFps_NumberBox().Value(pconfig->TargetFrameRate);
        TargetFov_NumberBox().Value(pconfig->FieldOfView);
        TargetFovHotSwitch_Toggle().IsOn(pconfig->EnableSetFieldOfView);
		DisableFog_Toggle().IsOn(pconfig->DisableFog);
		DisableShowDamageText_Toggle().IsOn(pconfig->DisableShowDamageText);
		TargetFpsToggleSwitch_Toggle().IsOn(pconfig->EnableSetTargetFrameRate);
		FixLowFovSceneToggleSwitch_Toggle().IsOn(pconfig->FixLowFovScene);
		RemoveOpenTeamProgress_Toggle().IsOn(pconfig->RemoveOpenTeamProgress);
		EventCameraMoveHotSwitch_Toggle().IsOn(pconfig->DisableEventCameraMove);
		RedirectCombineEntryToggleSwitch_Toggle().IsOn(pconfig->RedirectCombineEntry);
		HideQuestBanner_Toggle().IsOn(pconfig->HideQuestBanner);
		UsingTouchScreen_Toggle().IsOn(pconfig->UsingTouchScreen);
		ResinListItemAllowOriginalResin_Toggle().IsOn(pconfig->ResinListItemId000106Allowed);
		ResinListItemAllowPrimogem_Toggle().IsOn(pconfig->ResinListItemId000201Allowed);
		ResinListItemAllowFragileResin_Toggle().IsOn(pconfig->ResinListItemId107009Allowed);
		ResinListItemAllowTransientResin_Toggle().IsOn(pconfig->ResinListItemId107012Allowed);
		ResinListItemAllowCondensedResin_Toggle().IsOn(pconfig->ResinListItemId220007Allowed);

        CloseHandle(h);
        delete pconfig;
    }

    void MainWindow::saveConfig()
    {

        pConfig pconfig = new Config();
        ZeroMemory(pconfig, sizeof(Config));
        auto h = CreateFile(L"config", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (h == INVALID_HANDLE_VALUE) {
            return;
        }
        LPVOID ptr = nullptr;

        auto str = winrt::to_string(Path().Text());
        strcpy_s(pconfig->gamePath, str.c_str());
        pconfig->DisableEventCameraMove = penv->DisableEventCameraMove;;
        pconfig->DisableFog = penv->DisableFog;
        pconfig->DisableShowDamageText = penv->DisableShowDamageText;
        pconfig->EnableSetFieldOfView = penv->EnableSetFieldOfView;
        pconfig->EnableSetTargetFrameRate = penv->EnableSetTargetFrameRate;
        pconfig->FieldOfView = penv->FieldOfView;
        pconfig->FixLowFovScene = penv->FixLowFovScene;
        pconfig->HideQuestBanner = penv->HideQuestBanner;
        pconfig->RemoveOpenTeamProgress = penv->RemoveOpenTeamProgress;
        pconfig->RedirectCombineEntry = penv->RedirectCombineEntry;
        pconfig->UsingTouchScreen = penv->UsingTouchScreen;
        pconfig->TargetFrameRate = penv->TargetFrameRate;
        pconfig->ResinListItemId000106Allowed = penv->ResinListItemId000106Allowed;
        pconfig->ResinListItemId000201Allowed = penv->ResinListItemId000201Allowed;
        pconfig->ResinListItemId107009Allowed = penv->ResinListItemId107009Allowed;
        pconfig->ResinListItemId107012Allowed = penv->ResinListItemId107012Allowed;
        pconfig->ResinListItemId220007Allowed = penv->ResinListItemId220007Allowed;

        WriteFile(h, pconfig, sizeof(Config), NULL, NULL);
        CloseHandle(h);
        delete pconfig;
    }

    void MainWindow::initializeEnv()
    {
        HANDLE h = OpenFileMapping(FILE_MAP_READ | FILE_MAP_WRITE, FALSE, L"4F3E8543-40F7-4808-82DC-21E48A6037A7"); //4F3E8543-40F7-4808-82DC-21E48A6037A7

        if (h == NULL)
        {
            h = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_EXECUTE_READWRITE, 0, 1024, L"4F3E8543-40F7-4808-82DC-21E48A6037A7");

        }
        penv = (IslandEnvironment*)MapViewOfFile(_Notnull_ h, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);

        ZeroMemory(penv, sizeof(IslandEnvironment));
        penv->IslandFunctionOffsets.MickeyWonderMethod = 97683856;
        penv->IslandFunctionOffsets.MickeyWonderMethodPartner = 4054192;
        penv->IslandFunctionOffsets.MickeyWonderMethodPartner2 = 186683024;
        penv->IslandFunctionOffsets.SetFieldOfView = 16938096;
        penv->IslandFunctionOffsets.SetEnableFogRendering = 349320976;
        penv->IslandFunctionOffsets.SetTargetFrameRate = 349239824;
        penv->IslandFunctionOffsets.OpenTeam = 260760016;
        penv->IslandFunctionOffsets.OpenTeamPageAccordingly = 260940064;
        penv->IslandFunctionOffsets.CheckCanEnter = 206502784;
        penv->IslandFunctionOffsets.SetupQuestBanner = 220247008;
        penv->IslandFunctionOffsets.FindGameObject = 349252176;
        penv->IslandFunctionOffsets.SetActive = 349251472;
        penv->IslandFunctionOffsets.EventCameraMove = 109003424;
        penv->IslandFunctionOffsets.ShowOneDamageTextEx = 265242752;
        penv->IslandFunctionOffsets.SwitchInputDeviceToTouchScreen = 208642176;
        penv->IslandFunctionOffsets.MickeyWonderCombineEntryMethod = 256735408;
        penv->IslandFunctionOffsets.MickeyWonderCombineEntryMethodPartner = 111928560;
        penv->IslandFunctionOffsets.GetTargetFrameRate = 19127664;
        penv->IslandFunctionOffsets.GameManagerAwake = 204333664;
        penv->IslandFunctionOffsets.SetupResinList = 109454912;
        penv->IslandFunctionOffsets.ResinListRemove = 0x13CDA8C0;
        penv->IslandFunctionOffsets.ResinList = 0x1F0;
        penv->IslandFunctionOffsets.ResinListGetItem = 0x13CD8FF0;
        penv->IslandFunctionOffsets.ResinListGetCount = 0x13CD8F90;
        penv->IslandFunctionOffsets.SetLastUid = 0x0F43BA90;
    }



    void MainWindow::viewloaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        loadConfig();
    }

}

