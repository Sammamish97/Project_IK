/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 6.09.2025
Summary : Header file for Unit widget UI.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Managers/EnumCluster.h"
#include "HeroWidget.generated.h"

class UBuffContainer;
enum class ECharacterStatType : uint8;
enum class ECCType : uint8;
class USegmentedHPUI;
class UBorder;
class UHorizontalBox;
class UBuffDisplayer;
class UDataTableManager;
class USkillButtonWidget;
struct FBuffStatusData;

UCLASS()
class PROJECT_IK_API UHeroWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void InitHeroWidget(class UBuffPopupWidget* popup_widget, class URuneMechanics* rune_mechanics, class URunePopupWidget* rune_popup_widget,
		EHeroType hero_type, FColor hero_base_color_1, FColor hero_base_color_2, float max_hp, float cur_hp);
	USegmentedHPUI* GetHPWidget();
	USkillButtonWidget* GetSkillButtonWidget();
	UBuffContainer* GetBuffContainer();

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBorder> color_border_;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USegmentedHPUI> hp_bar_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UMiniRuneBoardWidget> mini_rune_board_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class USkillButtonWidget> skill_button_widget_;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBuffContainer> buff_container_;
};
