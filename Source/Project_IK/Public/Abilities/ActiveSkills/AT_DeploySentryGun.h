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

// It will be replaced to ASentryGun or something.
class ACover;

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UAT_DeploySentryGun : public UActiveSkillBase
{
	GENERATED_BODY()
public:

	UAT_DeploySentryGun();
	virtual void Decide(const FTargetResult& TargetResult) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ACover> actor_class_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float deployed_sentry_hit_points_ = 200.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float hit_points_scaling_factor_ = 0.8f;

protected:
	ACover* actor_;
};
