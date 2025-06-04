/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 6.04.2025
Summary : Heeader file for Mini Rune Board widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MiniRuneBoardWidget.generated.h"

class UImage;
UCLASS()
class PROJECT_IK_API UMiniRuneBoardWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	
	void InitMiniRuneBoard(class AHeroBase* owner);
	
private:
	UPROPERTY()
	TObjectPtr<class AHeroBase> owner_hero_;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UBorder> border_;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> rune_0_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> rune_1_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> rune_2_;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> rune_3_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> rune_4_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> rune_5_;
};
