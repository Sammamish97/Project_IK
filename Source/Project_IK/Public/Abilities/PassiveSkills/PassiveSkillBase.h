/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 2.5.2025
Summary : Header file for the equip skill base.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Structs/PassiveSkillData.h"
#include "PassiveSkillBase.generated.h"

class UTextBlock;

UCLASS(Blueprintable, Abstract)
class PROJECT_IK_API UPassiveSkillBase : public UObject
{
	GENERATED_BODY()
public:
	virtual void InitPassiveSkill(AActor* hero_ref, const FPassiveSkillData& skill_data);

protected:
	UPROPERTY(Transient)
	TWeakObjectPtr<AActor> hero_cache_;

	UPROPERTY(Transient)
	FPassiveSkillData skill_data_;
};
