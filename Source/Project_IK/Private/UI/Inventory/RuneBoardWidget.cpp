/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 3.10.2025
Summary : Source file for Rune Slot widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "UI/Inventory/RuneBoardWidget.h"

#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"
#include "Kismet/GameplayStatics.h"
#include "Structs/SpawnData.h"
#include "UI/InventorySlots/RuneSlotWidget.h"
#include "Components/ProgressBar.h"
#include "Components/SizeBox.h"
#include "WorldSettings/IKGameInstance.h"
#include "Subsystems/LevelTransitionSubsystem.h"
#include "Managers/SetBonusManager.h"
#include "UI/Inventory/RuneBoardEdgeWidget.h"

void URuneBoardWidget::NativeConstruct()
{
	Super::NativeConstruct();
	TArray rune_slots = {slot_0_, slot_1_, slot_2_, slot_3_, slot_4_, slot_5_};
	float r = 300;

	auto vertices = ComputeVertices(r);
	auto edges = ComputeEdges(vertices);

	for(int32 i = 0; i < 6; ++i)
	{
		//Left -> Top -> Right -> Bottom
		FMargin margin = {vertices[i].X, 0, 0,  vertices[i].Y};
		UOverlaySlot* rune_slot = CastChecked<UOverlaySlot>(rune_overlay_->GetSlots()[i]);
		rune_slot->SetPadding(margin);
	}
	
	TArray line_array = {line_0_, line_1_, line_2_, line_3_, line_4_, line_5_, line_6_, line_7_, line_8_, line_9_, line_10_, line_11_};
	TArray<UOverlaySlot*> line_slots;
	for(int32 i = 0; i < 12; ++i)
	{
		line_slots.Push(CastChecked<UOverlaySlot>(line_overlay_->GetSlots()[i]));
	}
	float temp_height = 2.f;

	TArray idx_map = {0, 4, 7, 9, 11, 3, 1, 8, 2, 5, 10, 6};
	for(int32 i = 0; i < 12; ++i)
	{
		line_slots[i]->SetPadding({edges[idx_map[i]].mid_point.X, 0, 0, edges[idx_map[i]].mid_point.Y});
		line_array[i]->size_box_->SetRenderTransformAngle(FMath::RadiansToDegrees(edges[idx_map[i]].angle));
		line_array[i]->size_box_->SetWidthOverride(edges[idx_map[i]].length);
		line_array[i]->size_box_->SetHeightOverride(temp_height);
		line_array[i]->SetVisibility(ESlateVisibility::Hidden);
	}
}

void URuneBoardWidget::SetInventoryWidget(UInventoryWidget* widget_ptr)
{
	TArray rune_slots = {slot_0_, slot_1_, slot_2_, slot_3_, slot_4_, slot_5_};
	for (auto elem : rune_slots)
	{
		elem->InitInventorySlot(widget_ptr);
	}
}

TArray<FVector2D> URuneBoardWidget::ComputeVertices(float radius)
{
	TArray<FVector2D> result;
	for (int32 i = 0; i < 6; ++i) {
		float angle = 2 * PI * i / 6;
		result.Push({radius * FMath::Sin(angle), radius * FMath::Cos(angle)});
	}
	return result;
}

TArray<URuneBoardWidget::Edge> URuneBoardWidget::ComputeEdges(const TArray<FVector2D>& vertices)
{
	TArray<Edge> result;
	for (int32 i = 0; i < 6; ++i) {
		for (int32 j = i + 1; j < 6; ++j) {
			// Skip same vertex and opposite vertex
			if (j == (i + 3) % 6) continue;

			FVector2D p1 = vertices[i];
			FVector2D p2 = vertices[j];

			// Midpoint
			FVector2D mid = { (p1.X + p2.X) / 2.0f, (p1.Y + p2.Y) / 2.0f };

			// Length
			float dx = p2.X - p1.X;
			float dy = p2.Y - p1.Y;
			float len = FMath::Sqrt(dx * dx + dy * dy);

			// Angle (radians)
			float angle = FMath::Atan2(dy, dx);
			angle *= -1;

			result.Push({ mid, len, angle });
		}
	}
	return result;
}

void URuneBoardWidget::LoadRuneBoardWidget()
{
	TObjectPtr<UIKGameInstance> ik_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	TObjectPtr<ULevelTransitionSubsystem> transition_system = ik_instance->GetLevelTransitionSubsystem();
	const auto& spawn_map = transition_system->GetSpawnData();
	for(const auto& elem : spawn_map)
	{
		if(elem.Value.is_dead_ == false)
		{
			LoadRuneBoardWidget(elem.Key);
			break;
		}
	}
}

