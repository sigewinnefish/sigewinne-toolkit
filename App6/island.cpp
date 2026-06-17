#include "pch.h"
#include "Settings.h"

using namespace Service::Settings;

namespace Service::Island
{

	void Init()
	{
		if (!pmap)
		{

			HANDLE h = OpenFileMapping(FILE_MAP_READ | FILE_MAP_WRITE, FALSE, L"4F3E8543-40F7-4808-82DC-21E48A6037A7");

			if (h)
			{
				pmap = (IslandEnvironment*)MapViewOfFile(_Notnull_ h, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);
				goto loc_1;
			}

			h = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, 1024, L"4F3E8543-40F7-4808-82DC-21E48A6037A7");
			pmap = (IslandEnvironment*)MapViewOfFile(_Notnull_ h, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);
			ZeroMemory(pmap, sizeof(IslandEnvironment));

		loc_1:
			pmap->FieldOfView = pisland->fieldofview();
			pmap->TargetFrameRate = pisland->targetframerate();
			pmap->EnableSetFieldOfView = pisland->enablesetfieldofview();
			pmap->FixLowFovScene = pisland->fixlowfovscene();
			pmap->DisableFog = pisland->disablefog();
			pmap->EnableSetTargetFrameRate = pisland->enablesettargetframerate();
			pmap->RemoveOpenTeamProgress = pisland->removeopenteamprogress();
			pmap->HideQuestBanner = pisland->hidequestbanner();
			pmap->DisableEventCameraMove = pisland->disableeventcameramove();
			pmap->DisableShowDamageText = pisland->disableshowdamagetext();
			pmap->UsingTouchScreen = pisland->usingtouchscreen();
			pmap->RedirectCombineEntry = pisland->redirectcombineentry();
			pmap->HideUid = pisland->hideuid();
		}
	}
}
