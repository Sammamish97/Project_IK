/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 10.04.2024
Summary : Source file for Skill Bar UI.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/



#include "UI/ButtonBarWidget.h"

#include "Kismet/GameplayStatics.h"

#include "Components/Button.h"
#include "WorldSettings/IKGameModeBase.h"
#include "Abilities/SkillContainer.h"
#include "Components/TargetingComponent.h"
#include "WorldSettings/IKPlayerController.h"
#include "Abilities/ItemInventory.h"
#include "Abilities/Item.h"
#include "WorldSettings/IKGameInstance.h"
#include "Managers/TextureManager.h"

#include "Characters/Unit.h"
#include "Components/CrowdControlComponent.h"
void UButtonBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	FindCharacters();

	// if (skill_button_0_)
	// {
	// 	skill_button_0_->OnClicked.AddDynamic(this, &UButtonBarWidget::OnSkillButtonClicked0);
	// }
	// if (skill_button_1_)
	// {
	// 	skill_button_1_->OnClicked.AddDynamic(this, &UButtonBarWidget::OnSkillButtonClicked1);
	// }
	// if (skill_button_2_)
	// {
	// 	skill_button_2_->OnClicked.AddDynamic(this, &UButtonBarWidget::OnSkillButtonClicked2);
	// }
	// if (skill_button_3_)
	// {
	// 	skill_button_3_->OnClicked.AddDynamic(this, &UButtonBarWidget::OnSkillButtonClicked3);
	// }

	if (item_button_0_)
	{
		item_button_0_->OnClicked.AddDynamic(this, &UButtonBarWidget::OnItemButtonClicked0);
	}
	if (item_button_1_)
	{
		item_button_1_->OnClicked.AddDynamic(this, &UButtonBarWidget::OnItemButtonClicked1);
	}
	if (item_button_2_)
	{
		item_button_2_->OnClicked.AddDynamic(this, &UButtonBarWidget::OnItemButtonClicked2);
	}

	if (AIKPlayerController* PC = Cast<AIKPlayerController>(GetOwningPlayer()))
	{
		targeting_component_ = PC->GetTargetingComponent();
		if (targeting_component_)
		{
			targeting_component_->OnTargetResultSelected.AddDynamic(this, &UButtonBarWidget::InvokeSkills);
		}
	}

	if (UIKGameInstance* GI = Cast<UIKGameInstance>(GetGameInstance()))
	{
		item_inventory_ = GI->GetItemInventory();

		empty_item_icon = GI->GetTextureManager()->GetTexture("empty_item_slot");
	}

	SynchroItemButtons();

	caster_ = -1;
	selected_item_index_ = -1;

	switch (characters_.Num())
	{
	case 0:
		skill_button_0_->SetVisibility(ESlateVisibility::Hidden);
	case 1:
		skill_button_1_->SetVisibility(ESlateVisibility::Hidden);
	case 2:
		skill_button_2_->SetVisibility(ESlateVisibility::Hidden);
	case 3:
		skill_button_3_->SetVisibility(ESlateVisibility::Hidden);
		break;
	default:
		break;
	}

	is_item_muted_ = false;
	
	
}

void UButtonBarWidget::NativeDestruct()
{
	if (skill_button_0_)
	{
		skill_button_0_->OnClicked.Clear();
	}
	if (skill_button_1_)
	{
		skill_button_1_->OnClicked.Clear();
	}
	if (skill_button_2_)
	{
		skill_button_2_->OnClicked.Clear();
	}
	if (skill_button_3_)
	{
		skill_button_3_->OnClicked.Clear();
	}

	if (item_button_0_)
	{
		item_button_0_->OnClicked.Clear();
	}
	if (item_button_1_)
	{
		item_button_1_->OnClicked.Clear();
	}
	if (item_button_2_)
	{
		item_button_2_->OnClicked.Clear();
	}
}

void UButtonBarWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	TArray<UButton*> buttons = { skill_button_0_, skill_button_1_, skill_button_2_, skill_button_3_ };
	for (int32 i = 0; i < buttons.Num(); ++i)
	{
		// Is the skill button connected in cooldown
		if (buttons[i]->GetVisibility() != ESlateVisibility::Hidden &&buttons[i]->GetIsEnabled() == false)
		{
			cooldowns_[i] += InDeltaTime;
			const float cooltime = skill_containers_[i]->GetCooltime();
			if (cooldowns_[i] >= cooltime)
			{
				buttons[i]->SetIsEnabled(true);
			}
			else
			{
				button_cooldown_materials_[i]->SetScalarParameterValue("CooldownPercent", cooldowns_[i] / cooltime);
			}
			
		}
	}
}
//
// void UButtonBarWidget::OnSkillButtonClicked0()
// {
// 	caster_ = 0;
// 	selected_item_index_ = -1;
//
// 	if (targeting_component_ && characters_.IsValidIndex(caster_))
// 	{
// 		targeting_component_->StartSkillTargeting(characters_[caster_], skill_containers_[caster_]->GetTargetParameters());
// 	}
// }
//
// void UButtonBarWidget::OnSkillButtonClicked1()
// {
// 	caster_ = 1;
// 	selected_item_index_ = -1;
//
// 	if (targeting_component_ && characters_.IsValidIndex(caster_))
// 	{
// 		targeting_component_->StartSkillTargeting(characters_[caster_], skill_containers_[caster_]->GetTargetParameters());
// 	}
// }
//
// void UButtonBarWidget::OnSkillButtonClicked2()
// {
// 	caster_ = 2;
// 	selected_item_index_ = -1;
//
// 	if (targeting_component_ && characters_.IsValidIndex(caster_))
// 	{
// 		targeting_component_->StartSkillTargeting(characters_[caster_], skill_containers_[caster_]->GetTargetParameters());
// 	}
// }
//
// void UButtonBarWidget::OnSkillButtonClicked3()
// {
// 	caster_ = 3;
// 	selected_item_index_ = -1;
//
// 	if (targeting_component_ && characters_.IsValidIndex(caster_))
// 	{
// 		targeting_component_->StartSkillTargeting(characters_[caster_], skill_containers_[caster_]->GetTargetParameters());
// 	}
// }

