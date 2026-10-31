#include "pch.h"
#include "island.h"
#include "Settings.h"
#include "GUID.h"

using namespace Service::Settings;
using namespace Service::GlobalConst::GUID;

namespace Service::Island
{
	void Init()
	{
		if (!pmap)
		{
			HANDLE h = OpenFileMapping(FILE_MAP_READ | FILE_MAP_WRITE, FALSE, IslandGUID);

			if (h)
			{
				pmap = (IslandEnvironment*)MapViewOfFile(_Notnull_ h, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);

			}
            else
            {
				h = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, 1024, IslandGUID);
				pmap = (IslandEnvironment*)MapViewOfFile(_Notnull_ h, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);
				ZeroMemory(pmap, sizeof(IslandEnvironment));
            }

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
			pmap->ResinListItemAllowOriginalResin = (*pisland->mutable_items())[106];
			pmap->ResinListItemAllowPrimogem = (*pisland->mutable_items())[201];
			pmap->ResinListItemAllowFragileResin = (*pisland->mutable_items())[107009];
			pmap->ResinListItemAllowTransientResin = (*pisland->mutable_items())[107012];
			pmap->ResinListItemAllowCondensedResin = (*pisland->mutable_items())[220007];
		}
	}
}
