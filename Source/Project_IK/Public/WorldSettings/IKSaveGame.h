/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 01.25.2025
Summary : Header file for SaveGame.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Structs/PerkNodeDetail.h"
#include "IKSaveGame.generated.h"

UCLASS()
class PROJECT_IK_API UIKSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	void SavePerkDetails(FName key, FPerkNodeDetail detail);
	FPerkNodeDetail LoadPerkDetails(FName key);
	void DeleteSaveFiles();
	
private:
	int32 perk_points;
	UPROPERTY()
	TMap<FName, FPerkNodeDetail> perk_node_map_;
};
