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

class UBuffHandler;
class UBulletMagnetizeEffectComponent;
class UNiagaraSystem;
class AHeroBase;

UCLASS(Abstract)
class PROJECT_IK_API UAT_MagnetizedBullet : public UActiveSkillBase
{
	GENERATED_BODY()

public:
	UAT_MagnetizedBullet();
	virtual void InitActiveSkill(AActor* skill_owner, const FActiveSkillData& skill_data) override;
	virtual bool ActivateSkill(const FTargetResult& TargetResult) override;

protected:
	void ApplyFXs(AHeroBase* hero);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UNiagaraSystem> magnetized_invoked_particle_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UBuffHandler> buff_class_;

	UPROPERTY()
	TObjectPtr<UBuffHandler> buff_;
};
