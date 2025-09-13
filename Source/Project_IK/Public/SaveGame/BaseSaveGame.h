/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 09.09.2025
Summary : Header file for pure virtual class for base class of SaveGame.
					All other class derived from USaveGame need to derived form this class instead.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "BaseSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UBaseSaveGame : public USaveGame 
{
	GENERATED_BODY()
	
public:
	// Pure virtual function to return FString that passed as second parameter to call SaveGameToSlot.
	virtual FString GetSaveSlotName() const;
	bool DoesSaveGameExist() const;
	void DeleteSaveFile();
};
