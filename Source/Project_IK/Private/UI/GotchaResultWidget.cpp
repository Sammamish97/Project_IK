/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 1.3.2025
Summary : Source file for a user widget to display gotcha result.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "UI/GotchaResultWidget.h"

#include "Blueprint/WidgetTree.h"
#include "Components/GridPanel.h"
#include "Components/GridSlot.h"
#include "Components/Image.h"

#include "Animation/WidgetAnimation.h"

#include "UI/GotchaSlot.h"

void UGotchaResultWidget::DisplayResults(TArray<UTexture2D*> textures)
{
	SetVisibility(ESlateVisibility::Visible);
	UGridSlot* grid_slot = Cast<UGridSlot>(slots_[0]->Slot);
	grid_slot->SetNudge(FVector2D(0.f, 0.f));

	const int32 texture_num = FMath::Min(textures.Num(), MAX_IMAGE);
	for (int32 i = 0; i < texture_num; i++)
	{
		slots_[i]->SetImage(textures[i]);
	}

	// Hide unused slots
	for (int32 i = texture_num; i < MAX_IMAGE; i++)
	{
		slots_[i]->SetRenderOpacity(0.f);
	}

	StartAnimationSquence(texture_num);
}

void UGotchaResultWidget::DisplayResult(UTexture2D* texture)
{
	SetVisibility(ESlateVisibility::Visible);
	slots_[0]->SetImage(texture);
	slots_[0]->SetRenderOpacity(1.f);
	UGridSlot* grid_slot = Cast<UGridSlot>(slots_[0]->Slot);
	grid_slot->SetNudge(FVector2D(600.f, 150.f));

	// Hide unused slots
	for (int32 i = 1; i < MAX_IMAGE; i++)
	{
		slots_[i]->SetRenderOpacity(0.f);
	}

	StartAnimationSquence(1);
}

void UGotchaResultWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	for (int32 i = 0; i < MAX_IMAGE; i++)
	{
		UGotchaSlot* image = WidgetTree->ConstructWidget<UGotchaSlot>(gotcha_slot_class_);
		UGridSlot* grid_slot = image_containers_->AddChildToGrid(image);
		if (grid_slot)
		{
			grid_slot->SetPadding(FMargin(86));
			grid_slot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
			grid_slot->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);
			grid_slot->SetColumn(i % 5);
			grid_slot->SetRow(i / 5);
		}

		slots_.Add(image);
	}
	animation_max = MAX_IMAGE;
	current_animation_index_ = 0;
	is_running_ = false;

	SetVisibility(ESlateVisibility::Hidden);
}

void UGotchaResultWidget::NativeDestruct()
{
	OnResultFinished.Clear();
}

FReply UGotchaResultWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	// Mouse clicked when everythings done
	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton && !is_running_)
	{
		SetVisibility(ESlateVisibility::Hidden);

		for (int32 i = 0; i < MAX_IMAGE; i++)
		{
			slots_[i]->SetRenderOpacity(1.f);
			slots_[i]->ResetAnimationStatus();
		}

		OnResultFinished.Broadcast();

	}
	// Mouse clicked to skip gotcha animation
	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton && is_running_)
	{
		StopAllAnimations();
	}

	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}

void UGotchaResultWidget::ContinueAnimation()
{
	++current_animation_index_;
	PlayNextAnimation();
}

void UGotchaResultWidget::StartAnimationSquence(int32 animation_max_)
{
	animation_max = animation_max_;
	for (int32 i = 0; i < animation_max; i++)
	{
		slots_[i]->ResetAnimationStatus();
	}

	is_running_ = true;
	current_animation_index_ = 0;
	PlayNextAnimation();
}

void UGotchaResultWidget::PlayNextAnimation()
{
	if (current_animation_index_ >= animation_max)
	{
		is_running_ = false;
		return;
	}

	UWidgetAnimation* current_animation = slots_[current_animation_index_]->GetAnimation();
	if (current_animation)
	{
		slots_[current_animation_index_]->PlayAnimation(current_animation);

		float animation_duration = slots_[current_animation_index_]->GetAnimation()->GetEndTime();
		GetWorld()->GetTimerManager().SetTimer(
			animation_timer_handle_,
			this,
			&UGotchaResultWidget::ContinueAnimation,
			animation_duration,
			false
		);
	}
}

void UGotchaResultWidget::StopAllAnimations()
{
	GetWorld()->GetTimerManager().ClearTimer(animation_timer_handle_);
	is_running_ = false;
	
	for (int32 i = 0; i < MAX_IMAGE; i++)
	{
		slots_[i]->PlayAnimation(slots_[i]->GetAnimation(), slots_[i]->GetAnimation()->GetEndTime());
	}
}
