/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 11.17.2024
Summary : Header file for Combat Result block class.
						It is an attachment for CombatResultUI. It is not be used itself alone.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CombatResultBlock.generated.h"

class UVerticalBox;
class UImage;
class USpacer;
class USizeBox;
class UProgressBar;
class UHorizontalBox;
class UTextBlock;

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UCombatResultBlock : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void SetHPPercent(float ratio);

	UFUNCTION(BlueprintPure)
	float GetHPPercent();

	UFUNCTION(BlueprintCallable)
	void SetHPOpacity(float opacity);

	UFUNCTION(BlueprintCallable)
	void SetDamageDealt(float damage);

	void SetInjuredVisibility(ESlateVisibility visibility);
	void SetInjuredOpacity(float opacity);

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> hero_portrait_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> hp_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> deal_icon_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> deal_text_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> injured_;
};
