/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 2.06.2025
Summary : Source file for inventory widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "UI/HeroInventoryWidget.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"
#include "Components/WrapBox.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

#include "Managers/EnumCluster.h"
#include "Managers/HeroInventoryManager.h"
#include "Managers/LevelTransitionManager.h"
#include "UI/InventorySlot.h"
#include "WorldSettings/IKGameInstance.h"

void UHeroInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
	switch_hero_left_button_->OnClicked.AddDynamic(this, &UHeroInventoryWidget::SwitchToLeftHero);
	switch_hero_right_button_->OnClicked.AddDynamic(this, &UHeroInventoryWidget::SwitchToRightHero);
}

void UHeroInventoryWidget::InitInventoryWidget(UHeroInventoryManager* inventory_component)
{
	inventory_manager_ref_ = inventory_component;
	hero_armor_->slot_type_ = EInventorySlotType::Armor;
	hero_trinket_->slot_type_ = EInventorySlotType::Trinket;
	scroll_box_->AddChild(wrap_box_);
}

void UHeroInventoryWidget::LoadInventoryComponent()
{
	UIKGameInstance* ik_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	ULevelTransitionManager* transition_manager = ik_instance->GetLevelTransitionManager();
	if(transition_manager->GetSavedData().IsEmpty() == false)
	{
		auto data_cache = transition_manager->GetSavedData(cur_hero_idx_);
		hero_name_text_->SetText(FText::FromName(data_cache.character_data_.character_name_));
	}
	
	wrap_box_->ClearChildren();
	inventory_slots_.Reset();
	inventory_slots_.Init(nullptr, inventory_manager_ref_->GetInventorySize());
	auto inventory_data = inventory_manager_ref_->GetInventory();
	for(int i = 0; i < inventory_data.Num(); i++)
	{
		inventory_slots_[i] = Cast<UInventorySlot>(CreateWidget(GetWorld(), slot_BP_class_));
		inventory_slots_[i]->slot_data_ = inventory_data[i];
		inventory_slots_[i]->slot_type_ = EInventorySlotType::Inventory;
		inventory_slots_[i]->grid_idx_ = i;
		inventory_slots_[i]->SetImageTexture();
		wrap_box_->AddChild(inventory_slots_[i]);
	}
}

void UHeroInventoryWidget::ApplyInventoryComponent()
{
	auto& inven_data = inventory_manager_ref_->GetInventory();
	for(int i = 0; i < inventory_slots_.Num(); i++)
	{
		inven_data[i] = inventory_slots_[i]->slot_data_;
	}
}

void UHeroInventoryWidget::SwitchToLeftHero()
{
	ApplyInventoryComponent();
	cur_hero_idx_ = FMath::Max(0, cur_hero_idx_ - 1);
	LoadInventoryComponent();
}

void UHeroInventoryWidget::SwitchToRightHero()
{
	ApplyInventoryComponent();
	cur_hero_idx_ = FMath::Min(cur_hero_idx_ + 1, 3);
	LoadInventoryComponent();
}
