/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 8.24.2025
Summary : Header file for Map Hero Widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Managers/EnumCluster.h"
#include "MapHeroWidget.generated.h"

class UImage;
class UBasicPopupWidget;
class USegmentedHPUI;
class UBuffContainer;
class UBorder;

UCLASS()
class PROJECT_IK_API UMapHeroWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void InitHeroWidget(float max_hp, float cur_hp);
	USegmentedHPUI* GetHPWidget();
	
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBorder> color_border_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> hero_portrait_;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USegmentedHPUI> hp_bar_;
};
