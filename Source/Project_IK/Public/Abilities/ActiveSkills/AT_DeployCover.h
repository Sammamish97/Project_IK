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
#include "Abilities/SkillBase.h"
#include "AT_DeployCover.generated.h"

class ACover;
class UNiagaraSystem;

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UAT_DeployCover : public USkillBase, public FTickableGameObject
{
	GENERATED_BODY()
public:

	UAT_DeployCover();
	virtual bool ActivateSkill_Implementation(const FTargetResult& TargetResult) override;

	virtual void Tick(float DeltaTime) override;
	inline virtual bool IsTickable() const override { return true; }
	inline virtual TStatId GetStatId() const override { RETURN_QUICK_DECLARE_CYCLE_STAT(UAT_DeployCover, STATGROUP_Tickables); }

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ACover> actor_class_;

protected:
	void UpdateNavMesh();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UNiagaraSystem> deploy_particle_ = nullptr;

	UPROPERTY()
	ACover* actor_ = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float deployed_cover_hit_points_ = 300.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float hit_points_scaling_factor_ = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float deploy_height_offset_ = 2000.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float deploy_time_ = 0.5f;

	FVector spawn_location_ = FVector::ZeroVector;
	FVector deploy_location_ = FVector::ZeroVector;
	bool is_deploying_ = false;
	float deploying_timer_ = 0.f;
};
