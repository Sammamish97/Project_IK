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

UCLASS(Abstract)
class PROJECT_IK_API UAT_DeploySentryGun : public UActiveSkillBase
{
	GENERATED_BODY()
public:

	UAT_DeploySentryGun();
	virtual bool ActivateSkill(const FTargetResult& TargetResult) override;
	virtual void OnEnterCasting() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SkillData", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ASentryGun> sentry_gun_class_;
	
	UPROPERTY()
	TObjectPtr<ASentryGun> sentry_gun_actor_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SkillData", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> casting_anim_montage_;
};
