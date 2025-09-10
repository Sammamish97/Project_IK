/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 04.22.2025
Summary : Header file for an active skill named DeployCover.
					It deploys a sentry gun on the battlefield.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Abilities/ActiveSkills/ActiveSkillBase.h"
#include "AT_DeploySentryGun.generated.h"

class ASentryGun;
class UNiagaraSystem;

UCLASS(Abstract)
class PROJECT_IK_API UAT_DeploySentryGun : public UActiveSkillBase, public FTickableGameObject
{
	GENERATED_BODY()
public:

	UAT_DeploySentryGun();
	virtual bool ActivateSkill(const FTargetResult& TargetResult) override;
	virtual void OnEnterCasting() override;

	virtual void Tick(float DeltaTime) override;
	inline virtual bool IsTickable() const override { return true; }
	inline virtual TStatId GetStatId() const { RETURN_QUICK_DECLARE_CYCLE_STAT(UAT_DeploySentryGun, STATGROUP_Tickables); }

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SkillData")
	TSubclassOf<ASentryGun> sentry_gun_class_;
	
	UPROPERTY()
	TObjectPtr<ASentryGun> sentry_gun_actor_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SkillData")
	TObjectPtr<UAnimMontage> casting_anim_montage_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UNiagaraSystem> deploy_particle_ = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float deploying_height_offset_ = 2000.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float deploy_time_ = 0.5f;


	bool is_deploying_ = false;
	float deploying_timer_ = 0.f;
	FVector deploying_location_ = FVector::ZeroVector;
	FVector spawn_location_ = FVector::ZeroVector;
};
