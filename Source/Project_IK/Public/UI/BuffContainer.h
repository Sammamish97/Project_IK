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
#include "Structs/BuffData.h"
#include "Managers/EnumCluster.h"
#include "BuffContainer.generated.h"

class UBuffWidget;
class UHorizontalBox;

UCLASS()
class PROJECT_IK_API UBuffContainer : public UUserWidget
{
	GENERATED_BODY()
public:
	void NativeConstruct() override;
	void NativeDestruct() override;

	UFUNCTION()
	void EnqueueBuff(FBuffData buff_data);
	UFUNCTION()
	void UpdateQueue(EBuffType remove_target_type);
	void ClearBuffQueue();
	
private:
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
};