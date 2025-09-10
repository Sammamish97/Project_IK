/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 09.09.2025
Summary : Header file for SaveGame that saves data about perks.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "SaveGame/BaseSaveGame.h"
#include "Structs/PerkNodeDetail.h"
#include "SavePerkProgress.generated.h"

UCLASS()
class PROJECT_IK_API USavePerkProgress : public UBaseSaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere)
	TMap<FName, FPerkNodeDetail> perk_node_map_;

	UPROPERTY(VisibleAnywhere)
	int32 perk_points_;
};
