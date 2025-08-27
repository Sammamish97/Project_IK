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
#include "Structs/HeroData.h"
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
class UBasicPopupWidget;
struct FBuffStatusData;

UCLASS()
class PROJECT_IK_API UHeroWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void InitHeroWidget(UBasicPopupWidget* popup_widget, class URuneMechanics* rune_mechanics, class URunePopupWidget* rune_popup_widget,
		EHeroType hero_type, float max_hp, float cur_hp, const FHeroData& hero_data);
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
