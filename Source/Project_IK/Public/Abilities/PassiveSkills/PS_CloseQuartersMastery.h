/******************************************************************************
Copyright(C) 2025
Author: Sinil Kang (rtd99062@gmail.com)
Creation Date : 4.28.2025
Summary : Header file for the CloseQuatersMastery passive skill.
					It gives high critical rate if damaged enemy is nearby.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Abilities/PassiveSkills/PassiveSkillBase.h"
#include "PS_CloseQuartersMastery.generated.h"

struct FDamageData;

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UPS_CloseQuartersMastery : public UPassiveSkillBase
{
	GENERATED_BODY()
public:

	virtual void InitEquipmentSkill(AActor* hero_ref) override;



protected:
	UFUNCTION()
	void CloseQuatersMastery(float& critical_rate);

	float GetDistance2D(const AActor* hero, const AActor* target, float weapon_range);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float max_critical_rate_bonus_ = 50.f;
};
