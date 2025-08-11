/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 8.11.2025
Summary : Header file for Support skill Popup Widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "BasicPopupWidget.h"
#include "SupportSkillPopupWidget.generated.h"


UCLASS()
class PROJECT_IK_API USupportSkillPopupWidget : public UBasicPopupWidget
{
	GENERATED_BODY()
public:
	void UpdateCost(int32 cool_time);
	
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> cost_text_;
};
