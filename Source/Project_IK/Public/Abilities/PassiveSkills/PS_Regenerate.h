/******************************************************************************
Copyright(C) 2025
Author: Sinil Kang (rtd99062@gmail.com)
Creation Date : 4.26.2025
Summary : Header file for the regenerate passive skill.
					It restores skill owner's hit points.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Abilities/PassiveSkills/PassiveSkillBase.h"
#include "PS_Regenerate.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UPS_Regenerate : public UPassiveSkillBase
{
	GENERATED_BODY()

	virtual void InitEquipmentSkill(AActor* hero_ref) override;

protected:
	UFUNCTION()
	void Regenerate();

	FTimerHandle regenerate_timer_handler_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Passive Skills")
	float restore_hit_points_amount_ = 5.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Passive Skills")
	float regenerate_intervals_ = 1.f;
};
