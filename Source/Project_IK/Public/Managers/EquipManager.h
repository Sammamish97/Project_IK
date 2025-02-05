/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 2.5.2025
Summary : Header file for the equip manager.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Managers/EnumCluster.h"
#include "Structs/ArmorData.h"
#include "Structs/TrinketData.h"
#include "EquipManager.generated.h"

UCLASS()
class PROJECT_IK_API UEquipManager : public UObject
{
	GENERATED_BODY()
public:
	UEquipManager();
	FArmorData GetArmorData(EArmorType type);
	FString ArmorEnumToString(EArmorType armor_type);

	FTrinketData GetTrinketData(ETrinketType type);
	FString TrinketEnumToString(ETrinketType trinket_type);

private:
	UDataTable* armor_table_;
	UDataTable* trinket_table_;
};
