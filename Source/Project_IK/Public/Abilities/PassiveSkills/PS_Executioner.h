/******************************************************************************
Copyright(C) 2025
Author: Sinil Kang (rtd99062@gmail.com)
Creation Date : 4.28.2025
Summary : Header file for the Executioner passive skill.
					It gives attack speed for a second & reduce skill cooldown by a second.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Abilities/PassiveSkills/PassiveSkillBase.h"
#include "PS_Executioner.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UPS_Executioner : public UPassiveSkillBase
{
	GENERATED_BODY()
public:
	virtual void InitEquipmentSkill(AActor* hero_ref) override;

protected:
	UFUNCTION()
	void ApplyExecutionerBuff();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Passive Skills")
	float buff_amount_ = 1.15f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Passive Skills")
	bool is_buff_percentage_ = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Passive Skills")
	float buff_duration_ = 1.f;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Passive Skills")
	float reduce_cooltime_amount_ = 1.f;
};
