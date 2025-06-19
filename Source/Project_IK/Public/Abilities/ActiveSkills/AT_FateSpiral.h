/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 04.21.2025
Summary : Header file for an active skill named FateSpiral.
					It dispatches a wave that travels from an ally to an enemy and back again.
					It damages enemies it touches and heals allies when it returns.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Abilities/ActiveSkills/ActiveSkillBase.h"
#include "AT_FateSpiral.generated.h"

class AFateSpiral;

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UAT_FateSpiral : public UActiveSkillBase
{
	GENERATED_BODY()
public:

	UAT_FateSpiral();
	virtual bool ActivateSkill(const FTargetResult& TargetResult) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AFateSpiral> actor_class_;

protected:
	AFateSpiral* actor_ = nullptr;
};
