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
#include <functional>
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
	//Demo: TestSkill_1은 받는 피해를 고정적으로 3씩 차감한다.
	void TestSkill_1_Prepare();
	static FDamageData TestSkill_1(UArmorMechanics* target, FDamageData dmg_input);
	void TestSkill_1_Terminate();

public:
	FArmorData GetEquippedArmorData();
	void EquipArmor(EArmorType type);
	void UnEquipArmor();
	std::function<FDamageData(UArmorMechanics*, FDamageData)> OnArmorHitFunction;
	std::function<FDamageData(UArmorMechanics*, FDamageData)> OnArmorHealFunction;
	std::function<FDamageData(UArmorMechanics*, FDamageData)> OnArmorHPChangedFunction;

private:
	FArmorData equipped_armor_data_;
	class UArmorManager* armor_manager_cache_;
};
