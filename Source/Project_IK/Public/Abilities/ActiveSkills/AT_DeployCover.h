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

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UAT_DeployCover : public USkillBase
{
	GENERATED_BODY()
public:

	UAT_DeployCover();
	virtual bool ActivateSkill_Implementation(const FTargetResult& TargetResult) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ACover> actor_class_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float deployed_cover_hit_points_ = 300.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float hit_points_scaling_factor_ = 1.f;

protected:
	ACover* actor_;
};
