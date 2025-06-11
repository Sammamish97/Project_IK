/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 6.06.2025
Summary : Header file for Hero widget UI.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HeroWidget.generated.h"

class UHP_UI_Widget;
class UMiniRuneBoardWidget;
class USkillButtonWidget;
UCLASS()
class PROJECT_IK_API UHeroWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	void InitHeroWidget(class URuneMechanics* rune_mechanics, float max_hp, float cur_hp);
	UHP_UI_Widget* GetHPWidget();
	UMiniRuneBoardWidget* GetMiniRuneBoardWidget();
	USkillButtonWidget* GetSkillButtonWidget();
	
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UHP_UI_Widget> hp_bar_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UMiniRuneBoardWidget> mini_rune_board_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USkillButtonWidget> active_skill_button_;
};
