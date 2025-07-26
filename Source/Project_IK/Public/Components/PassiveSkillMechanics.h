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

class UPassiveSkillBase;
class AHeroBase;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECT_IK_API UPassiveSkillMechanics : public UActorComponent
{
	GENERATED_BODY()

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	void EquipPassiveSkill(const FPassiveSkillData& skill_data, int32 idx);
	void InitPassiveSkill();
	void UnEquipPassiveSkill(int32 idx);
	
private:
	UPROPERTY()
	TArray<FPassiveSkillData> equipped_passive_skill_data_;

	UPROPERTY()
	TArray<TObjectPtr<UPassiveSkillBase>> passive_skills_;
	
	UPROPERTY()
	TObjectPtr<AHeroBase> hero_cache_;
};
