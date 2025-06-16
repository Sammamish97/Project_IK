/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 10.13.2024
Summary : Source file for Skill Bar UI.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "UI/HitPointsUI.h"

#include "Blueprint/WidgetTree.h"
#include "Components/ProgressBar.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"

#include "UI/BuffDisplayer.h"

#include "Kismet/GameplayStatics.h"
#include "WorldSettings/IKGameInstance.h"
#include "Managers/DataTableManager.h"
#include "Managers/EnumCluster.h"
#include "Structs/BuffStatusData.h"

void UHitPointsUI::NativeConstruct()
{
	Super::NativeConstruct();

	InitializeImages();

	// If did not update HP explicitly before this function, it may not work
		// because initialize HP bar fully in default.
	UpdateHPWidget(1.f);
	UpdateShieldWidget(0.f);
	UpdateBuffWidgets();

	data_table_manager_ = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->GetDataTableManager();
}

void UHitPointsUI::NativeDestruct()
{
	Super::NativeDestruct();

	debuff_displayers_.Empty();
	buff_displayers_.Empty();
}

void UHitPointsUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
}

void UHitPointsUI::UpdateAppliedBuffs(TArray<FBuffStatusData> applied_buffs)
{
	buffs_array_ = applied_buffs;
	UpdateBuffWidgets();
}

void UHitPointsUI::UpdateAppliedCCs(TArray<ECCType> applied_ccs)
{
	ccs_array_ = applied_ccs;
	UpdateBuffWidgets();
}

void UHitPointsUI::UpdateHPWidget(float hp_ratio)
{
	if (hp_progress_bar_)
	{
		hp_progress_bar_->SetPercent(hp_ratio);
	}
}

void UHitPointsUI::UpdateShieldWidget(float shield_ratio)
{
	if (shield_progress_bar_)
	{
		if (shield_ratio <= 0.f)
		{
			shield_progress_bar_->SetVisibility(ESlateVisibility::Hidden);
		}
		else
		{
			shield_progress_bar_->SetPercent(shield_ratio);
			if (shield_progress_bar_->GetVisibility() != ESlateVisibility::Visible)
			{
				shield_progress_bar_->SetVisibility(ESlateVisibility::Visible);
			}
		}
	}
}

void UHitPointsUI::UpdateBuffWidgets()
{	// Display buff icons, hide the rest of them.
	TMap<ECharacterStatType, int32> buff_counts;
	TMap<ECharacterStatType, int32> debuff_counts;
	for (const FBuffStatusData& buff : buffs_array_)
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

void UHitPointsUI::InitializeImages()
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

void UHitPointsUI::UpdateBuffDisplayers(TArray<TObjectPtr<UBuffDisplayer>>& displayers, const TMap<ECharacterStatType, int32>& counts, const FLinearColor& background_color)
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

void UHitPointsUI::UpdateDebuffDisplayers(TArray<TObjectPtr<UBuffDisplayer>>& displayers, const TMap<ECharacterStatType, int32>& counts, const TArray<ECCType>& appliedCCs, const FLinearColor& background_color)
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

void UHitPointsUI::UpdateDisplayer(UBuffDisplayer* displayer, UTexture2D* texture, const FLinearColor& color, int32 duplicated_count)
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

void UHitPointsUI::HideUnusedDisplayers(TArray<TObjectPtr<UBuffDisplayer>>& displayers, int32 start_index)
{
	for (int32 i = start_index; i < DISPLAYER_SIZE; i++)
	{
		if (displayers[i].Get() && displayers[i]->GetVisibility() != ESlateVisibility::Hidden)
		{
			displayers[i]->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}
