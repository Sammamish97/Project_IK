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

#include "Managers/EnumCluster.h"
#include "UI/InventorySlot.h"

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
}

void UHeroInventoryWidget::ApplyInventoryComponent()
{
}

void UHeroInventoryWidget::SwitchToLeftHero()
{
}

void UHeroInventoryWidget::SwitchToRightHero()
{
}
