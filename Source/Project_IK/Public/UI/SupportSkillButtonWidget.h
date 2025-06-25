/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 6.12.2025
Summary : Header file for Support Skill Button Widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "SkillButtonWidget.h"
#include "SupportSkillButtonWidget.generated.h"

UCLASS()
class PROJECT_IK_API USupportSkillButtonWidget : public USkillButtonWidget
{
	GENERATED_BODY()
public:
	void SetSupportSkillCost(int32 cost);
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> cost_text_;
};
