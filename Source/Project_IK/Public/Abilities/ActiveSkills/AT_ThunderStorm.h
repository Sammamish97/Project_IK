/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 04.18.2025
Summary : Header file for an active skill named ThunderStorm.
					It periodically summons thunders that damages in an area.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Abilities/ActiveSkills/ActiveSkillBase.h"
#include "AT_ThunderStorm.generated.h"

class AThunderStorm;

UCLASS(Abstract)
class PROJECT_IK_API UAT_ThunderStorm : public UActiveSkillBase
{
	GENERATED_BODY()
public:
	UAT_ThunderStorm();
	virtual bool ActivateSkill(const FTargetResult& TargetResult) override;
	virtual void OnEnterCasting() override;

protected:
	UFUNCTION()
	void DamageEnemies();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float damage_ = 0.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visuals", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AThunderStorm> visual_actor_class_;
	
	UPROPERTY()
	TObjectPtr<AThunderStorm> visual_actor_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ThunderStorm", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> casting_anim_montage_;
};
