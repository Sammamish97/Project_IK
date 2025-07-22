/******************************************************************************
Copyright(C) 2025
Author: Sinil Kang (rtd99062@gmail.com)
Creation Date : 4.28.2025
Summary : Header file for the berserker passive skill.
					It gives life steal and attack speed buffs.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Abilities/PassiveSkills/PassiveSkillBase.h"
#include "PS_Berserker.generated.h"

class UBuffBase;
class AUnit;
class UNiagaraSystem;
class UNiagaraComponent;

UCLASS()
class PROJECT_IK_API UPS_Berserker : public UPassiveSkillBase
{
	GENERATED_BODY()
public:
	virtual void InitPassiveSkill(AActor* hero_ref, const FPassiveSkillData& skill_data) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UNiagaraSystem> skill_particle_system_;

protected:
	UFUNCTION()
	void BuffBerserker(float hp_ratio);

	void ApplyBuff();
	void RemoveBuff();

	void SpawnParticles(AUnit* actor);
	void ActivateParticles();
	void DeactivateParticles();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Passive Skills")
	TSubclassOf<UBuffBase> buff_class_;

	UPROPERTY(Transient)
	TObjectPtr<UBuffBase> buff_;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Passive Skills")
	float hp_ratio_threshold_ = 0.8f;
	
	bool is_buff_applied_ = false;

	UPROPERTY()
	TObjectPtr<UNiagaraComponent> berserker_particle_component_;
};
