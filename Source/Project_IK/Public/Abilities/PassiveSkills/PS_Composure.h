/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.21.2025
Summary : Header file for the Composure passive skill.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "PassiveSkillBase.h"
#include "Structs/BuffStatusData.h"
#include "PS_Composure.generated.h"

UCLASS()
class PROJECT_IK_API UPS_Composure : public UPassiveSkillBase
{
	GENERATED_BODY()
public:
	virtual void InitPassiveSkill(AActor* hero_ref, const FPassiveSkillData& skill_data) override;
	
private:
	void OnHPChanged(float hp_ratio);
	void ApplyBuff(float buff_amount);
	void RemoveBuff();

	float min_hp_ratio_ = 0.5f;
	float max_hp_ratio_ = 0.2f;

	float min_dodge_rate_ = 0.05f;
	float max_dodge_rate_ = 0.15f;

	bool is_buff_applied_ = false;
};
