/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 09.09.2025
Summary : Source file for pure virtual class for base class of SaveGame.
					All other class derived from USaveGame need to derived form this class instead.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "SaveGame/BaseSaveGame.h"
#include "Kismet/GameplayStatics.h"

FString UBaseSaveGame::GetSaveSlotName() const
{
	return FString::Printf(TEXT("default_slot_name_of_%s"), *GetClass()->GetName());
}

void UBaseSaveGame::DeleteSaveFile()
{
	FString run_progress_slot_name = GetSaveSlotName();

	if (UGameplayStatics::DoesSaveGameExist(run_progress_slot_name, 0))
	{
		UGameplayStatics::DeleteGameInSlot(run_progress_slot_name, 0);
	}
}
