/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 10.04.2024
Summary : Source file for Skill Bar UI.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "UI/ButtonBarWidget.h"
#include "UI/SkillButtonWidget.h"
#include "UI/HeroWidget.h"

#include "Kismet/GameplayStatics.h"

#include "Components/Button.h"

#include "WorldSettings/IKGameModeBase.h"
#include "WorldSettings/IKGameState.h"

void UButtonBarWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	TArray hero_widget_array = {hero_widget_0_, hero_widget_1_, hero_widget_2_, hero_widget_3_};
	TArray active_skill_button_delegate_array = {&UButtonBarWidget::OnActiveSkillButtonClicked0, &UButtonBarWidget::OnActiveSkillButtonClicked1,
		&UButtonBarWidget::OnActiveSkillButtonClicked2, &UButtonBarWidget::OnActiveSkillButtonClicked3};
	for (int32 i = 0; i < hero_widget_array.Num(); i++)
	{
		hero_widget_array[i]->GetSkillButtonWidget()->button_->OnClicked.AddDynamic(this, active_skill_button_delegate_array[i]);
	}
	
	TArray support_skill_widget_array = {support_skill_button_0_, support_skill_button_1_, support_skill_button_2_};
	TArray support_skill_button_delegate_array = {&UButtonBarWidget::OnSupportSkillButtonClicked0, &UButtonBarWidget::OnSupportSkillButtonClicked1
		, &UButtonBarWidget::OnSupportSkillButtonClicked2};

	for (int32 i = 0; i < support_skill_widget_array.Num(); i++)
	{
		support_skill_widget_array[i]->button_->OnClicked.AddDynamic(this, support_skill_button_delegate_array[i]);
	}

	game_state_cache_ = Cast<AIKGameState>(UGameplayStatics::GetGameState(GetWorld()));
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
	game_state_cache_->ActivateActiveSkill(EHeroType::Hero1);
}

void UButtonBarWidget::OnActiveSkillButtonClicked1()
{
	game_state_cache_->ActivateActiveSkill(EHeroType::Hero2);
}

void UButtonBarWidget::OnActiveSkillButtonClicked2()
{
	game_state_cache_->ActivateActiveSkill(EHeroType::Hero3);
}

void UButtonBarWidget::OnActiveSkillButtonClicked3()
{
	game_state_cache_->ActivateActiveSkill(EHeroType::Hero4);
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

USkillButtonWidget* UButtonBarWidget::GetSkillButtonWidget(int32 idx)
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