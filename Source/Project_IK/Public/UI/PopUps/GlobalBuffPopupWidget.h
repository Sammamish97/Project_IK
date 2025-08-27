/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 8.24.2025
Summary : Header file for Global Buff Popup Widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "BasicPopupWidget.h"
#include "GlobalBuffPopupWidget.generated.h"

UCLASS()
class PROJECT_IK_API UGlobalBuffPopupWidget : public UBasicPopupWidget
{
	GENERATED_BODY()
public:
	void UpdateLeftDuration(float left_duration);

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> left_duration_text_;
};
