/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 2.09.2025
Summary : Header file for Passive Skill Mechanics.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Structs/PassiveSkillData.h"
#include "PassiveSkillMechanics.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECT_IK_API UPassiveSkillMechanics : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPassiveSkillMechanics();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	FPassiveSkillData GetEquippedPassiveSkillData();
	void EquipPassiveSkill(EPassiveSkillType type);
	void UnEquipPassiveSkill();
	
private:
	FPassiveSkillData equipped_passiev_skill_data_;
	
	class UDataTableManager* equip_manager_cache_;
	class AHeroBase* hero_cache_;
};
