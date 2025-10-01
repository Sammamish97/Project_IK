/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 6.23.2025
Summary : Header file for Mini Rune Board Edge widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RuneBoardEdgeWidget.generated.h"
class UImage;
class USizeBox;
class UOverlay;

UCLASS()
class PROJECT_IK_API URuneBoardEdgeWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USizeBox> size_box_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> line_;
};
