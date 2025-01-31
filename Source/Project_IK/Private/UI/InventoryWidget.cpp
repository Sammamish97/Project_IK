/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 1.10.2025
Summary : Source file for the Inventory Widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "UI/InventoryWidget.h"

#include "VectorTypes.h"
#include "Characters/HeroBase.h"
#include "Components/Button.h"
#include "Components/CharacterStatComponent.h"
#include "Components/WrapBox.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/DronePluginManager.h"
#include "Managers/LevelTransitionManager.h"
#include "Managers/InventoryManager.h"
#include "UI/DPSlot.h"
#include "WorldSettings/IKGameInstance.h"
#include "WorldSettings/IKGameModeBase.h"
void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
	switch_hero_left_button_->OnClicked.AddDynamic(this, &UInventoryWidget::SwitchToLeftHero);
	switch_hero_right_button_->OnClicked.AddDynamic(this, &UInventoryWidget::UInventoryWidget::SwitchToRightHero);
}

void UInventoryWidget::Initialize(UInventoryManager* inventory_component)
{
	inventory_manager_ref_ = inventory_component;
	heroDP_generic_->slot_type_ = EDPSlotType::HeroGeneral;
	heroDP_periodic_->slot_type_ = EDPSlotType::HeroPeriodic;
	scroll_box_->AddChild(wrap_box_);
}

void UInventoryWidget::LoadInventoryComponent()
{
	UIKGameInstance* ik_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	ULevelTransitionManager* transition_manager = ik_instance->GetLevelTransitionManager();
	if(transition_manager->GetSavedData().IsEmpty() == false)
	{
		auto data_cache = transition_manager->GetSavedData(cur_hero_idx_);
		const UDronePluginManager* dp_manager = ik_instance->GetDronePluginManager();
	
		heroDP_generic_->dp_data_ = dp_manager->GetDPData(data_cache.character_data_.general_dp_);
		heroDP_generic_->SetImageTexture();
		heroDP_periodic_->dp_data_ = dp_manager->GetDPData(data_cache.character_data_.periodic_dp_);
		heroDP_periodic_->SetImageTexture();

		hero_name_text_->SetText(FText::FromName(data_cache.character_data_.character_name_));
	}
	
	wrap_box_->ClearChildren();
	inventory_slots_.Reset();
	inventory_slots_.Init(nullptr, inventory_manager_ref_->GetInventorySize());
	auto inventory_data = inventory_manager_ref_->GetInventory();
	for(int i = 0; i < inventory_data.Num(); i++)
	{
		inventory_slots_[i] = Cast<UDPSlot>(CreateWidget(GetWorld(), slot_BP_class_));
		inventory_slots_[i]->dp_data_ = inventory_data[i];
		inventory_slots_[i]->grid_idx_ = i;
		inventory_slots_[i]->SetImageTexture();
		wrap_box_->AddChild(inventory_slots_[i]);
	}
}

void UInventoryWidget::SwitchToLeftHero()
{
	ApplyHeroDP();
	ApplyInventoryComponent();
	cur_hero_idx_ = FMath::Max(0, cur_hero_idx_ - 1);
	LoadInventoryComponent();
}

void UInventoryWidget::SwitchToRightHero()
{
	ApplyHeroDP();
	ApplyInventoryComponent();
	cur_hero_idx_ = FMath::Min(cur_hero_idx_ + 1, 3);
	LoadInventoryComponent();
}

void UInventoryWidget::ApplyHeroDP()
{
	UIKGameInstance* ik_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	ULevelTransitionManager* transition_manager = ik_instance->GetLevelTransitionManager();
	if(transition_manager->GetSavedData().IsEmpty() == false)
	{
		transition_manager->SetHeroGenericDPData(heroDP_generic_->dp_data_.dp_type_, cur_hero_idx_);
		transition_manager->SetHeroPeriodicDPData(heroDP_periodic_->dp_data_.dp_type_, cur_hero_idx_);
	}
}

void UInventoryWidget::ApplyInventoryComponent()
{
	auto& inven_data = inventory_manager_ref_->GetInventory();
	for(int i = 0; i < inventory_slots_.Num(); i++)
	{
		inven_data[i] = inventory_slots_[i]->dp_data_;
	}
}