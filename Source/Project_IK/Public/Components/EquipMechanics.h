/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 2.5.2025
Summary : Header file for the equip mechanics.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Structs/ArmorData.h"
#include "Structs/TrinketData.h"
#include "EquipMechanics.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECT_IK_API UEquipMechanics : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UEquipMechanics();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	FArmorData GetEquippedArmorData();
	void EquipArmor(EArmorType type);
	void UnEquipArmor();

	FTrinketData GetEquippedTrinketData();
	void EquipTrinket(ETrinketType type);
	void UnEquipTrinket();

private:
	FArmorData equipped_armor_data_;
	FTrinketData equipped_trinket_data_;
	
	class UDataTableManager* data_table_cache_;
	class AHeroBase* hero_cache_;
};
