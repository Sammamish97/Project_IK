/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 04.19.2025
Summary : Header file for an active skill named Encourage.
					Buffs of attack speed & skill cool-time in a range of allies.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Abilities/ActiveSkills/ActiveSkillBase.h"
#include "AT_Encourage.generated.h"

class UBuffHandler;
class UNiagaraSystem;

UCLASS(Abstract)
class PROJECT_IK_API UAT_Encourage : public UActiveSkillBase
{
	GENERATED_BODY()
public:
	UAT_Encourage();
	virtual void OnEnterCasting() override;
	virtual void InitActiveSkill(AActor* skill_owner, const FActiveSkillData& skill_data) override;
	virtual bool ActivateSkill(const FTargetResult& TargetResult) override;

protected:
	void SpawnSkillParticle(const FTargetResult& TargetResult);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SkillData")
	TSubclassOf<UBuffHandler> buff_class_;

	UPROPERTY();
	TObjectPtr<UBuffHandler> buff_;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SkillData")
	TObjectPtr<UAnimMontage> casting_anim_montage_;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UNiagaraSystem> encourage_fx_;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UNiagaraSystem> encouraged_target_fx_;
};
