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
#include "Interfaces/PassiveSkillInterface.h"
#include "PassiveSkillBase.generated.h"

UCLASS(Blueprintable, Abstract)
class PROJECT_IK_API UPassiveSkillBase : public UObject, public IPassiveSkillInterface
{
	GENERATED_BODY()
public:
	UPassiveSkillBase() = default;

public:
	virtual void InitEquipmentSkill(AActor* hero_ref) override;

protected:
	TWeakObjectPtr<AActor> hero_cache_;
};
