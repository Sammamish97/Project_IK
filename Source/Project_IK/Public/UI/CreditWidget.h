/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 01.07.2025
Summary : Header file for a widget to display credits.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CreditWidget.generated.h"

class UTextBlock;
class UInventoryManager;

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UCreditWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void UpdateCreditText();

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TWeakObjectPtr<UTextBlock> credit_text_;

	UPROPERTY()
	TWeakObjectPtr<UInventoryManager> inventory_manager_;
};
