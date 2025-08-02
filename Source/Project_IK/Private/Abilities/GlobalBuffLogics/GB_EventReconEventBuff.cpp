/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 08.01.2025
Summary : Source file for a global buff that remove negative events.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Abilities/GlobalBuffLogics/GB_EventReconEventBuff.h"

#include "WorldSettings/IKGameInstance.h"
#include "Managers/EventManager.h"

void UGB_EventReconEventBuff::OnBuffExpired()
{
	UWorld* world = GetWorld();
	if (world)
	{
		UIKGameInstance* instance = Cast<UIKGameInstance>(world->GetGameInstance());
		UEventManager* manager = instance->GetEventManager();
		manager->CountDownIsNegativeEventsRemoved();
	}
}
