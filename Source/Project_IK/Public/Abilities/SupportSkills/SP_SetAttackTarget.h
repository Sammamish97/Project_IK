/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.24.2025
Summary : Header file for set attack target support skill.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "SupportSkillBase.h"
#include "SP_SetAttackTarget.generated.h"

class AHeroBase;
class UNiagaraSystem;

UCLASS()
class PROJECT_IK_API USP_SetAttackTarget : public USupportSkillBase
{
	GENERATED_BODY()
public:
	USP_SetAttackTarget();
	virtual bool ActivateSkill(const FTargetResult& TargetResult) override;
	virtual void ResetSkill() override;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UNiagaraSystem> target_vfx_;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FVector vfx_offset_;

private:
	FTargetParameters attack_target_params_ = FTargetParameters();

	UPROPERTY(Transient)
	TObjectPtr<AHeroBase> selected_hero_ = nullptr;
};
