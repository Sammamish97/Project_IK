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
#include "Components/TextBlock.h"

#include "WorldSettings/IKGameModeBase.h"
#include "WorldSettings/IKPlayerController.h"
#include "WorldSettings/IKGameInstance.h"

#include "Abilities/SkillContainer.h"

#include "Subsystems/DelegateBridgeSubsystem.h"

void UButtonBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	FindCharacters();
	
	if (skill_button_0_)
	{
		skill_button_0_->OnClicked.AddDynamic(this, &UButtonBarWidget::OnSkillButtonClicked0);
	}
	if (skill_button_1_)
	{
		skill_button_1_->OnClicked.AddDynamic(this, &UButtonBarWidget::OnSkillButtonClicked1);
	}
	if (skill_button_2_)
	{
		skill_button_2_->OnClicked.AddDynamic(this, &UButtonBarWidget::OnSkillButtonClicked2);
	}
	if (skill_button_3_)
	{
		skill_button_3_->OnClicked.AddDynamic(this, &UButtonBarWidget::OnSkillButtonClicked3);
	}

	player_controller_cache_ = Cast<AIKPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	UDelegateBridgeSubsystem* delegate_bridge_subsystem = GetWorld()->GetSubsystem<UDelegateBridgeSubsystem>();
	if (delegate_bridge_subsystem)
	{
		delegate_bridge_subsystem->BindOnItemUsed(this, &UButtonBarWidget::SynchroItemButtons);
		delegate_bridge_subsystem->BindOnActiveSkill(this, &UButtonBarWidget::SynchroActiveSkillButtons);
	}

	for (int32 i = 0; i < 3; ++i)
	{
		SynchroItemButtons(i);
	}

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
			if (skill_containers_[i].IsValid())
			{
				float left_cooldown = skill_containers_[i]->GetLeftCoolDown();
				if (left_cooldown <= 0.f)
				{
					buttons[i]->SetIsEnabled(true);
				}
				else
				{
					const float cooltime = skill_containers_[i]->GetCooltime();
					button_cooldown_materials_[i]->SetScalarParameterValue("CooldownPercent", 1.f - (left_cooldown / cooltime));
				}
			}
		}
	}
	repositioning_point_->SetText(FText::AsNumber(player_controller_cache_->GetChargeTime()));
}

void UButtonBarWidget::OnSkillButtonClicked0()
{
	ActivateSkillTargeting(EHeroType::Hero1);
}

void UButtonBarWidget::OnSkillButtonClicked1()
{
	ActivateSkillTargeting(EHeroType::Hero2);
}

void UButtonBarWidget::OnSkillButtonClicked2()
{
	ActivateSkillTargeting(EHeroType::Hero3);
}

void UButtonBarWidget::OnSkillButtonClicked3()
{
	ActivateSkillTargeting(EHeroType::Hero4);
}

void UButtonBarWidget::ActivateSkillTargeting(EHeroType caster)
{
	player_controller_cache_->ActivateSkillTargeting(caster);
}

void UButtonBarWidget::SynchroItemButtons(int32 item_idx)
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
}

void UButtonBarWidget::SynchroActiveSkillButtons(EHeroType hero_type)
{
	switch (hero_type)
	{
	case EHeroType::Hero1:
		skill_button_0_->SetIsEnabled(false);
		break;
	case EHeroType::Hero2:
		skill_button_1_->SetIsEnabled(false);
		break;
	case EHeroType::Hero3:
		skill_button_2_->SetIsEnabled(false);
		break;
	case EHeroType::Hero4:
		skill_button_3_->SetIsEnabled(false);
		break;
	case EHeroType::INVALID:
	default:
		//IKTODO: 예외처리 넣기 좋은 자리.
		break;
	}
	int32 hero_idx = HeroTypeToInt(hero_type);
	button_cooldown_materials_[hero_idx]->SetScalarParameterValue("CooldownPercent", 0.f);
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
	//IKTODO: 침묵 될 시, 다른 위치에서 아래의 코드를 발동 시켜야함.
	//targeting_component_cache_->StopTargetingIfInvokerIs(character);
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

void UButtonBarWidget::FindCharacters()
{
	skill_containers_.Empty();

	AIKGameModeBase* game_mode = Cast<AIKGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	TArray<UButton*> temp_array = {skill_button_0_, skill_button_1_, skill_button_2_, skill_button_3_};
	button_cooldown_materials_.Empty();
	button_cooldown_materials_.SetNum(temp_array.Num());

	if (game_mode)
	{
		characters_ = game_mode->GetHeroContainer();

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
							button_cooldown_materials_[i]->SetScalarParameterValue("CooldownPercent", 0.f);
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

