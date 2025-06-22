/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 6.16.2025
Summary : Header file for Buff Popup Widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structs/BuffUIData.h"
#include "BuffPopupWidget.generated.h"

class UImage;
class UTextBlock;

UCLASS()
class PROJECT_IK_API UBuffPopupWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	void SetBuffDetail(FBuffUIData target_data);
	void ResetWidget();
	
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> thumbnail_;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> name_;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> detail_;
};
