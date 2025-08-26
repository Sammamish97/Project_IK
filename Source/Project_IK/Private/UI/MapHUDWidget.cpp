/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 8.24.2025
Summary : Source file for Map HUD Widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "UI/MapHUDWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "Managers/DataTableManager.h"
#include "Managers/InventoryManager.h"
#include "Subsystems/GlobalBuffSubsystem.h"
#include "Subsystems/LevelTransitionSubsystem.h"
#include "UI/GlobalBuffWidget.h"
#include "UI/MapHeroWidget.h"
#include "WorldSettings/IKGameInstance.h"
#include "UI/PopUps/GlobalBuffPopupWidget.h"

void UMapHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
	inventory_manager_cache_ = Cast<UIKGameInstance>(GetGameInstance())->GetInventoryManager();
	open_inventory_button_->OnClicked.AddDynamic(this, &UMapHUDWidget::OnOpenInventory);
	global_buff_popup_widget_->SetVisibility(ESlateVisibility::Hidden);

	TArray hero_widget_array = {hero_widget_0_, hero_widget_1_, hero_widget_2_, hero_widget_3_};
	TArray hero_type_array = {EHeroType::Hero1, EHeroType::Hero2, EHeroType::Hero3, EHeroType::Hero4};
	
	ULevelTransitionSubsystem* level_transition_subsystem = GetGameInstance()->GetSubsystem<ULevelTransitionSubsystem>();
	const auto& spawn_map = level_transition_subsystem->GetSpawnData();

	auto data_table_cache = Cast<UIKGameInstance>(GetGameInstance())->GetDataTableManager();

	for (int32 i = 0; i < 4; ++i)
	{
		//Spawn Data에서 현재 HP를 가져온다.
		auto cur_spawn_data = spawn_map[hero_type_array[i]];

		//Char Data에서 최대 HP를 가져온다.
		auto cur_char_data = data_table_cache->GetCharacterData(HeroTypeToCharacterType(hero_type_array[i]));

		//HP Bar 업데이트
		hero_widget_array[i]->InitHeroWidget(cur_char_data.status_data_.hit_point_,
			cur_spawn_data.character_data_.status_data_.hit_point_);
	}

	//Global Buff 생성
	UGlobalBuffSubsystem* global_buff_subsystem = GetGameInstance()->GetSubsystem<UGlobalBuffSubsystem>();
	TArray<FGlobalBuffData> buffs = global_buff_subsystem->GetBuffs();
	
	UIKGameInstance* instance = Cast<UIKGameInstance>(GetGameInstance());
	if (instance)
	{
		UDataTableManager* data_table_manager = instance->GetDataTableManager();
		TSet<EGlobalBuffType> everlasting_buff_types = global_buff_subsystem->GetEverlastingBuffTypes();
		for (EGlobalBuffType type : everlasting_buff_types)
		{
			buffs.Add(data_table_manager->GetGlobalBuffData(type));
		}
	}

	int32 buff_amount = buffs.Num();
	for (size_t i = 0; i < buff_amount; i++)
	{
		//IKTODO: 이 if문은 테스트 이후 반드시 사라져야 한다. Display Data가 반드시 있어야 하기 때문이다.
		if (buffs[i].display_data_)
		{
			auto cur_global_buff_widget = CreateWidget<UGlobalBuffWidget>(global_buff_widget_holder_, global_buff_widget_class_);
			cur_global_buff_widget->InitGlobalBuffWidget(buffs[i].display_data_, global_buff_popup_widget_, buffs[i].duration_);
			if (auto GridSlot = Cast<UUniformGridSlot>(cur_global_buff_widget->Slot))
			{
				GridSlot->SetHorizontalAlignment(HAlign_Center);
				GridSlot->SetVerticalAlignment(VAlign_Center);
			}
			global_buff_widget_holder_->AddChildToUniformGrid(cur_global_buff_widget, i / grid_column_, i % grid_column_);
		}
	}
	

	//IKTODO: 재화 업데이트
	credit_text_->SetText(FText::FromString("Credits"));
	credit_value_text_->SetText(FText::AsNumber(inventory_manager_cache_->GetCredits()));
}

void UMapHUDWidget::InitMapHUD()
{
}

void UMapHUDWidget::OnOpenInventory()
{
	inventory_manager_cache_->OpenReadOnlyInventoryWidget();
}