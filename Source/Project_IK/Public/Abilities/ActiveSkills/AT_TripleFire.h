/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 4.12.2025
Summary : Header file for TripleFire Active Skill.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Abilities/ActiveSkills/ActiveSkillBase.h"
#include "Structs/BuffStatusData.h"
#include "AT_TripleFire.generated.h"

UCLASS(Abstract)
class PROJECT_IK_API UAT_TripleFire : public UActiveSkillBase
{
	GENERATED_BODY()

public:
	UAT_TripleFire();
	virtual void InitActiveSkill(AActor* skill_owner, const FActiveSkillData& skill_data) override;
	virtual bool ActivateSkill(const FTargetResult& TargetResult) override;

private:
	virtual void OnTripleFire();

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="TripleFire", meta=(AllowPrivateAccess=true))
	float attack_speed_buff_amount_ = 5.5f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="TripleFire", meta=(AllowPrivateAccess=true))
	float upgraded_buff_amount_ = 3.5f;
	
	FBuffStatusData buff_status_data_;
	bool on_triple_fire_ = false;
	int32 fire_counter_ = 0.f;
};
