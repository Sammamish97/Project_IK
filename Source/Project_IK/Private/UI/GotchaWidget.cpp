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

#include "Blueprint/WidgetTree.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "UI/GotchaResultWidget.h"

void UGotchaWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (back_space_)
	{
		back_space_->OnClicked.AddDynamic(this, &UGotchaWidget::BackSpace);
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

	UIKGameInstance* game_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	tickets_ = game_instance->GetInventoryManager()->GetTickets();

	UpdateGotchaTicketCount();

	ClearContainers();
}

void UGotchaWidget::NativeDestruct()
{
	if (back_space_)
	{
		back_space_->OnClicked.Clear();
	}
	if (pull_one_button_)
	{
		pull_one_button_->OnClicked.Clear();
	}
	if (pull_ten_button_)
	{
		pull_ten_button_->OnClicked.Clear();
	}

	UIKGameInstance* game_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (game_instance)
	{
		game_instance->GetInventoryManager()->SetTickets(tickets_);
	}
}

void UGotchaWidget::BackSpace()
{
	// @@ TODO: Go to proper level
	// UGameplayStatics::OpenLevel(GetWorld(), FName("CombatLevel"));
}

void UGotchaWidget::PullOne()
{
	if (tickets_ < 1)
	{
		return;
	}

	SetTickets(tickets_ - 1);
	Gotcha(1);
}

void UGotchaWidget::PullTen()
{
	if (tickets_ < 10)
	{
		return;
	}
	SetTickets(tickets_ - 10);
	Gotcha(10);
}

void UGotchaWidget::SetTickets(int32 tickets)
{
	tickets_ = tickets;
	UpdateGotchaTicketCount();
}

void UGotchaWidget::UpdateGotchaTicketCount()
{
	tickets_count_text_->SetText(FText::AsNumber(tickets_));
}

void UGotchaWidget::Gotcha(int32 pulls)
{
	ClearContainers();

	UIKGameInstance* game_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	const UDataTableManager* data_table_manager = game_instance->GetDataTableManager();

	TArray<UTexture2D*> textures;
	// @@ TODO: Expand it from only item to item, DP, manuals, money
	for (int32 i = 0; i < pulls; i++)
	{
		//int32 tmp = FMath::RandRange(0, 2);
		//switch (tmp)
		//{
		//default:
		//	textures.Add(credits_texture_);
		//	pulled_credits_ += 20;
		//	break;
		//}

		// Rewarded credits only.
		textures.Add(credits_texture_);
		pulled_credits_ += 20;
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
}

void UGotchaWidget::StorePulledData()
{
	UIKGameInstance* game_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	UInventoryManager* inventory_manager = game_instance->GetInventoryManager();
	inventory_manager->SetCredits(inventory_manager->GetCredits() + pulled_credits_);
}
