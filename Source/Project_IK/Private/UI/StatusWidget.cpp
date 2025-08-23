/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 8.23.2025
Summary : Source file for status widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "UI/StatusWidget.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystems/LevelTransitionSubsystem.h"
#include "WorldSettings/IKGameInstance.h"

void UStatusWidget::NativeConstruct()
{
	Super::NativeConstruct();
	UIKGameInstance* game_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	text_manager_cache_ = game_instance->GetTextManager();
}

void UStatusWidget::LoadStatusData(EHeroType hero_type)
{
	TObjectPtr<UIKGameInstance> ik_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	TObjectPtr<ULevelTransitionSubsystem> transition_system = ik_instance->GetLevelTransitionSubsystem();
	FStatusData cur_status_data = transition_system->GetSpawnData(hero_type).character_data_.status_data_;

	hp_text_->SetText(text_manager_cache_->GetStatusText(ECharacterStatType::HitPoints));
	hp_val_->SetText(FText::AsNumber(cur_status_data.hit_point_));

	armor_text_->SetText(text_manager_cache_->GetStatusText(ECharacterStatType::Armor));
	armor_value_->SetText(FText::AsNumber(cur_status_data.armor_));

	dodge_text_->SetText(text_manager_cache_->GetStatusText(ECharacterStatType::EvasionRate));
	dodge_value_->SetText(FText::AsNumber(cur_status_data.evasion_rate_));

	survivability_text_->SetText(text_manager_cache_->GetStatusText(ECharacterStatType::Survivability));
	survivability_value_->SetText(FText::AsNumber(cur_status_data.survivability_));

	attack_power_text_->SetText(text_manager_cache_->GetStatusText(ECharacterStatType::AttackPower));
	attack_power_value_->SetText(FText::AsNumber(cur_status_data.attack_power_));

	attack_speed_text_->SetText(text_manager_cache_->GetStatusText(ECharacterStatType::AttackSpeed));
	attack_speed_value_->SetText(FText::AsNumber(cur_status_data.attack_speed_));

	crit_rate_text_->SetText(text_manager_cache_->GetStatusText(ECharacterStatType::CriticalHitRate));
	crit_rate_value_->SetText(FText::AsNumber(cur_status_data.critical_hit_rate_));

	vamp_rate_text_->SetText(text_manager_cache_->GetStatusText(ECharacterStatType::LifeSteal));
	vamp_rate_value_->SetText(FText::AsNumber(cur_status_data.life_steal_));

	skill_power_text_->SetText(text_manager_cache_->GetStatusText(ECharacterStatType::SkillPower));
	skill_power_value_->SetText(FText::AsNumber(cur_status_data.skill_power_));

	skill_cool_down_text_->SetText(text_manager_cache_->GetStatusText(ECharacterStatType::SkillCoolDown));
	skill_cool_down_value_->SetText(FText::AsNumber(cur_status_data.skill_cool_down_));
}
