/******************************************************************************
Copyright(C) 2025
Author: Sinil Kang (rtd99062@gmail.com)
Creation Date : 4.25.2025
Summary : Header file for the agility skill.
					It buffs attack speed rate after active skill is invoked.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Abilities/PassiveSkills/PassiveSkillBase.h"
#include "Structs/BuffUIData.h"
#include "PS_Agility.generated.h"

class UNiagaraSystem;
class UNiagaraComponent;

UCLASS()
class PROJECT_IK_API UPS_Agility : public UPassiveSkillBase
{
	GENERATED_BODY()
public:

	virtual void InitEquipmentSkill(AActor* hero_ref) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UNiagaraSystem> skill_particle_system_;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UNiagaraSystem> hand_particle_system_;

protected:
	UFUNCTION()
	void BuffAttackSpeed();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Agility")
	FBuffStatusData buff_status_data_;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Agility")
	FBuffUIData buff_ui_data_;

	void SpawnParticles(AActor* actor);
	void ActivateParticles();
	void DeactivateParticles();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Passive Skills")
	float buff_amount_ = 1.2f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Passive Skills")
	bool is_buff_percentage_ = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Passive Skills")
	float buff_duration_ = 6.f;

	UPROPERTY()
	TObjectPtr<UNiagaraComponent> agility_particle_component_;
	UPROPERTY()
	TObjectPtr<UNiagaraComponent> hand_particle_component_1_;
	UPROPERTY()
	TObjectPtr<UNiagaraComponent> hand_particle_component_2_;
	FTimerHandle particle_deactivator_;
};
