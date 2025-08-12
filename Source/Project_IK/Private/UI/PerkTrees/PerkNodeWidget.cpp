/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 8.13.2025
Summary : Source file for perk node widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "UI/PerkTrees/PerkNodeWidget.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/Button.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
#include "Components/Overlay.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UI/PerkTrees/PerkConnectionWidget.h"

void UPerkNodeWidget::UnlockSkill()
{
	if (perk_detail_.locked_)
	{
		perk_detail_.locked_ = false;
		SaveSkill();
	}
}

void UPerkNodeWidget::PurchaseSkill()
{
	perk_detail_.purchased_ = true;
	RemoveSkillPoint(perk_detail_.cost_);
}

bool UPerkNodeWidget::CanPurchase()
{
	//어딘가에서 cost를 받아와야 함.
	int32 hard_code_cost = 3;
	return perk_detail_.cost_ < hard_code_cost &&
		perk_detail_.purchased_ == false &&
		perk_detail_.locked_ == false;
}

void UPerkNodeWidget::RemoveSkillPoint(int32 amount)
{
	//어딘가에서 cost를 받아와야 함
	
}

bool UPerkNodeWidget::IsPurchased()
{
	return perk_detail_.purchased_;
}

void UPerkNodeWidget::ConnectPerkNodes()
{
	if (connected_indices_.IsEmpty()) return;
	auto connected_skills = GetConnectedSkills();
	for (auto widget : connected_skills)
	{
		if (skill_connection_overlay_->GetChildrenCount() != connected_indices_.Num())
		{
			FVector2D connection_begin_point = UWidgetLayoutLibrary::SlotAsCanvasSlot(this)->GetPosition();
			FVector2D connection_end_point =  UWidgetLayoutLibrary::SlotAsCanvasSlot(widget)->GetPosition();
			FVector2D end_to_begin = connection_end_point - connection_begin_point;

			auto new_connection = CreateWidget<UPerkConnectionWidget>(GetWorld(), perk_connection_widget_class_);
			new_connection->InitConnection(this, end_to_begin, perk_connection_color_);

			skill_connection_overlay_->AddChild(new_connection);
		}
	}
}

TArray<UPerkNodeWidget*> UPerkNodeWidget::GetConnectedSkills()
{
	TArray<UUserWidget*> output_;
	TArray<UPerkNodeWidget*> result_;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), output_, UPerkNodeWidget::StaticClass(), false);
	for (auto widget : output_)
	{
		UPerkNodeWidget* casted_skill = Cast<UPerkNodeWidget>(widget);
		if(connected_indices_.Contains(casted_skill->perk_index_) && result_.Contains(casted_skill) == false)
		{
			result_.Add(casted_skill);
		}
	}
	return result_;
}

TArray<UPerkNodeWidget*> UPerkNodeWidget::GetAllSkills()
{
	TArray<UUserWidget*> output_;
	TArray<UPerkNodeWidget*> result_;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), output_, StaticClass());
	for (auto widget : output_)
	{
		UPerkNodeWidget* casted_skill = Cast<UPerkNodeWidget>(widget);
		result_.Add(casted_skill);
	}
	return result_;
}

FLinearColor UPerkNodeWidget::LinearColorLerp(float duration)
{
	timer_ = UKismetMathLibrary::FInterpTo_Constant(duration,
			UKismetMathLibrary::SelectFloat(duration, 0, button_->IsPressed() && CanPurchase()),
			UGameplayStatics::GetWorldDeltaSeconds(GetWorld()),
			1.0f);

	if (timer_ == duration)
	{
		PurchaseSkill();
		return FLinearColor();
	}
	return UKismetMathLibrary::LinearColorLerp(FLinearColor(), purchased_color_, timer_/duration);
}

void UPerkNodeWidget::SetAlignment()
{
	if (UCanvasPanelSlot* canvas_slot = UWidgetLayoutLibrary::SlotAsCanvasSlot(this))
	{
		canvas_slot->SetAlignment({0.5f, 0.5f});
		canvas_slot->SetAutoSize(true);
	}
	
}

ESlateVisibility UPerkNodeWidget::SetUnlockedImageVisibility()
{
	if (CanPurchase())
	{
		return ESlateVisibility::HitTestInvisible;
	}
	return ESlateVisibility::Collapsed;
}

ESlateVisibility UPerkNodeWidget::SetLockIconVisibility()
{
	if (perk_detail_.locked_)
	{
		return ESlateVisibility::HitTestInvisible;
	}
	return ESlateVisibility::Collapsed;
}

FLinearColor UPerkNodeWidget::SetIconColor()
{
	if (perk_detail_.purchased_)
	{
		return UKismetMathLibrary::CInterpTo(thumbnail_->GetColorAndOpacity(),
			purchased_color_,
			UGameplayStatics::GetWorldDeltaSeconds(GetWorld()),
			100.f);
	}
	if (perk_detail_.locked_)
	{
		return FLinearColor();
	}
	return LinearColorLerp(0.9f);
	
}

FSlateBrush UPerkNodeWidget::SetIconBrush()
{
	return UWidgetBlueprintLibrary::MakeBrushFromTexture(perk_detail_.thumbnail, 60, 60);
}

ESlateVisibility UPerkNodeWidget::SetCheckVisibility()
{
	if (perk_detail_.purchased_)
	{
		return ESlateVisibility::HitTestInvisible;
	}
	return ESlateVisibility::Collapsed;
}

void UPerkNodeWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	SetAlignment();
	FLatentActionInfo info;
	UKismetSystemLibrary::Delay(GetWorld(), 1, info);
	ConnectPerkNodes();
}

void UPerkNodeWidget::NativeConstruct()
{
	Super::NativeConstruct();
	//IKTODO: 여기서 자신의 index에 해당하는 data를 불러 bind해야 함.
}

void UPerkNodeWidget::SaveSkill()
{
}


