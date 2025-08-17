/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 8.15.2025
Summary : Header file for perk popup Widget

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structs/PerkNodeDetail.h"
#include "PerkPopupWidget.generated.h"

class UImage;
class UHorizontalBox;
class UTextBlock;
class UTextManager;

UCLASS()
class PROJECT_IK_API UPerkPopupWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	void UpdatePosition();
	void UpdateSkillDetail();

	UFUNCTION()
	void SetPerkData(const FPerkNodeDetail& perk_data);
	
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> cost_text_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> name_text_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> detail_text_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> name_bottom_image_;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> detail_bottom_image_;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UHorizontalBox> hb_purchase_skill_;

	UPROPERTY()
	FPerkNodeDetail perk_data_;

	UPROPERTY(Transient)
	TObjectPtr<UTextManager> text_manager_cache_;

	float offset_x;
	float offset_y;
};
