/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 6.04.2025
Summary : Source file for Mini Rune Board widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "UI/MiniRuneBoardWidget.h"
#include "Characters/HeroBase.h"
#include "Components/Image.h"
#include "Components/RuneMechanics.h"
#include "Components/ProgressBar.h"
#include "UI/MiniRuneSlotWidget.h"

void UMiniRuneBoardWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	rune_array_.Empty();
	rune_array_.Add(rune_0_);
	rune_array_.Add(rune_1_);
	rune_array_.Add(rune_2_);
	rune_array_.Add(rune_3_);
	rune_array_.Add(rune_4_);
	rune_array_.Add(rune_5_);

	line_array_.Empty();
	line_array_.Add(line_0_);
	line_array_.Add(line_1_);
	line_array_.Add(line_2_);
	line_array_.Add(line_3_);
	line_array_.Add(line_4_);
	line_array_.Add(line_5_);
	line_array_.Add(line_6_);
	line_array_.Add(line_7_);
	line_array_.Add(line_8_);
	line_array_.Add(line_9_);
	line_array_.Add(line_10_);
	line_array_.Add(line_11_);	
}

void UMiniRuneBoardWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UMiniRuneBoardWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UMiniRuneBoardWidget::InitMiniRuneBoard(AHeroBase* owner)
{
	owner_hero_ = owner;
	auto owner_rune_mechanics = owner_hero_->GetRuneMechanics();
	auto rune_data_array = owner_rune_mechanics->GetEquippedRunes();
	TArray rune_widget_array = {rune_0_, rune_1_, rune_2_, rune_3_, rune_4_, rune_5_};
	for(int32 i = 0; i < 6; ++i)
	{
		if(rune_data_array[i].set_type != ERuneSetType::INVALID)
		{
			rune_widget_array[i]->image_->SetColorAndOpacity(FLinearColor::Red);	
		}
		else
		{
			rune_widget_array[i]->image_->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	auto result = owner_rune_mechanics->GetSetBonusData();
	for (const auto& elem : result)
	{
		if (elem.Value.Num() == 2)
		{
			line_array_[elem.Value[0]]->SetPercent(1.0);
		}
		else if (elem.Value.Num() == 3)
		{
			line_array_[6 + 3 * elem.Value[0]]->SetPercent(1.0);
			line_array_[7 + 3 * elem.Value[0]]->SetPercent(1.0);
			line_array_[8 + 3 * elem.Value[0]]->SetPercent(1.0);
		}
		else if (elem.Value.Num() == 6)
		{
			for (int i = 0; i < 6; ++i)
			{
				line_array_[i]->SetPercent(1.0);
			}
		}
	}
}
