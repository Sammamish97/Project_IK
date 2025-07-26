/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 10.04.2024
Summary : Source file for Skill Bar UI.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "UI/ButtonBarWidget.h"
#include "UI/SupportSkillButtonWidget.h"
#include "UI/HeroWidget.h"
#include "UI/SkillPopupWidget.h"
#include "UI/BuffPopupWidget.h"

#include "Kismet/GameplayStatics.h"

#include "Components/Button.h"
#include "UI/RunePopupWidget.h"

#include "WorldSettings/IKGameModeBase.h"
#include "WorldSettings/IKPlayerController.h"

#include "WorldSettings/IKGameState.h"

void UButtonBarWidget::NativeConstruct()
{
	Super::NativeConstruct();
	support_skill_button_0_->button_->OnClicked.AddDynamic(this, &UButtonBarWidget::OnSupportSkillButtonClicked0);
	support_skill_button_1_->button_->OnClicked.AddDynamic(this, &UButtonBarWidget::OnSupportSkillButtonClicked1);
	support_skill_button_2_->button_->OnClicked.AddDynamic(this, &UButtonBarWidget::OnSupportSkillButtonClicked2);

	hero_widget_0_->GetSkillButtonWidget()->button_->OnClicked.AddDynamic(this, &UButtonBarWidget::OnActiveSkillButtonClicked0);
	hero_widget_1_->GetSkillButtonWidget()->button_->OnClicked.AddDynamic(this, &UButtonBarWidget::OnActiveSkillButtonClicked1);
	hero_widget_2_->GetSkillButtonWidget()->button_->OnClicked.AddDynamic(this, &UButtonBarWidget::OnActiveSkillButtonClicked2);
	hero_widget_3_->GetSkillButtonWidget()->button_->OnClicked.AddDynamic(this, &UButtonBarWidget::OnActiveSkillButtonClicked3);

	skill_popup_widget_->SetVisibility(ESlateVisibility::Hidden);
	rune_popup_widget_->SetVisibility(ESlateVisibility::Hidden);
	buff_popup_widget_->SetVisibility(ESlateVisibility::Hidden);

	game_state_cache_ = Cast<AIKGameState>(UGameplayStatics::GetGameState(GetWorld()));
	player_controller_cache_ = Cast<AIKPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	is_item_muted_ = false;
}

void UButtonBarWidget::NativeDestruct()
{
	TArray hero_widget_array = {hero_widget_0_, hero_widget_1_, hero_widget_2_, hero_widget_3_};
	for (const auto& elem : hero_widget_array)
	{
		elem->GetSkillButtonWidget()->button_->OnClicked.Clear();
	}
	TArray support_skill_widget_array = {support_skill_button_0_, support_skill_button_1_, support_skill_button_2_};
	for (const auto& elem : support_skill_widget_array)
	{
		elem->button_->OnClicked.Clear();
	}
}

void UButtonBarWidget::OnActiveSkillButtonClicked0()
{
	game_state_cache_->ActivateSkillTargeting(EHeroType::Hero1);
}

void UButtonBarWidget::OnActiveSkillButtonClicked1()
{
	game_state_cache_->ActivateSkillTargeting(EHeroType::Hero2);
}

void UButtonBarWidget::OnActiveSkillButtonClicked2()
{
	game_state_cache_->ActivateSkillTargeting(EHeroType::Hero3);
}

void UButtonBarWidget::OnActiveSkillButtonClicked3()
{
	game_state_cache_->ActivateSkillTargeting(EHeroType::Hero4);
}

void UButtonBarWidget::OnSupportSkillButtonClicked0()
{
	game_state_cache_->ActivateSupportSkill(0);
}

void UButtonBarWidget::OnSupportSkillButtonClicked1()
{
	game_state_cache_->ActivateSupportSkill(1);
}

void UButtonBarWidget::OnSupportSkillButtonClicked2()
{
	game_state_cache_->ActivateSupportSkill(2);
}

USupportSkillButtonWidget* UButtonBarWidget::GetSupportSkillButtonWidget(int32 idx)
{
	switch (idx)
	{
		case 0:
			return support_skill_button_0_;
		case 1:
			return support_skill_button_1_;
		case 2:
			return support_skill_button_2_;
		default:
			return nullptr;
	}
}

USkillButtonWidget* UButtonBarWidget::GetActiveSkillButtonWidget(EHeroType idx)
{
	switch (idx)
	{
	case EHeroType::Hero1:
		return hero_widget_0_->GetSkillButtonWidget();
	case EHeroType::Hero2:
		return hero_widget_1_->GetSkillButtonWidget();
	case EHeroType::Hero3:
		return hero_widget_2_->GetSkillButtonWidget();
	case EHeroType::Hero4:
		return hero_widget_3_->GetSkillButtonWidget();
	default:
		return nullptr;
	}
}

UHeroWidget* UButtonBarWidget::GetHeroWidget(EHeroType idx)
{
	switch (idx)
	{
	case EHeroType::Hero1:
		return hero_widget_0_;
	case EHeroType::Hero2:
		return hero_widget_1_;
	case EHeroType::Hero3:
		return hero_widget_2_;
	case EHeroType::Hero4:
		return hero_widget_3_;
	default:
		return nullptr;
	}
}

USkillPopupWidget* UButtonBarWidget::GetSkillPopupWidget()
{
	return skill_popup_widget_;
}

UBuffPopupWidget* UButtonBarWidget::GetBuffPopupWidget()
{
	return buff_popup_widget_;
}

URunePopupWidget* UButtonBarWidget::GetRunePopupWidget()
{
	return rune_popup_widget_;
}