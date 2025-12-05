#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif
#include <winrt/Microsoft.UI.Interop.h>

IslandEnvironment* penv = nullptr;
// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::App6::implementation
{

    void MainWindow::initializeEnv()
    {
        HANDLE h = OpenFileMapping(FILE_MAP_READ | FILE_MAP_WRITE, FALSE, L"4F3E8543-40F7-4808-82DC-21E48A6037A7"); //4F3E8543-40F7-4808-82DC-21E48A6037A7

        if (h == NULL)
        {
            h = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_EXECUTE_READWRITE, 0, 1024, L"4F3E8543-40F7-4808-82DC-21E48A6037A7");
                
        }

        
        penv = (IslandEnvironment*)MapViewOfFile(_Notnull_ h, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);
        ::penv = penv;
        ZeroMemory(penv, sizeof(IslandEnvironment));
        penv->IslandFunctionOffsets.MickeyWonderMethod = 0x5e0d680; //
        penv->IslandFunctionOffsets.MickeyWonderMethodPartner = 0x3e87b0; //
        penv->IslandFunctionOffsets.MickeyWonderMethodPartner2 = 0x7728b90; //
        penv->IslandFunctionOffsets.SetFieldOfView = 0x10407c0; //
        penv->IslandFunctionOffsets.SetEnableFogRendering = 0x14f2cb90; //
        penv->IslandFunctionOffsets.SetTargetFrameRate = 0x14f18ea0; //
        penv->IslandFunctionOffsets.OpenTeam = 0xb8dcfa0; //
        penv->IslandFunctionOffsets.OpenTeamPageAccordingly = 0xb8e5fb0;
        penv->IslandFunctionOffsets.CheckCanEnter = 0x954f230; //
        penv->IslandFunctionOffsets.SetupQuestBanner = 0xdbb1320; //
        penv->IslandFunctionOffsets.FindGameObject = 0x14f1bf20; //
        penv->IslandFunctionOffsets.SetActive = 0x14f1bc60; //
        penv->IslandFunctionOffsets.EventCameraMove = 0xe076e80; //
        penv->IslandFunctionOffsets.ShowOneDamageTextEx = 0xfea2160; //
        penv->IslandFunctionOffsets.SwitchInputDeviceToTouchScreen = 0xab06670; //
        penv->IslandFunctionOffsets.MickeyWonderCombineEntryMethod = 0xa0a2d00; //
        penv->IslandFunctionOffsets.MickeyWonderCombineEntryMethodPartner = 0x84fb720; //
        penv->IslandFunctionOffsets.GetTargetFrameRate = 0x125a050; //
        penv->IslandFunctionOffsets.GameManagerAwake = 0xc4007c0; //
        //penv->IslandFunctionOffsets.SetupResinList = 0xd03a400; //!!!!!!!!!!
        //penv->IslandFunctionOffsets.ResinListRemove = 0x13CDA8C0;
        //penv->IslandFunctionOffsets.ResinList = 0x1F0;
        //penv->IslandFunctionOffsets.ResinListGetItem = 0x13CD8FF0;
        //penv->IslandFunctionOffsets.ResinListGetCount = 0x13CD8F90;
        //penv->IslandFunctionOffsets.SetLastUid = 0x0F43BA90;
    }


    void MainWindow::viewloaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {

        //
        //loadConfig();
        contentFrame().Navigate(xaml_typename<App6::IslandPage>());
    }

    void MainWindow::NavigationView_SelectionChanged(winrt::Microsoft::UI::Xaml::Controls::NavigationView const& sender, winrt::Microsoft::UI::Xaml::Controls::NavigationViewSelectionChangedEventArgs const& args)
    {
        //contentFrame().Navigate(xaml_typename<App6::HomePage>());
    }

}



