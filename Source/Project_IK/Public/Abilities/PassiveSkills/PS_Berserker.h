/******************************************************************************
Copyright(C) 2025
Author: Sinil Kang (rtd99062@gmail.com)
Creation Date : 4.28.2025
Summary : Header file for the berserker passive skill.
					It gives life steal and attack speed buffs.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Abilities/PassiveSkills/PassiveSkillBase.h"
#include "PS_Berserker.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UPS_Berserker : public UPassiveSkillBase
{
	GENERATED_BODY()
public:

	virtual void InitEquipmentSkill(AActor* hero_ref) override;



protected:
	UFUNCTION()
	void BuffBerserker(float hp_ratio);

	void ApplyBuff();
	void RemoveBuff();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Passive Skills")
	float hp_ratio_threshold_ = 0.2f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Passive Skills")
	float life_steal_buff_amount_ = 0.05f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Passive Skills")
	float attack_speed_buff_amount_ = 1.2f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Passive Skills")
	bool is_attack_speed_buff_percentage_ = true;

	bool is_buff_applied_ = false;
};
