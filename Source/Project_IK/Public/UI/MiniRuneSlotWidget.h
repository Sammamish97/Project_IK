/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 6.05.2025
Summary : Header file for Mini Rune Slot widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MiniRuneSlotWidget.generated.h"

UCLASS(Abstract)
class PROJECT_IK_API UMiniRuneSlotWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class USizeBox> size_box_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> image_;
};
