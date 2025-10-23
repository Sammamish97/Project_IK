/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 01.15.2025
Summary : Source file for main Widget in StoreLevel.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "UI/StoreWidget.h"

#include "Kismet/GameplayStatics.h"
#include "WorldSettings/IKGameInstance.h"
#include "Managers/InventoryManager.h"
#include "Managers/DataTableManager.h"
#include "Structs/WrapperEquipmentData.h"

#include "WorldSettings/StoreLevel/IKStoreHUD.h"

#include "Blueprint/WidgetTree.h"
#include "UI/StoreSlot.h"
#include "UI/ConfirmationWidget.h"
#include "UI/CreditWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

#include "Subsystems/LevelTransitionSubsystem.h"
#include "UI/PopUps/ActiveSkillPopupWidget.h"
#include "UI/PopUps/SingleRunePopupWidget.h"
#include "UI/PopUps/WeaponPopupWidget.h"

#include "Subsystems/AudioManagerSubsystem.h"

template<typename ItemType, typename ItemContainer, typename SlotContainer>
inline void UStoreWidget::AddItems(TArray<ItemType> items, ItemContainer& item_container, SlotContainer& slot_container)
{
	for (int32 i = 0; i < items.Num(); i++)
	{
		UStoreSlot* slot = WidgetTree->ConstructWidget<UStoreSlot>(store_widget_class_);
		FRewardData reward;
		reward.SetData(items[i]);
		slot->SetItemData(reward);
		slot->SetStoreWidgetCache(this);
		slot->SetTexture(items[i].thumbnail_);
		slot->SetPrice(GetPriceByRarity(items[i].rarity_));
		slot->OnStoreSlotClickedDelegate.AddDynamic(this, &UStoreWidget::OnStoreSlotClicked);
		UHorizontalBoxSlot* box_slot = item_container->AddChildToHorizontalBox(slot);
		if (box_slot)
		{
			box_slot->SetPadding(slot_margin_);
		}
		slot_container.Add(slot);
	}
}


bool UStoreWidget::Initialize()
{
	Super::Initialize();
	total_cost_ = 0;
	credits_ = 0;
	return true;
}

void UStoreWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UIKGameInstance* game_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!game_instance)
	{
		return;
	}
	
	text_manager_cache_ = game_instance->GetTextManager();
	credits_ = game_instance->GetInventoryManager()->GetCredits();
	slot_margin_ = FMargin(30, 30);

	UDataTableManager* manager = game_instance->GetDataTableManager();
	if (store_widget_class_)
	{
		weapons_ = manager->GetUniqueWeaponDataRandomly(STOCK);
		AddItems(weapons_, weapon_slot_container_, weapon_slots_);
		active_skills_ = manager->GetUniqueActiveSkillDataRandomly(STOCK);
		AddItems(active_skills_, active_slot_container_, active_slots_);
		passive_skills_ = manager->GetUniquePassiveSkillDataRandomly(STOCK);
		AddItems(passive_skills_, passive_slot_container_, passive_slots_);
		runes_ = manager->GetUniqueRuneDataRandomly(RUNE_STOCK);
		AddItems(runes_, rune_slot_container_, rune_slots_);
	}
	confirmation_widget_->OnConfirmation.AddDynamic(this, &UStoreWidget::GoToNextLevel);

	pay_button_->OnClicked.AddDynamic(this, &UStoreWidget::OnPayButtonClicked);
	pay_text_->SetText(text_manager_cache_->GetStoreText(EStoreTextType::Leave));
}

void UStoreWidget::NativeDestruct()
{
	Super::NativeDestruct();

	pay_button_->OnClicked.Clear();

	if (confirmation_widget_->OnConfirmation.IsBound())
	{
		confirmation_widget_->OnConfirmation.Clear();
	}
}

void UStoreWidget::CreateWeaponPopupWidget(UTexture2D* thumbnail, const FText& name, const FText& detail,
											   const FWeaponStatusData& data)
{
	equip_popup_ptr_ = CreateWidget<UBasicPopupWidget>(this, weapon_popup_class_);
	equip_popup_ptr_->UpdatePopupData(thumbnail, name, detail);
	Cast<UWeaponPopupWidget>(equip_popup_ptr_)->UpdateWeaponData(data);
	equip_popup_ptr_->AddToViewport();
}

void UStoreWidget::CreateActiveSkillPopupWidget(UTexture2D* thumbnail, const FText& name, const FText& detail, float cool_down)
{
	equip_popup_ptr_ = CreateWidget<UBasicPopupWidget>(this, active_skill_popup_class_);
	equip_popup_ptr_->UpdatePopupData(thumbnail, name, detail);
	Cast<UActiveSkillPopupWidget>(equip_popup_ptr_)->UpdateCoolDown(cool_down);
	equip_popup_ptr_->AddToViewport();
}

