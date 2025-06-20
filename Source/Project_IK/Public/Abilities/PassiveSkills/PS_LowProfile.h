/******************************************************************************
Copyright(C) 2025
Author: Sinil Kang (rtd99062@gmail.com)
Creation Date : 5.2.2025
Summary : Header file for the low profile passive skill.
					It gives evade rate buffs when they are not in cover.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Abilities/PassiveSkills/PassiveSkillBase.h"
#include "PS_LowProfile.generated.h"

class UNiagaraSystem;
class UNiagaraComponent;

UCLASS()
class PROJECT_IK_API UPS_LowProfile : public UPassiveSkillBase
{
	GENERATED_BODY()
public:

	virtual void InitEquipmentSkill(AActor* hero_ref) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UNiagaraSystem> skill_particle_system_;

protected:
	UFUNCTION()
	void ApplyBuff();
	UFUNCTION()
	void RemoveBuff();

	void AttachParticles(USceneComponent* attached_component);
	void ActivateParticles();
	void DeactivateParticles();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Passive Skills")
	TObjectPtr<class UBuffDataAsset> buff_data_asset_;
	
	bool is_buff_applied_ = false;

	UPROPERTY()
	TObjectPtr<UNiagaraComponent> left_elbow_particle_;

	UPROPERTY()
	TObjectPtr<UNiagaraComponent> right_elbow_particle_;

	UPROPERTY()
	TObjectPtr<UNiagaraComponent> left_foot_particle_;

	UPROPERTY()
	TObjectPtr<UNiagaraComponent> right_foot_particle_;
};
