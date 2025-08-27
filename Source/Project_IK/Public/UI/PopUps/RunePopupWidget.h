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
#include "Managers/EnumCluster.h"
#include "RunePopupWidget.generated.h"

class URunePopupDetailWidget;
class URuneMechanics;
class UTextBlock;
class UVerticalBox;


typedef TPair<ERuneSetType, TArray<int32>> RuneSetBonus;

UCLASS()
class PROJECT_IK_API URunePopupWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void InitSetBonusDetails(const TMap<EHeroType, TArray<RuneSetBonus>>& bonus_details);
	void UpdateRuneData(EHeroType type);
	void ResetWidget();
	
private:
	TMap<EHeroType, TArray<RuneSetBonus>> bonus_details_;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="RunePopupWidget", meta=(AllowPrivateAccess=true))
	TSubclassOf<URunePopupDetailWidget> rune_popup_detail_widget_class_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UVerticalBox> vertical_box_;
	
	UPROPERTY()
	TArray<TObjectPtr<URunePopupDetailWidget>> details_;
};
