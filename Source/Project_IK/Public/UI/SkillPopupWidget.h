/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 6.13.2025
Summary : Header file for Skill Popup widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structs/ItemData.h"
#include "Components/TextBlock.h"
#include "SkillPopupWidget.generated.h"

enum class EHeroType : uint8;
class UImage;
class UTextBlock;
class UDisplayDataAsset;

UCLASS()
class PROJECT_IK_API USkillPopupWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void UpdatePopupData(UTexture2D* thumbnail, const FText& name, const FText& detail);
	
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> thumbnail_;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> skill_name_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> skill_detail_;
};
