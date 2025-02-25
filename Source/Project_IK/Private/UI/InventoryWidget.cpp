/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 2.06.2025
Summary : Source file for inventory widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "UI/InventoryWidget.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"
#include "Components/WrapBox.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

#include "Managers/EnumCluster.h"
#include "Managers/InventoryManager.h"
#include "Structs/SpawnData.h"
#include "Subsystems/LevelTransitionSubsystem.h"
#include "UI/InventorySlot.h"
#include "WorldSettings/IKGameInstance.h"


void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
	switch_hero_left_button_->OnClicked.AddDynamic(this, &UInventoryWidget::SwitchToLeftHero);
	switch_hero_right_button_->OnClicked.AddDynamic(this, &UInventoryWidget::SwitchToRightHero);
}

void UInventoryWidget::NativeDestruct()
{
	switch_hero_left_button_->OnClicked.RemoveAll(this);
	switch_hero_right_button_->OnClicked.RemoveAll(this);
	Super::NativeDestruct();
}

void UInventoryWidget::InitInventoryWidget(UInventoryManager* inventory_manager)
{
	inventory_manager_ref_ = inventory_manager;
	hero_armor_->slot_type_ = EInventorySlotType::Armor;
	hero_trinket_->slot_type_ = EInventorySlotType::Trinket;
	hero_weapon_->slot_type_ = EInventorySlotType::Weapon;
	hero_passive_skill_->slot_type_ = EInventorySlotType::PassiveSkill;
	hero_active_skill_->slot_type_ = EInventorySlotType::ActiveSkill;
	hero_oopart_->slot_type_ = EInventorySlotType::Oopart;

	scroll_box_->AddChild(wrap_box_);
}

void UInventoryWidget::LoadInventoryManager()
{
	UIKGameInstance* ik_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	ULevelTransitionSubsystem* transition_system = ik_instance->GetLevelTransitionSubsystem();
	if(transition_system->GetSpawnData().IsEmpty() == false)
	{
		FSpawnData data_cache = transition_system->GetSpawnData(cur_hero_idx_);
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

void UInventoryWidget::ApplyInventoryManager()
{
	auto& inven_data = inventory_manager_ref_->GetInventory();
	for(int i = 0; i < inventory_slots_.Num(); i++)
	{
		inven_data[i] = inventory_slots_[i]->slot_data_;
	}
}

void UInventoryWidget::SwitchToLeftHero()
{
	ApplyInventoryManager();
	cur_hero_idx_ = FMath::Max(0, cur_hero_idx_ - 1);
	LoadInventoryManager();
}

void UInventoryWidget::SwitchToRightHero()
{
	ApplyInventoryManager();
	cur_hero_idx_ = FMath::Min(cur_hero_idx_ + 1, 3);
	LoadInventoryManager();
}
