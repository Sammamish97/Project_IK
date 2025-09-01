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
#include "UI/PerkTrees/PerkConnectionWidget.h"
#include "UI/PerkTrees/PerkHUDWidget.h"
#include "Subsystems/PerkProgressSubsystem.h"
#include "WorldSettings/PerkUnlockLevel/IKPerkUnlockHUD.h"

void UPerkNodeWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	SetAlignment();
	FTimerDelegate timerDelegate = FTimerDelegate::CreateUObject(this, &UPerkNodeWidget::ConnectPerkNodes);
	GetWorld()->GetTimerManager().SetTimerForNextTick(timerDelegate);
}

void UPerkNodeWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (progress_system_cache_ == nullptr)
	{
		progress_system_cache_ = GetGameInstance()->GetSubsystem<UPerkProgressSubsystem>();
	}

	perk_detail_ = progress_system_cache_->LoadPerkDetails( FName(perk_detail_.key_));
	
	button_->OnPressed.AddDynamic(this, &UPerkNodeWidget::OnButtonPressed);
	button_->OnReleased.AddDynamic(this, &UPerkNodeWidget::OnButtonReleased);
	button_->OnHovered.AddDynamic(this, &UPerkNodeWidget::OnButtonHovered);
	button_->OnUnhovered.AddDynamic(this, &UPerkNodeWidget::OnButtonUnhovered);
}

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
	SaveSkill();
	for (const auto& elem: GetConnectedSkills())
	{
		elem->UnlockSkill();
	}
}

bool UPerkNodeWidget::CanPurchase()
{
	//IKTODO: 어딘가에서 cost를 받아와야 함.
	//int32 cur_point = save_ref_->LoadPerkPoint();
	int32 cur_point = 5;
	return perk_detail_.cost_ < cur_point &&
		perk_detail_.purchased_ == false &&
		perk_detail_.locked_ == false;
}

void UPerkNodeWidget::RemoveSkillPoint(int32 amount)
{
	int32 left_point = progress_system_cache_->LoadPerkPoint();
	progress_system_cache_->SavePerkPoint(left_point - amount);
	
	auto hud = Cast<AIKPerkUnlockHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());
	hud->GetPerkHUDWidget()->SetPerkPointText();
	
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
	timer_ = UKismetMathLibrary::FInterpTo_Constant(timer_,
			UKismetMathLibrary::SelectFloat(duration, 0, button_->IsPressed() && CanPurchase()),
			UGameplayStatics::GetWorldDeltaSeconds(GetWorld()),
			1.0f);
	if (timer_ == duration)
	{
		PurchaseSkill();
		return FLinearColor();
	}
	return UKismetMathLibrary::LinearColorLerp(FLinearColor::White, purchased_color_, timer_/duration);
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
	return UWidgetBlueprintLibrary::MakeBrushFromTexture(perk_detail_.thumbnail_, 60, 60);
}

ESlateVisibility UPerkNodeWidget::SetCheckVisibility()
{
	if (perk_detail_.purchased_)
	{
		return ESlateVisibility::HitTestInvisible;
	}
	return ESlateVisibility::Collapsed;
}

void UPerkNodeWidget::SaveSkill()
{
	FString string_name = perk_detail_.key_;
	FName name = FName(*string_name);
	progress_system_cache_->SavePerkDetails(name, perk_detail_);
}

void UPerkNodeWidget::OnButtonPressed()
{
	if (CanPurchase())
	{
		if (skill_connection_overlay_->HasAnyChildren())
		{
			for (const auto& elem : skill_connection_overlay_->GetAllChildren())
			{
				Cast<UPerkConnectionWidget>(elem)->SetLineConnectionTarget(true);
			}
		}
	}
}

void UPerkNodeWidget::OnButtonReleased()
{
	if (CanPurchase())
	{
		if (skill_connection_overlay_->HasAnyChildren())
		{
			for (const auto& elem : skill_connection_overlay_->GetAllChildren())
			{
				Cast<UPerkConnectionWidget>(elem)->SetLineConnectionTarget(false);
			}
		}
	}
}

void UPerkNodeWidget::OnButtonHovered()
{
	auto hud = Cast<AIKPerkUnlockHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());
	hud->GetPerkHUDWidget()->SetPopupDetail(perk_detail_);
}

void UPerkNodeWidget::OnButtonUnhovered()
{
	auto hud = Cast<AIKPerkUnlockHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());
	hud->GetPerkHUDWidget()->SetPopupDetail(FPerkNodeDetail());
}