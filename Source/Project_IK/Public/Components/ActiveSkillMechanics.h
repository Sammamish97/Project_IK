/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 2.22.2025
Summary : Header file for Active Skill Mechanics.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Structs/ActiveSkillData.h"
#include "ActiveSkillMechanics.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECT_IK_API UActiveSkillMechanics : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UActiveSkillMechanics();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	FActiveSkillData GetEquippedActiveSkill();
	void EquipActiveSkill(EActiveSkillType type);
	void UnEquipActiveSkill();
	
private:
	FActiveSkillData equipped_active_skill_data_;
	UActiveSkillBase* active_skill_cache_;
	
	class UDataTableManager* equip_manager_cache_;
	class AHeroBase* hero_cache_;
};