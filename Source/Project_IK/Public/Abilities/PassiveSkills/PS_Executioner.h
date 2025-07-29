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
class UBuffHandler;
UCLASS()
class PROJECT_IK_API UPS_Executioner : public UPassiveSkillBase
{
	GENERATED_BODY()
public:
	virtual void InitPassiveSkill(AActor* hero_ref, const FPassiveSkillData& skill_data) override;

protected:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TSubclassOf<UBuffHandler> buff_class_;

	UPROPERTY(Transient)
	TObjectPtr<UBuffHandler> buff_;
};
