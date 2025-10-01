/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 8.11.2025
Summary : Header file for Single Rune Popup Widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "BasicPopupWidget.h"
#include "Managers/EnumCluster.h"
#include "SingleRunePopupWidget.generated.h"

UCLASS()
class PROJECT_IK_API USingleRunePopupWidget : public UBasicPopupWidget
{
	GENERATED_BODY()
public:
	void UpdateRuneData(ERuneSetType rune_type, ERuneSetBonusType set_type);
	
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<URichTextBlock> edge_name_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<URichTextBlock> triangle_name_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<URichTextBlock> hexagon_name_;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<URichTextBlock> edge_bonus_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<URichTextBlock> triangle_bonus_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<URichTextBlock> hexagon_bonus_;
};
