/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 8.24.2025
Summary : Source file for Map HUD Widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "UI/Map/MapHUDWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "Managers/DataTableManager.h"
#include "Managers/InventoryManager.h"
#include "Subsystems/GlobalBuffSubsystem.h"
#include "Subsystems/LevelTransitionSubsystem.h"
#include "UI/GlobalBuffWidget.h"
#include "UI/Map/MapHeroWidget.h"
#include "WorldSettings/IKGameInstance.h"
#include "UI/PopUps/GlobalBuffPopupWidget.h"

void UMapHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
	TObjectPtr<UIKGameInstance> ik_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	UDataTableManager* data_table_cache = ik_instance->GetDataTableManager();
	inventory_manager_cache_ = ik_instance->GetInventoryManager();
	open_inventory_button_->OnClicked.AddDynamic(this, &UMapHUDWidget::OnOpenInventory);
	global_buff_popup_widget_->SetVisibility(ESlateVisibility::Hidden);

	TArray hero_widget_array = {hero_widget_0_, hero_widget_1_, hero_widget_2_, hero_widget_3_};
	TArray hero_type_array = {EHeroType::Hero1, EHeroType::Hero2, EHeroType::Hero3, EHeroType::Hero4};
	
	ULevelTransitionSubsystem* level_transition_subsystem = GetGameInstance()->GetSubsystem<ULevelTransitionSubsystem>();
	const auto& spawn_map = level_transition_subsystem->GetSpawnData();
	
	for (int32 i = 0; i < 4; ++i)
	{
		//Spawn Data에서 현재 HP를 가져온다.
		auto cur_spawn_data = spawn_map[hero_type_array[i]];

		//Char Data에서 최대 HP를 가져온다.
		auto cur_char_data = data_table_cache->GetCharacterData(HeroTypeToCharacterType(hero_type_array[i]));

		//HP Bar 업데이트
		hero_widget_array[i]->InitMapHeroWidget(cur_char_data.status_data_.hit_point_,
			cur_spawn_data.character_data_.status_data_.hit_point_,
			data_table_cache->GetHeroData(hero_type_array[i])
			);
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
		auto cur_global_buff_widget = CreateWidget<UGlobalBuffWidget>(global_buff_widget_holder_, global_buff_widget_class_);
		cur_global_buff_widget->InitGlobalBuffWidget(global_buff_popup_widget_, buffs[i]);
		global_buff_widget_holder_->AddChildToUniformGrid(cur_global_buff_widget, i / grid_column_, i % grid_column_);
	}
	

	auto text_manager = instance->GetTextManager();
	open_inventory_text_->SetText(text_manager->GetButtonText(EButtonType::OpenInventory));

	//IKTODO: 재화에 로컬라이징 적용하기.
	credit_text_->SetText(FText::FromString("Credits"));
	credit_value_text_->SetText(FText::AsNumber(inventory_manager_cache_->GetCredits()));
}

void UMapHUDWidget::OnOpenInventory()
{
	inventory_manager_cache_->OpenReadOnlyInventoryWidget();
}