/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 8.11.2025
Summary : Header file for Active Skill Popup Widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "BasicPopupWidget.h"
#include "ActiveSkillPopupWidget.generated.h"

class UTextBlock;

UCLASS()
class PROJECT_IK_API UActiveSkillPopupWidget : public UBasicPopupWidget
{
	GENERATED_BODY()
public:
	void UpdateCoolDown(float cool_time);
	
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> cool_time_text_;
};
