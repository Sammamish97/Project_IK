/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 6.16.2025
Summary : Source file for Buff Popup Widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "UI/BuffPopupWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Structs/BuffData.h"

void UBuffPopupWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SetVisibility(ESlateVisibility::Hidden);
}

void UBuffPopupWidget::ResetWidget()
{
	SetVisibility(ESlateVisibility::Hidden);
	thumbnail_->SetBrushFromTexture(nullptr);
	name_->SetText(FText::FromString(""));
	TArray details = {detail_0_, detail_1_, detail_2_};
	
	for (int32 i = 0; i < 3; ++i)
	{
		details[i]->SetText(FText::FromString(""));
	}
}

void UBuffPopupWidget::SetBuffDetail(FBuffData target_data)
{
	SetVisibility(ESlateVisibility::Visible);
	thumbnail_->SetBrushFromTexture(target_data.thumbnail);
	name_->SetText(target_data.buff_name_);
	TArray details = {detail_0_, detail_1_, detail_2_};
	
	for (int32 i = 0; i < target_data.buff_status_.Num(); ++i)
	{
		FString result;
		result += StatToString(target_data.buff_status_[i].stat_type_);
		result += " ";
		if (target_data.buff_status_[i].is_percentage_)
		{
			if (target_data.buff_status_[i].value_ > 1.f)
			{
				result += FString(" + %d %%", (target_data.buff_status_[i].value_ - 1.f) * 100.f);
			}
			else
			{
				result += FString(" - %d %%", (1.f - target_data.buff_status_[i].value_) * 100.f);
			}
		}
		else
		{
			if (target_data.buff_status_[i].value_ > 1.f)
			{
				result += FString(" + %d %%", target_data.buff_status_[i].value_);
			}
			else
			{
				result += FString(" - %d %%", target_data.buff_status_[i].value_);
			}
		}
		details[i]->SetText(FText::FromString(result));
	}
}

//IKTODO: 로컬라이징 할 시 여기도 영향을 받는것을 잊으면 안됨.
FString UBuffPopupWidget::StatToString(ECharacterStatType stat)
{
	switch (stat)
	{
	case ECharacterStatType::AttackPower:
		return FString("Attack Power");
	case ECharacterStatType::AttackSpeed:
		return FString("Attack Speed");
	case ECharacterStatType::SkillPower:
		return FString("SKill Power");
	default:
		return FString("");
	}
}
