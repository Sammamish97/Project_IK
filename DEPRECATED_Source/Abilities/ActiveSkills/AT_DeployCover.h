/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 04.22.2025
Summary : Header file for an active skill named DeployCover.
					It deploys a cover on the battlefield.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Abilities/ActiveSkills/ActiveSkillBase.h"
#include "Structs/BuffUIData.h"
#include "AT_DeployCover.generated.h"

class ACover;
class UNiagaraSystem;

UCLASS(Abstract)
class PROJECT_IK_API UAT_DeployCover : public UActiveSkillBase, public FTickableGameObject
{
	GENERATED_BODY()
public:
	UAT_DeployCover();
	virtual bool ActivateSkill(const FTargetResult& TargetResult) override;
	virtual void OnEnterCasting() override;

	virtual void Tick(float DeltaTime) override;
	inline virtual bool IsTickable() const override { return true; }
	inline virtual TStatId GetStatId() const override { RETURN_QUICK_DECLARE_CYCLE_STAT(UAT_DeployCover, STATGROUP_Tickables); }

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ACover> cover_b_class_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ACover> cover_a_class_;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UNiagaraSystem> deploy_particle_ = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float deployed_cover_hit_points_ = 300.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float hit_points_scaling_factor_ = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float deploy_height_offset_ = 2000.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float deploy_time_ = 0.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ThunderStorm", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> casting_anim_montage_;
	
	protected:
	UPROPERTY()
	ACover* actor_;

	UPROPERTY()
	FBuffUIData buff_ui_data_;

	UPROPERTY()
	FBuffStatusData buff_status_data_;

	FVector spawn_location_ = FVector::ZeroVector;
	FVector deploy_location_ = FVector::ZeroVector;
	bool is_deploying_ = false;
	float deploying_timer_ = 0.f;
};