void UButtonBarWidget::OnItemButtonClicked0()
{
	if (item_inventory_->GetItem(0).IsValid() && !is_item_muted_)
	{
		caster_ = -1;
		selected_item_index_ = 0;
		targeting_component_->StartItemTargeting(item_inventory_->GetItem(0)->GetTargetParameters());
	}
}

void UButtonBarWidget::OnItemButtonClicked1()
{
	if (item_inventory_->GetItem(1).IsValid() && !is_item_muted_)
	{
		caster_ = -1;
		selected_item_index_ = 1;
		targeting_component_->StartItemTargeting(item_inventory_->GetItem(1)->GetTargetParameters());
	}
}

void UButtonBarWidget::OnItemButtonClicked2()
{
	if (item_inventory_->GetItem(2).IsValid() && !is_item_muted_)
	{
		caster_ = -1;
		selected_item_index_ = 2;
		targeting_component_->StartItemTargeting(item_inventory_->GetItem(2)->GetTargetParameters());
	}
}

void UButtonBarWidget::SynchroItemButtons()
{
	if (is_item_muted_)
	{
		// Do not synchro if muted.
		// CC component may synchro it after the effect has expired.
		return ;
	}

	FButtonStyle button_style;
	FSlateBrush normal_brush;
	normal_brush.DrawAs = ESlateBrushDrawType::Type::Image;
	normal_brush.SetImageSize(FVector2D(128.0, 128.0));
	normal_brush.TintColor = FSlateColor(FLinearColor(0.69f, 0.69f, 0.69f));
	FSlateBrush hovered_brush = normal_brush;
	hovered_brush.TintColor = FSlateColor(FLinearColor(0.95f, 0.95f, 0.95f));
	FSlateBrush pressed_brush = normal_brush;
	pressed_brush.TintColor = FSlateColor(FLinearColor(0.5f, 0.5f, 0.5f));
	FSlateBrush disabled_brush = pressed_brush;
	disabled_brush.SetResourceObject(empty_item_icon);

	button_style.SetDisabled(disabled_brush);

	if (item_inventory_->GetItem(0) != nullptr)
	{
		UTexture2D* item_icon = item_inventory_->GetItem(0)->GetData().item_icon_;
		normal_brush.SetResourceObject(item_icon);
		button_style.SetNormal(normal_brush);
		hovered_brush.SetResourceObject(item_icon);
		button_style.SetHovered(hovered_brush);
		pressed_brush.SetResourceObject(item_icon);
		button_style.SetPressed(pressed_brush);

		item_button_0_->SetIsEnabled(true);
		item_button_0_->SetStyle(button_style);
	}
	else
	{
		item_button_0_->SetIsEnabled(false);
		item_button_0_->SetStyle(button_style);
	}
	if (item_inventory_->GetItem(1) != nullptr)
	{
		UTexture2D* item_icon = item_inventory_->GetItem(1)->GetData().item_icon_;
		normal_brush.SetResourceObject(item_icon);
		button_style.SetNormal(normal_brush);
		hovered_brush.SetResourceObject(item_icon);
		button_style.SetHovered(hovered_brush);
		pressed_brush.SetResourceObject(item_icon);
		button_style.SetPressed(pressed_brush);

		item_button_1_->SetStyle(button_style);
		item_button_1_->SetIsEnabled(true);
	}
	else
	{
		item_button_1_->SetIsEnabled(false);
		item_button_1_->SetStyle(button_style);
	}
	if (item_inventory_->GetItem(2) != nullptr)
	{
		UTexture2D* item_icon = item_inventory_->GetItem(2)->GetData().item_icon_;
		normal_brush.SetResourceObject(item_icon);
		button_style.SetNormal(normal_brush);
		hovered_brush.SetResourceObject(item_icon);
		button_style.SetHovered(hovered_brush);
		pressed_brush.SetResourceObject(item_icon);
		button_style.SetPressed(pressed_brush);

		item_button_2_->SetIsEnabled(true);
		item_button_2_->SetStyle(button_style);
	}
	else
	{
		item_button_2_->SetIsEnabled(false);
		item_button_2_->SetStyle(button_style);
	}
}

