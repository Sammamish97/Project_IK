/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 1.3.2025
Summary : Source file of user widget class to gotcha.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "UI/GotchaWidget.h"

#include "Kismet/GameplayStatics.h"

#include "WorldSettings/IKGameInstance.h"
#include "Managers/DataTableManager.h"
#include "Managers/InventoryManager.h"
#include "Subsystems/PerkModifierSubsystem.h"
#include "Subsystems/LevelTransitionSubsystem.h"

#include "Blueprint/WidgetTree.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "UI/GotchaResultWidget.h"

void UGotchaWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (end_gotcha_button_)
	{
		end_gotcha_button_->OnClicked.AddDynamic(this, &UGotchaWidget::EndGotchaButtonPressed);
	}
	if (pull_one_button_)
	{
		pull_one_button_->OnClicked.AddDynamic(this, &UGotchaWidget::PullOne);
	}
	if (pull_ten_button_)
	{
		pull_ten_button_->OnClicked.AddDynamic(this, &UGotchaWidget::PullTen);
	}
	if (result_widget_class_)
	{
		result_widget_ = WidgetTree->ConstructWidget<UGotchaResultWidget>(result_widget_class_);
		result_widget_->AddToViewport(1);
		result_widget_->OnResultFinished.AddDynamic(this, &UGotchaWidget::StorePulledData);
	}

	num_max_pull_ = GetGameInstance()->GetSubsystem<UPerkModifierSubsystem>()->GetNumMaxPull();

	UpdateGotchaTicketCount();

	ClearContainers();
}

void UGotchaWidget::NativeDestruct()
{
	if (end_gotcha_button_)
	{
		end_gotcha_button_->OnClicked.Clear();
	}
	if (pull_one_button_)
	{
		pull_one_button_->OnClicked.Clear();
	}
	if (pull_ten_button_)
	{
		pull_ten_button_->OnClicked.Clear();
	}
}

void UGotchaWidget::EndGotchaButtonPressed()
{
	GetGameInstance()->GetSubsystem<ULevelTransitionSubsystem>()->OpenMapLevel(GetWorld());
}

void UGotchaWidget::PullOne()
{
	if (num_max_pull_ < 1)
	{
		return;
	}

	SetTickets(num_max_pull_ - 1);
	Gotcha(1);
}

void UGotchaWidget::PullTen()
{
	if (num_max_pull_ <= 0)
	{
		return;
	}
	int32 pull_num = num_max_pull_ % 10;
	SetTickets(num_max_pull_ - pull_num);
	Gotcha(pull_num);
}

void UGotchaWidget::SetTickets(int32 tickets)
{
	num_max_pull_ = tickets;
	UpdateGotchaTicketCount();
}

void UGotchaWidget::UpdateGotchaTicketCount()
{
	tickets_count_text_->SetText(FText::AsNumber(num_max_pull_));
}

void UGotchaWidget::Gotcha(int32 pulls)
{
	ClearContainers();

	UIKGameInstance* game_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	const UDataTableManager* data_table_manager = game_instance->GetDataTableManager();

	TArray<UTexture2D*> textures;
	for (int32 i = 0; i < pulls; i++)
	{
		int32 probability = FMath::RandRange(0, 99);
		if (probability <= 19)
		{
			textures.Add(credits_texture_);
			pulled_credits_ += 20;
		}
		else
		{	// Add equipment texture
			FWrapperEquipmentData pulled_data = data_table_manager->GetEquipmentDataRandomly();
			if (!pulled_data.weapons_.IsEmpty())
			{
				textures.Add(pulled_data.weapons_[0].item_data_.display_data_->thumbnail);
			}
			else if (!pulled_data.active_skills_.IsEmpty())
			{
				textures.Add(pulled_data.active_skills_[0].item_data_.display_data_->thumbnail);
			}
			else if (!pulled_data.passive_skills_.IsEmpty())
			{
				textures.Add(pulled_data.passive_skills_[0].item_data_.display_data_->thumbnail);
			}
			else
			{
				textures.Add(pulled_data.runes_[0].item_data_.display_data_->thumbnail);
			}
			pulled_equipments_ += pulled_data;
		}
	}
	if (pulls <= 1)
	{
		result_widget_->DisplayResult(textures[0]);
	}
	else
	{
		result_widget_->DisplayResults(textures);
	}
}

void UGotchaWidget::ClearContainers()
{
	pulled_credits_ = 0;
	pulled_equipments_ = FWrapperEquipmentData();
}

void UGotchaWidget::StorePulledData()
{
	UIKGameInstance* game_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	UInventoryManager* inventory_manager = game_instance->GetInventoryManager();
	inventory_manager->SetCredits(inventory_manager->GetCredits() + pulled_credits_);
}
