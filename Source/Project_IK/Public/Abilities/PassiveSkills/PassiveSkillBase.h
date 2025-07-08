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
#include "Structs/BuffUIData.h"
#include "PassiveSkillBase.generated.h"

class UTextBlock;

UCLASS(Blueprintable, Abstract)
class PROJECT_IK_API UPassiveSkillBase : public UObject, public IPassiveSkillInterface
{
	GENERATED_BODY()
public:
	UPassiveSkillBase() = default;

public:
	virtual void InitEquipmentSkill(AActor* hero_ref) override;

protected:
	UPROPERTY(Transient)
	TWeakObjectPtr<AActor> hero_cache_;

	//기본적으로 패시브 스킬은 하나이상의 버프를 가지고 있다고 가정한다.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PassivSkillBase")
	FBuffUIData buff_ui_data_;
};
