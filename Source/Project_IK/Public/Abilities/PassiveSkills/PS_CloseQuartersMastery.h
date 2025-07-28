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
class UBuffHandler;
UCLASS()
class PROJECT_IK_API UPS_CloseQuartersMastery : public UPassiveSkillBase
{
	GENERATED_BODY()
public:
	virtual void InitPassiveSkill(AActor* hero_ref, const FPassiveSkillData& skill_data) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Agility")
	TSubclassOf<UBuffHandler> buff_class_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Agility")
	TObjectPtr<UBuffHandler> buff_;
};
