/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 6.17.2025
Summary : Header file for Rune Popup Widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Subsystems/PerkProgressSubsystem.h"
#include "RunePopupWidget.generated.h"

class URuneMechanics;
class UTextBlock;

UCLASS()
class PROJECT_IK_API URunePopupWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void InitSetBonusDetails(const TMap<EHeroType, TArray<FString>> bonus_details);
	void UpdateRuneData(EHeroType type);
	void ResetWidget();
	
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> name_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> detail_0_;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> detail_1_;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> detail_2_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> detail_3_;

	TMap<EHeroType, TArray<FString>> bonus_details_;
};