void UStoreWidget::CreatePassiveSkillPopupWidget(UTexture2D* thumbnail, const FText& name, const FText& detail)
{
	equip_popup_ptr_ = CreateWidget<UBasicPopupWidget>(this, passive_skill_popup_class_);
	equip_popup_ptr_->UpdatePopupData(thumbnail, name, detail);
	equip_popup_ptr_->AddToViewport();
}

void UStoreWidget::CreateRunePopupWidget(UTexture2D* thumbnail, const FText& name, const FText& detail,
	ERuneSetType rune_set_type)
{
	equip_popup_ptr_ = CreateWidget<UBasicPopupWidget>(this, rune_popup_class_);
	equip_popup_ptr_->UpdatePopupData(thumbnail, name, detail);
	Cast<USingleRunePopupWidget>(equip_popup_ptr_)->UpdateRuneData(rune_set_type, ERuneSetBonusType::Hexagon);
	equip_popup_ptr_->AddToViewport();
}

void UStoreWidget::RemovePopupWidget()
{
	if(equip_popup_ptr_)
	{
		equip_popup_ptr_->Destruct();
		equip_popup_ptr_->SetVisibility(ESlateVisibility::Hidden);
		equip_popup_ptr_ = nullptr;
	}
}

void UStoreWidget::OnPayButtonClicked()
{
	if (!confirmation_widget_)
	{
		return;
	}

	if (total_cost_ <= 0)
	{
		UAudioManagerSubsystem::Get(this)->Play2D(EAudioType::UI_Confirm);
		confirmation_widget_->SetText(text_manager_cache_->GetStoreText(EStoreTextType::ConfirmLeave));
		confirmation_widget_->SetVisibility(ESlateVisibility::Visible);
	}
	else if (total_cost_ <= credits_)
	{
		UAudioManagerSubsystem::Get(this)->Play2D(EAudioType::UI_StorePurchase);
		// Are you sure you want to purchase this item? This action cannot be undone.
		confirmation_widget_->SetText(text_manager_cache_->GetStoreText(EStoreTextType::ConfirmPurchase));
		confirmation_widget_->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		UAudioManagerSubsystem::Get(this)->Play2D(EAudioType::UI_Deny);
		casher_text_->SetText(text_manager_cache_->GetStoreText(EStoreTextType::NotEnoughCredit));
	}
}

void UStoreWidget::OnStoreSlotClicked()
{
	total_cost_ = 0;
	for (int32 i = 0; i < STOCK; i++)
	{
		if (weapon_slots_[i]->IsChecked())
		{
			total_cost_ += weapon_slots_[i]->GetPrice();
		}
		if (active_slots_[i]->IsChecked())
		{
			total_cost_ += active_slots_[i]->GetPrice();
		}
		if (passive_slots_[i]->IsChecked())
		{
			total_cost_ += passive_slots_[i]->GetPrice();
		}
	}
	for (int32 i = 0; i < RUNE_STOCK; i++)
	{
		if (rune_slots_[i]->IsChecked())
		{
			total_cost_ += rune_slots_[i]->GetPrice();
		}
	}

	total_cost_text_->SetText(FText::AsNumber(total_cost_));

	// Update button style
	if (total_cost_ <= 0)
	{
		pay_text_->SetText(text_manager_cache_->GetStoreText(EStoreTextType::Leave));
	}
	else
	{
		pay_text_->SetText(text_manager_cache_->GetStoreText(EStoreTextType::Purchase));
	}
}

int32 UStoreWidget::GetPriceByRarity(ERarity rarity)
{
	switch (rarity)
	{
	case ERarity::Legendary:
		return 100;
		break;
	case ERarity::Rare:
		return 75;
		break;
	case ERarity::Common:
	default:
		return 50;
		break;
	}
}

void UStoreWidget::GoToNextLevel()
{
	UIKGameInstance* game_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	// Save purchased items and dps
	UInventoryManager* inventory_manager = game_instance->GetInventoryManager();
	inventory_manager->SetCredits(credits_ - total_cost_);
	credit_widget_->UpdateCreditText();


	FWrapperEquipmentData data;
	for (int32 i = 0; i < STOCK; i++)
	{
		if (weapon_slots_[i]->IsChecked())
		{
			data += weapons_[i];
		}
		if (active_slots_[i]->IsChecked())
		{
			data += active_skills_[i];
		}
		if (passive_slots_[i]->IsChecked())
		{
			data += passive_skills_[i];
		}
	}
	for (int32 i = 0; i < RUNE_STOCK; i++)
	{
		if (rune_slots_[i]->IsChecked())
		{
			data += runes_[i];
		}
	}
	game_instance->GetInventoryManager()->OpenInventoryWidgetReward(data, [&]() 
		{
			GetGameInstance()->GetSubsystem<ULevelTransitionSubsystem>()->OpenMapLevel(GetWorld());
		});

}