void UButtonBarWidget::SilenceSkill(AActor* character)
{
	// Disable a button
	for(int32 i = 0; i < characters_.Num(); ++i)
	{
		if (characters_[i] == character)
		{
			switch (i)
			{
			case 0:
				skill_button_0_->SetIsEnabled(false);
				break;
			case 1:
				skill_button_1_->SetIsEnabled(false);
				break;
			case 2:
				skill_button_2_->SetIsEnabled(false);
				break;
			case 3:
				skill_button_3_->SetIsEnabled(false);
				break;
			default:
				break;
			}

			break;
		}
	}
	// Cancel targeting if invoker is the character
	targeting_component_->StopTargetingIfInvokerIs(character);
}

void UButtonBarWidget::UnsilenceSkill(AActor* character)
{
	// Enable a button
	// Disable a button
	for (int32 i = 0; i < characters_.Num(); ++i)
	{
		if (characters_[i] == character)
		{
			switch (i)
			{
			case 0:
				skill_button_0_->SetIsEnabled(true);
				break;
			case 1:
				skill_button_1_->SetIsEnabled(true);
				break;
			case 2:
				skill_button_2_->SetIsEnabled(true);
				break;
			case 3:
				skill_button_3_->SetIsEnabled(true);
				break;
			default:
				break;
			}

			break;
		}
	}
}

void UButtonBarWidget::MuteItems()
{
	is_item_muted_ = true;

	// Disable item buttons
	item_button_0_->SetIsEnabled(false);
	item_button_1_->SetIsEnabled(false);
	item_button_2_->SetIsEnabled(false);
	
	// Cancel if user is targeting by item
	targeting_component_->StopItemTargeting();
}

void UButtonBarWidget::UnmuteItems()
{
	is_item_muted_ = false;
	SynchroItemButtons();
}

void UButtonBarWidget::InvokeSkills(const FTargetResult& TargetResult)
{
	if (caster_ < 0)
	{
		item_inventory_->GetItem(selected_item_index_)->UseItem(GetWorld(), TargetResult);
		item_inventory_->RemoveItem(selected_item_index_);

		SynchroItemButtons();
	}
	else
	{
		skill_containers_[caster_]->InvokeSkills(TargetResult);
		switch (caster_)
		{
		case 0:
			skill_button_0_->SetIsEnabled(false);
			break;
		case 1:
			skill_button_1_->SetIsEnabled(false);
			break;
		case 2:
			skill_button_2_->SetIsEnabled(false);
			break;
		case 3:
			skill_button_3_->SetIsEnabled(false);
			break;
		default:
			break;
		}
		cooldowns_[caster_] = 0.f;
		button_cooldown_materials_[caster_]->SetScalarParameterValue("CooldownPercent", cooldowns_[caster_]);
	}
}

void UButtonBarWidget::FindCharacters()
{
	skill_containers_.Empty();

	AIKGameModeBase* game_mode = Cast<AIKGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	TArray<UButton*> temp_array = {skill_button_0_, skill_button_1_, skill_button_2_, skill_button_3_};
	button_cooldown_materials_.Empty();
	button_cooldown_materials_.SetNum(temp_array.Num());
	cooldowns_.SetNum(temp_array.Num());

	if (game_mode)
	{
		characters_ = game_mode->GetHeroContainers();

		for (int32 i = 0; i < characters_.Num(); ++i)
		{

			if (characters_[i])
			{
				if (auto skill_container = characters_[i]->FindComponentByClass<USkillContainer>())
				{
					skill_containers_.Add(skill_container);
					FButtonStyle button_style = temp_array[i]->GetStyle();
					UTexture2D* image = skill_container->GetEquippedActiveSkillData().thumbnail;
					button_style.Normal.SetResourceObject(image);
					button_style.Pressed.SetResourceObject(image);
					button_style.Hovered.SetResourceObject(image);
					UObject* tmp = button_style.Disabled.GetResourceObject();
					if (tmp && tmp->IsA<UMaterialInterface>())
					{
						UMaterialInterface* material = Cast<UMaterialInterface>(tmp);
						if (material)
						{
							button_cooldown_materials_[i] = UMaterialInstanceDynamic::Create(material, this);
							button_cooldown_materials_[i]->SetTextureParameterValue("Texture", image);
							cooldowns_[i] = 0.f;
							button_cooldown_materials_[i]->SetScalarParameterValue("CooldownPercent", cooldowns_[i]);
							button_cooldown_materials_[i]->SetVectorParameterValue("Tint",
								button_style.Normal.TintColor.GetSpecifiedColor());
							button_style.Disabled.SetResourceObject(button_cooldown_materials_[i]);
						}
					}
					temp_array[i]->SetStyle(button_style);
				}
			}
		}
	}
}

