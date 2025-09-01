/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 6.16.2025
Summary : Header file for Buff Widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Managers/EnumCluster.h"
#include "BuffWidget.generated.h"

class USizeBox;
class UDisplayDataAsset;
class UBuffPopupWidget;
class UBuffContainer;
class UProgressBar;
class UBasicPopupWidget;

UCLASS()
class PROJECT_IK_API UBuffWidget : public UUserWidget
{
	GENERATED_BODY()
	friend UBuffContainer;
	
public:
	void InitWidget(UBasicPopupWidget* popup, UBuffContainer* container);
	void BeginBuffUI();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

	bool GetIsPermanent() const;
	float GetDuration() const;
	float GetLeftTime() const;

	EBuffType GetCurBuffType() const;
	FProgressBarStyle GetProgressBarStyle() const;

	void SetWidget(const FProgressBarStyle& style, EBuffType buff_type, bool is_permanent, float duration, float left_time, bool is_available);
	
	void ResetWidget();
	bool IsWidgetAvailable() const;
	
private:
	UPROPERTY()
	TObjectPtr<UBuffContainer> container_ref_;

	UPROPERTY()
	TObjectPtr<UBasicPopupWidget> buff_popup_ref_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USizeBox> size_box_;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> buff_image_;

	UPROPERTY(EditDefaultsOnly, Category = "PassiveSkillData")
	TObjectPtr<UTexture2D> thumbnail_;
	
	UPROPERTY()
	EBuffType cur_buff_type_;
	
	float duration_ = 0.f;
	float left_time_ = 0.f;
	
	bool is_permanent_ = false;
	bool is_available_ = true;
};
