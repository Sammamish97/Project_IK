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
#include "UnitWidget.generated.h"

class UBuffContainer;
enum class ECharacterStatType : uint8;
enum class ECCType : uint8;
class USegmentedHPUI;
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
	virtual void NativeConstruct() override;
	void InitHeroWidget(class URuneMechanics* rune_mechanics, float max_hp, float cur_hp);
	USegmentedHPUI* GetHPWidget();
	USkillButtonWidget* GetSkillButtonWidget();
	UBuffContainer* GetBuffContainer();

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USegmentedHPUI> hp_bar_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UMiniRuneBoardWidget> mini_rune_board_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class USkillButtonWidget> skill_button_widget_;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBuffContainer> buff_container_;
};
