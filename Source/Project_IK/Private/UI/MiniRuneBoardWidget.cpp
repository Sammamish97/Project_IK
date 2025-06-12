/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 6.04.2025
Summary : Source file for Mini Rune Board widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "UI/MiniRuneBoardWidget.h"
#include "Components/Image.h"
#include "Components/RuneMechanics.h"
#include "Components/ProgressBar.h"
#include "UI/MiniRuneSlotWidget.h"

void UMiniRuneBoardWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UMiniRuneBoardWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UMiniRuneBoardWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UMiniRuneBoardWidget::InitMiniRuneBoard(URuneMechanics* rune_mechanics)
{
	TArray line_array = {line_0_, line_1_, line_2_, line_3_, line_4_, line_5_, line_6_, line_7_, line_8_, line_9_, line_10_, line_11_};
	TArray rune_widget_array = {rune_0_, rune_1_, rune_2_, rune_3_, rune_4_, rune_5_};
	auto rune_data_array = rune_mechanics->GetEquippedRunes();

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

	auto result = rune_mechanics->GetSetBonusData();
	for (const auto& elem : result)
	{
		if (elem.Value.Num() == 2)
		{
			line_array[elem.Value[0]]->SetPercent(1.0);
		}
		else if (elem.Value.Num() == 3)
		{
			line_array[6 + 3 * elem.Value[0]]->SetPercent(1.0);
			line_array[7 + 3 * elem.Value[0]]->SetPercent(1.0);
			line_array[8 + 3 * elem.Value[0]]->SetPercent(1.0);
		}
		else if (elem.Value.Num() == 6)
		{
			for (int i = 0; i < 6; ++i)
			{
				line_array[i]->SetPercent(1.0);
			}
		}
	}
}