void URuneBoardWidget::LoadRuneBoardWidget(EHeroType hero_type)
{
	cur_hero_type_ = hero_type;
	
	TObjectPtr<UIKGameInstance> ik_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	TObjectPtr<ULevelTransitionSubsystem> transition_system = ik_instance->GetLevelTransitionSubsystem();
	TArray rune_slots = {slot_0_, slot_1_, slot_2_, slot_3_, slot_4_, slot_5_};
	for (int32 i = 0; i < 6; ++i)
	{
		rune_slots[i]->ClearData();
	}
	
	if(transition_system->GetSpawnData().IsEmpty() == false)
	{
		FSpawnData data_cache = transition_system->GetSpawnData(cur_hero_type_);
		
		TArray rune_data_array = {data_cache.rune_data_1, data_cache.rune_data_2, data_cache.rune_data_3, data_cache.rune_data_4, data_cache.rune_data_5, data_cache.rune_data_6};
		TArray rune_slot_type_array = {EInventorySlotType::Rune_0, EInventorySlotType::Rune_1, EInventorySlotType::Rune_2, EInventorySlotType::Rune_3, EInventorySlotType::Rune_4, EInventorySlotType::Rune_5};
		for (int32 i = 0; i < rune_data_array.Num(); i++)
		{
			if (rune_data_array[i].IsSet())
			{
				rune_slots[i]->SetRuneSetSlotData(rune_data_array[i].GetValue());
			}
			else
			{
				rune_slots[i]->SetRuneSetSlotData(rune_slot_type_array[i]);
			}
		}
	}
}

void URuneBoardWidget::UpdateRuneBoard()
{
	if (cur_hero_type_ != EHeroType::INVALID)
	{
		TObjectPtr<UIKGameInstance> ik_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		TObjectPtr<ULevelTransitionSubsystem> transition_system = ik_instance->GetLevelTransitionSubsystem();
		TArray rune_slots = {slot_0_, slot_1_, slot_2_, slot_3_, slot_4_, slot_5_};

		if(transition_system->GetSpawnData().IsEmpty() == false)
		{
			FSpawnData data_cache = transition_system->GetSpawnData(cur_hero_type_);
			TArray rune_data_array = {data_cache.rune_data_1, data_cache.rune_data_2, data_cache.rune_data_3, data_cache.rune_data_4, data_cache.rune_data_5, data_cache.rune_data_6};

			for (int32 i = 0; i < rune_data_array.Num(); i++)
			{
				if (rune_slots[i]->IsEmpty())
				{
					rune_data_array[i].Reset();
				}
				else
				{
					rune_data_array[i] = rune_slots[i]->GetStoredRuneData();
				}
			}
		
			data_cache.rune_data_1 = rune_data_array[0];
			data_cache.rune_data_2 = rune_data_array[1];
			data_cache.rune_data_3 = rune_data_array[2];
			data_cache.rune_data_4 = rune_data_array[3];
			data_cache.rune_data_5 = rune_data_array[4];
			data_cache.rune_data_6 = rune_data_array[5];
		
			transition_system->UpdateSpawnDataIdx(cur_hero_type_, data_cache);
		}	
	}
}

void URuneBoardWidget::ClearSetBonusEffect()
{
	TArray lines = {line_0_, line_1_, line_2_, line_3_, line_4_, line_5_, line_6_, line_7_, line_8_, line_9_, line_10_, line_11_};
	for (auto& elem : lines)
	{
		elem->SetVisibility(ESlateVisibility::Hidden);
	}
}

void URuneBoardWidget::UpdateSetBonusEffect()
{
	ClearSetBonusEffect();
	
	TArray rune_slots = {slot_0_, slot_1_, slot_2_, slot_3_, slot_4_, slot_5_};
	TArray lines = {line_0_, line_1_, line_2_, line_3_, line_4_, line_5_, line_6_, line_7_, line_8_, line_9_, line_10_, line_11_};

	TObjectPtr<UIKGameInstance> ik_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	TObjectPtr<USetBonusManager> set_bonus_cache = ik_instance->GetSetBonusManager();
	
	TArray<FRuneData> data_array;
	for (int i = 0; i < 6; ++i)
	{
		if (rune_slots[i]->IsEmpty())
		{
			data_array.Add(FRuneData());
		}
		else
		{
			data_array.Add(rune_slots[i]->GetStoredRuneData());
		}
	}
	auto result = set_bonus_cache->FigureOutRuneSet(data_array);
	for (const auto& elem : result)
	{
		if (elem.Value.Num() == 2)
		{
			lines[elem.Value[0]]->SetVisibility(ESlateVisibility::Visible);
		}
		else if (elem.Value.Num() == 3)
		{
				lines[6 + 3 * elem.Value[0]]->SetVisibility(ESlateVisibility::Visible);
				lines[7 + 3 * elem.Value[0]]->SetVisibility(ESlateVisibility::Visible);
				lines[8 + 3 * elem.Value[0]]->SetVisibility(ESlateVisibility::Visible);
		}
		else if (elem.Value.Num() == 6)
		{
			for (int i = 0; i < 6; ++i)
			{
				lines[i]->SetVisibility(ESlateVisibility::Visible);
			}
		}
	}
}

TObjectPtr<URuneSlotWidget> URuneBoardWidget::GetRuneSlotWidget(int32 idx)
{
	switch (idx)
	{
		case 0:
			return slot_0_;
		case 1:
			return slot_1_;
		case 2:
			return slot_2_;
		case 3:
			return slot_3_;
		case 4:
			return slot_4_;
		case 5:
			return slot_5_;
		default:
			return nullptr;
	}
}

void URuneBoardWidget::ToggleReadOnly(bool is_read_only)
{
	TArray rune_slots = {slot_0_, slot_1_, slot_2_, slot_3_, slot_4_, slot_5_};
	for (const auto& elem : rune_slots)
	{
		elem->SetIsReadOnly(is_read_only);
	}
}
