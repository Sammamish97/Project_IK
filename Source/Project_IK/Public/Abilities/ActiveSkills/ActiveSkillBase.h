/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 09.21.2024
Summary : Header file for Skill base class.
					It will be used like a pure virtual class. A skill class will derived it.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Abilities/SkillBase.h"
#include "Structs/ActiveSKillData.h"
#include "ActiveSkillBase.generated.h"

struct FDamageData;
struct FBuffStatusData;

UCLASS(Blueprintable, Abstract)
class PROJECT_IK_API UActiveSkillBase : public USkillBase
{
	GENERATED_BODY()
	
public:
	virtual bool ActivateSkill(const FTargetResult& TargetResult) override;
	void InitActiveSkill(AActor* skill_owner, const FActiveSkillData& skill_data);
	float GetCastingTime() const;
	float GetAIHoldTime() const;
	bool HasMotion() const;
	void ApplyDamage(FDamageData DamageData);

	virtual void OnEnterCasting();
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float scaling_factor_ = 1.f;
	
	UPROPERTY()
	TObjectPtr<AActor> skill_owner_ = nullptr;

	UPROPERTY()
	FActiveSkillData skill_data_ = FActiveSkillData();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool has_casting_motion_ = false;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float casting_time_ = 0.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float ai_holding_time_ = 0.f;
};
