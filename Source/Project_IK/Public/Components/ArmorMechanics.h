/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 2.1.2025
Summary : Header file for the ArmorMechanics.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Structs/ArmorData.h"
#include "Structs/DamageData.h"
#include "ArmorMechanics.generated.h"
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECT_IK_API UArmorMechanics : public UActorComponent
{
	GENERATED_BODY()
public:
	// Sets default values for this component's properties
	UArmorMechanics();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	FArmorData GetEquippedArmorData();
	void EquipArmor(EArmorType type);
	void UnEquipArmor();

private:
	FArmorData equipped_armor_data_;
	
	class UArmorManager* armor_manager_cache_;
	class AHeroBase* hero_cache_;
};
