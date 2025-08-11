/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 6.25.2025
Summary : Header file for Rune Popup Detail Widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RunePopupDetailWidget.generated.h"

class UTextBlock;
class UImage;
class UBorder;

UCLASS()
class PROJECT_IK_API URunePopupDetailWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBorder> border_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> thumbnail_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> set_bonus_type_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> set_bonus_detail_;
};
