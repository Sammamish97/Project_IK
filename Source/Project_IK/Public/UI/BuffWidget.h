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
#include "Structs/BuffData.h"
#include "BuffWidget.generated.h"

class UBuffPopupWidget;
class UBuffContainer;
class UProgressBar;

UCLASS()
class PROJECT_IK_API UBuffWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void InitWidget(UBuffPopupWidget* popup, UBuffContainer* container);
	void BeginBuffUI(FBuffData buff_data);
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	
	float GetLeftTime() const;
	FBuffData GetBuffDataCache() const;
	FProgressBarStyle GetProgressBarStyle() const;
	
	void SetWidget(const FProgressBarStyle& style, const FBuffData& data_cache, float left_time, bool is_available);
	void ResetWidget();
	bool IsWidgetAvailable() const;
	
private:
	UPROPERTY()
	TObjectPtr<UBuffContainer> container_ref_;

	UPROPERTY()
	TObjectPtr<UBuffPopupWidget> buff_popup_ref_;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> buff_image_;

	UPROPERTY()
	FBuffData buff_data_cache_;

	float left_time_ = 0.f;
	
	bool is_available_ = true;
};
