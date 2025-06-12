/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 6.09.2025
Summary : Source file for Unit widget UI.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "UI/UnitWidget.h"

#include "Blueprint/WidgetTree.h"
#include "Components/HorizontalBox.h"
#include "Components/RuneMechanics.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/DataTableManager.h"
#include "Structs/BuffData.h"
#include "UI/BuffDisplayer.h"
#include "UI/SegmentedHPUI.h"
#include "UI/MiniRuneBoardWidget.h"
#include "UI/SkillButtonWidget.h"
#include "WorldSettings/IKGameInstance.h"

void UHeroWidget::NativeConstruct()
{
	Super::NativeConstruct();
	InitializeImages();

	UpdateBuffWidgets();
	data_table_manager_ = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->GetDataTableManager();
}

void UHeroWidget::InitHeroWidget(URuneMechanics* rune_mechanics,float max_hp, float cur_hp)
{
	hp_bar_->InitHPWidget(max_hp, cur_hp);
	mini_rune_board_->InitMiniRuneBoard(rune_mechanics);
}

USegmentedHPUI* UHeroWidget::GetHPWidget()
{
	return hp_bar_;
}

USkillButtonWidget* UHeroWidget::GetSkillButtonWidget()
{
	return skill_button_widget_;
}

void UHeroWidget::UpdateAppliedBuffs(TArray<FBuffData> applied_buffs)
{
	buffs_array_ = applied_buffs;
	UpdateBuffWidgets();
}

void UHeroWidget::UpdateAppliedCCs(TArray<ECCType> applied_ccs)
{
	ccs_array_ = applied_ccs;
	UpdateBuffWidgets();
}

void UHeroWidget::InitializeImages()
{
	for (int32 i = 0; i < DISPLAYER_SIZE; i++)
	{
		UBuffDisplayer* buff_displayer = WidgetTree->ConstructWidget<UBuffDisplayer>(buff_displayer_class_);
		buffs_container_->AddChildToHorizontalBox(buff_displayer);

		buff_displayers_.Add(buff_displayer);
	}
	for (int32 i = 0; i < DISPLAYER_SIZE; i++)
	{
		UBuffDisplayer* debuff_displayer = WidgetTree->ConstructWidget<UBuffDisplayer>(buff_displayer_class_);
		debuffs_container_->AddChildToHorizontalBox(debuff_displayer);

		debuff_displayers_.Add(debuff_displayer);
	}
}

void UHeroWidget::UpdateBuffWidgets()
{
	// Display buff icons, hide the rest of them.
	TMap<ECharacterStatType, int32> buff_counts;
	TMap<ECharacterStatType, int32> debuff_counts;
	for (const FBuffData& buff : buffs_array_)
	{
		// Buff if greater than 0 on raw data, greater than 1 on percentage data
		TMap<ECharacterStatType, int32>& target_map = (buff.is_percentage_) ? ((buff.value_ > 1.f) ? buff_counts : debuff_counts) : ((buff.value_ > 0.f) ? buff_counts : debuff_counts);

		// Find the value associated with a specified key, or if none exists, 
		// adds a value using the default constructor.
		// Increase value of TPair
		target_map.FindOrAdd(buff.stat_type_) += 1;
	}

	UpdateBuffDisplayers(buff_displayers_, buff_counts, FLinearColor::Green);

	UpdateDebuffDisplayers(debuff_displayers_, debuff_counts, ccs_array_, FLinearColor::Red);
}

void UHeroWidget::UpdateBuffDisplayers(TArray<TObjectPtr<UBuffDisplayer>>& displayers,
	const TMap<ECharacterStatType, int32>& counts, const FLinearColor& background_color)
{
	int i = 0;
	for (const TPair<ECharacterStatType, int32>& pair : counts)
	{
		if (i >= DISPLAYER_SIZE)
		{
			break;
		}
		
		UpdateDisplayer(displayers[i].Get(), data_table_manager_->GetStatTexture(pair.Key), background_color, pair.Value);
		++i;
	}
	HideUnusedDisplayers(displayers, i);
}

void UHeroWidget::UpdateDebuffDisplayers(TArray<TObjectPtr<UBuffDisplayer>>& displayers,
	const TMap<ECharacterStatType, int32>& counts, const TArray<ECCType>& appliedCCs,
	const FLinearColor& background_color)
{
	int i = 0;
	for (const TPair<ECharacterStatType, int32>& pair : counts)
	{
		if (i >= DISPLAYER_SIZE)
		{
			break;
		}

		UpdateDisplayer(displayers[i].Get(), data_table_manager_->GetStatTexture(pair.Key), background_color, pair.Value);
		++i;
	}
	for (ECCType cc_type : appliedCCs)
	{
		if (i >= DISPLAYER_SIZE)
		{
			break;
		}
		UpdateDisplayer(displayers[i].Get(), data_table_manager_->GetCCTexture(cc_type), background_color, 0);
		++i;
	}
	HideUnusedDisplayers(displayers, i);
}

void UHeroWidget::UpdateDisplayer(UBuffDisplayer* displayer, UTexture2D* texture, const FLinearColor& color,
	int32 duplicated_count)
{
	if (!displayer)
	{
		return;
	}

	if (displayer->GetVisibility() != ESlateVisibility::Visible)
	{
		displayer->SetVisibility(ESlateVisibility::Visible);
	}
	displayer->SetImage(texture);
	displayer->SetBackground(color);

	if (duplicated_count > 1)
	{
		displayer->SetDuplicatedText(duplicated_count);
	}
	else
	{
		displayer->HideText();
	}
}

void UHeroWidget::HideUnusedDisplayers(TArray<TObjectPtr<UBuffDisplayer>>& displayers, int32 start_index)
{
	for (int32 i = start_index; i < DISPLAYER_SIZE; i++)
	{
		if (displayers[i].Get() && displayers[i]->GetVisibility() != ESlateVisibility::Hidden)
		{
			displayers[i]->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}
