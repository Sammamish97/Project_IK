/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 2.22.2025
Summary : Header file for Thunder Active Skill.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Abilities/ActiveSkills/ActiveSkillBase.h"
#include "Structs/TargetResult.h"
#include "AT_Thunder.generated.h"

class UNiagaraSystem;

UCLASS(Abstract)
class PROJECT_IK_API UAT_Thunder : public UActiveSkillBase
{
	GENERATED_BODY()
public:
	UAT_Thunder();
	virtual void InitActiveSkill(AActor* skill_owner, const FActiveSkillData& skill_data) override;
	virtual bool CanActivateSkill(const FTargetResult& TargetResult) override;
	virtual bool ActivateSkill(const FTargetResult& TargetResult) override;
	virtual void OnEnterCasting() override;

protected:
	void PlaySFX(const FVector& location);
	void PlayVFX(const FVector& location);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UNiagaraSystem> zap_vfx_;

	float damage_ = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SkillData", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> casting_anim_montage_;
};
