/******************************************************************************
Copyright(C) 2025
Author: Sinil Kang (rtd99062@gmail.com)
Creation Date : 5.2.2025
Summary : Header file for the stable first round passive skill.
					It gives high critical rate buffs on the first shot in megazines.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Abilities/PassiveSkills/PassiveSkillBase.h"
#include "PS_StableFirstRound.generated.h"
class UBuffHandler;
UCLASS()
class PROJECT_IK_API UPS_StableFirstRound : public UPassiveSkillBase
{
	GENERATED_BODY()
public:
	virtual void InitPassiveSkill(AActor* hero_ref, const FPassiveSkillData& skill_data) override;

private:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TSubclassOf<UBuffHandler> buff_class_;

	UPROPERTY(Transient)
	TObjectPtr<UBuffHandler> buff_;
};
