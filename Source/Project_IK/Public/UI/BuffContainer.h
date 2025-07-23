/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 6.16.2025
Summary : Header file for Buff Container.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Managers/EnumCluster.h"
#include "BuffContainer.generated.h"

class USizeBox;
class UBuffPopupWidget;
class UBuffWidget;
class UHorizontalBox;

UCLASS()
class PROJECT_IK_API UBuffContainer : public UUserWidget
{
	GENERATED_BODY()
public:
	void InitBuffContainer(UBuffPopupWidget* popup_widget);

	UFUNCTION()
	void EnqueueBuff(EBuffType buff_type, UDisplayDataAsset* buff_data, bool is_permanent, float duration);
	UFUNCTION()
	void UpdateQueue(EBuffType buff_type);
	void ClearBuffQueue();
	
private:
	UPROPERTY()
	TMap<EBuffType, FTimerHandle> buff_timers_;
	
	UPROPERTY()
	TObjectPtr<UBuffPopupWidget> buff_popup_cache_;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USizeBox> size_box_;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UHorizontalBox> buff_container_;

	const int32 max_buffs_ = 5;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBuffWidget> buff_widget_0_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBuffWidget> buff_widget_1_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBuffWidget> buff_widget_2_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBuffWidget> buff_widget_3_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBuffWidget> buff_widget_4_;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta = (AllowPrivateAccess));
	float height_;
};