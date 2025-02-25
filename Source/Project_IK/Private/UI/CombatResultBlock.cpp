/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 11.17.2024
Summary : Source file for Combat Result block class.
						It is an attachment for CombatResultUI. It is not be used itself alone.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "UI/CombatResultBlock.h"

#include "Blueprint/WidgetTree.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Components/Image.h"
#include "Components/Spacer.h"
#include "Components/SizeBox.h"
#include "Components/ProgressBar.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/TextBlock.h"

#include "Kismet/GameplayStatics.h"
#include "WorldSettings/IKGameInstance.h"
#include "Managers/TextureManager.h"

void UCombatResultBlock::SetHPPercent(float ratio)
{
	// @@ TODO: Make it function
	// 10% Red, 90% Green
	hp_->SetPercent(ratio);
	ratio -= 0.5f;
	ratio *= 5.f / 4.f;
	ratio = FMath::Clamp(ratio, -0.5f, 0.5f);
	ratio += 0.5f;

	FLinearColor hp_color = FMath::Lerp(FLinearColor(1.f, 0.f, 0.f), FLinearColor(0.f, 1.f, 0.f), ratio);
	hp_->SetFillColorAndOpacity(hp_color);
}

float UCombatResultBlock::GetHPPercent()
{
	return hp_->GetPercent();
}

void UCombatResultBlock::SetHPOpacity(float opacity)
{
	hp_->SetRenderOpacity(opacity);
}

void UCombatResultBlock::SetDamageDealt(float damage)
{
	deal_text_->SetText(FText::AsNumber(damage));
}

void UCombatResultBlock::NativeConstruct()
{
	Super::NativeConstruct();

	hp_->SetFillColorAndOpacity(FLinearColor(1.f, 0.f, 0.f));
}

//void UCombatResultBlock::InitializeChildWidgets()
//{
//	UIKGameInstance* game_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
//	if (!game_instance)
//	{
//		return;
//	}
//	const UTextureManager* texture_manager = game_instance->GetTextureManager();
//
//	// Init a portrait image component
//	hero_portrait_ = NewObject<UImage>();
//	FString hero_portrait_unique_name = MakeUniqueObjectName(GetOuter(), hero_portrait_->GetClass(), TEXT("Hero portrait")).ToString();
//	hero_portrait_->Rename(*hero_portrait_unique_name);
//	// @@ TODO: Change portraits by targeted hero not using default.
//	UTexture2D* hero_portrait_texture = texture_manager->GetTexture("default_portrait");
//	if (!hero_portrait_texture)
//	{
//		UE_LOG(LogTemp, Error, TEXT("Loading hero portrait image in CombatResultBlock has failed!"));
//		return;
//	}
//	FSlateBrush hero_portrait_brush;
//	hero_portrait_brush.SetResourceObject(hero_portrait_texture);
//	hero_portrait_brush.SetImageSize(FVector2D(256, 256));
//	hero_portrait_->SetBrush(hero_portrait_brush);
//	root_vertical_box_->AddChildToVerticalBox(hero_portrait_.Get());
//
//	spacer_hero_hp_ = NewObject<USpacer>();
//	FString spacer_hero_hp_unique_name = MakeUniqueObjectName(GetOuter(), spacer_hero_hp_->GetClass(), TEXT("Spacer b/w hero&hp")).ToString();
//	spacer_hero_hp_->Rename(*spacer_hero_hp_unique_name);
//	spacer_hero_hp_->SetSize(FVector2D(1.0, 20.0));
//	root_vertical_box_->AddChildToVerticalBox(spacer_hero_hp_.Get());
//
//	// Init HP using a progress bar component
//	hp_holder_ = NewObject<USizeBox>();
//	FString hp_holder_unique_name = MakeUniqueObjectName(GetOuter(), hp_holder_->GetClass(), TEXT("HP holder")).ToString();
//	hp_holder_->Rename(*hp_holder_unique_name);
//	hp_holder_->SetHeightOverride(28.f);
//	UVerticalBoxSlot* hp_holder_slot = root_vertical_box_->AddChildToVerticalBox(hp_holder_.Get());
//	if (hp_holder_slot)
//	{
//		hp_holder_slot->SetPadding(FMargin(10.f, 0.f));
//	}
//
//	hp_ = NewObject<UProgressBar>();
//	FString hp_unique_name = MakeUniqueObjectName(GetOuter(), hp_->GetClass(), TEXT("HP")).ToString();
//	hp_->Rename(*hp_unique_name);
//	hp_->SetPercent(0.5f);
//	hp_holder_->AddChild(hp_.Get());
//
//	spacer_hp_deal_ = NewObject<USpacer>();
//	FString spacer_hp_deal_unique_name = MakeUniqueObjectName(GetOuter(), spacer_hp_deal_->GetClass(), TEXT("Spacer b/t HP&deal")).ToString();
//	spacer_hp_deal_->Rename(*spacer_hp_deal_unique_name);
//	spacer_hp_deal_->SetSize(FVector2D(1.0, 20.0));
//	root_vertical_box_->AddChildToVerticalBox(spacer_hp_deal_.Get());
//
//	// Init damage dealt section.
//	deal_holder_ = NewObject<UHorizontalBox>();
//	FString deal_holder_unique_name = MakeUniqueObjectName(GetOuter(), deal_holder_->GetClass(), TEXT("deal holder")).ToString();
//	deal_holder_->Rename(*deal_holder_unique_name);
//	UVerticalBoxSlot* deal_holder_slot = root_vertical_box_->AddChildToVerticalBox(deal_holder_.Get());
//	if (deal_holder_slot)
//	{
//		deal_holder_slot->SetPadding(FMargin(20.f, 0.f));
//	}
//
//	deal_icon_ = NewObject<UImage>();
//	FString deal_icon_unique_name = MakeUniqueObjectName(GetOuter(), deal_holder_->GetClass(), TEXT("Deal icon")).ToString();
//	deal_icon_->Rename(*deal_icon_unique_name);
//
//	UTexture2D* deal_texture = texture_manager->GetTexture("damage_icon");
//	if (!deal_texture)
//	{
//		UE_LOG(LogTemp, Error, TEXT("Loading damage icon image has failed!"));
//		return;
//	}
//	FSlateBrush deal_icon_brush;
//	deal_icon_brush.SetResourceObject(deal_texture);
//	deal_icon_brush.SetImageSize(FVector2D(64, 64));
//	deal_icon_->SetBrush(deal_icon_brush);
//	UHorizontalBoxSlot* deal_icon_slot = deal_holder_->AddChildToHorizontalBox(deal_icon_.Get());
//	if (deal_icon_slot)
//	{
//		deal_icon_slot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Left);
//	}
//
//	deal_text_ = NewObject<UTextBlock>();
//	FString deal_text_unique_name = MakeUniqueObjectName(GetOuter(), deal_text_->GetClass(), TEXT("damage dealt")).ToString();
//	deal_text_->Rename(*deal_text_unique_name);
//	deal_text_->SetText(FText::FromString("2000"));
//	deal_text_->SetJustification(ETextJustify::Type::Center);
//	UHorizontalBoxSlot* deal_text_slot = deal_holder_->AddChildToHorizontalBox(deal_text_.Get());
//	if (deal_text_slot)
//	{
//		deal_text_slot->SetSize(FSlateChildSize());
//		deal_text_slot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
//		deal_text_slot->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);
//	}
//}
