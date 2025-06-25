/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 04.17.2025
Summary : Header file for Magnetized Bullet Active Skill.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Abilities/ActiveSkills/ActiveSkillBase.h"
#include "AT_MagnetizedBullet.generated.h"

class UNiagaraSystem;
class UBulletChainEffectComponent;

UCLASS()
class PROJECT_IK_API UAT_MagnetizedBullet : public UActiveSkillBase
{
	GENERATED_BODY()

public:
	UAT_MagnetizedBullet();
	virtual bool ActivateSkill(const FTargetResult& TargetResult) override;
	void OnFinishSkill();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UBulletChainEffectComponent> on_hit_class_;

protected:
	float duration_ = 0.f;
	FTimerHandle duration_timer_handle_;
};
