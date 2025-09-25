/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 09.08.2025
Summary : Source file for Setting UI.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "UI/Settings/SettingWidget.h"

#include "Components/TextBlock.h"
#include "Components/Slider.h"
#include "Components/Button.h"
#include "Components/ComboBoxString.h"

#include "Subsystems/AudioManagerSubsystem.h"

// Save files
#include "Kismet/GameplayStatics.h"
#include "SaveGame/SaveSettings.h"

// Language
#include "Kismet/KismetInternationalizationLibrary.h"
void USettingWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UAudioManagerSubsystem* subsystem = UAudioManagerSubsystem::Get(this);
	if (subsystem)
	{
		MasterSliderChanged(subsystem->GetMasterVolume());
		master_slider_->SetValue(master_volume_);

		MusicSliderChanged(subsystem->GetBGMVolume());
		music_slider_->SetValue(music_volume_);

		SFXSliderChanged(subsystem->GetSFXVolume());
		sfx_slider_->SetValue(sfx_volume_);
	}

	master_slider_->OnValueChanged.AddDynamic(this, &USettingWidget::MasterSliderChanged);
	music_slider_->OnValueChanged.AddDynamic(this, &USettingWidget::MusicSliderChanged);
	sfx_slider_->OnValueChanged.AddDynamic(this, &USettingWidget::SFXSliderChanged);

	master_slider_->OnMouseCaptureEnd.AddDynamic(this, &USettingWidget::MasterSliderCaptureEnd);
	music_slider_->OnMouseCaptureEnd.AddDynamic(this, &USettingWidget::MusicSliderCaptureEnd);
	sfx_slider_->OnMouseCaptureEnd.AddDynamic(this, &USettingWidget::SFXSliderCaptureEnd);

	confirm_button_->OnClicked.AddDynamic(this, &USettingWidget::OnConfirmButtonClicked);

	InitLanguageDropdown();
}

void USettingWidget::NativeDestruct()
{
	master_slider_->OnValueChanged.Clear();
	music_slider_->OnValueChanged.Clear();
	sfx_slider_->OnValueChanged.Clear();

	master_slider_->OnMouseCaptureEnd.Clear();
	music_slider_->OnMouseCaptureEnd.Clear();
	sfx_slider_->OnMouseCaptureEnd.Clear();

	confirm_button_->OnClicked.Clear();

	Super::NativeDestruct();
}

void USettingWidget::MasterSliderChanged(float value)
{
	// Only Set local data and update text
	master_volume_ = value;
	master_text_->SetText(FText::FromString(FString::FromInt(master_volume_ * 100.f)));
}

void USettingWidget::MusicSliderChanged(float value)
{
	music_volume_ = value;
	music_text_->SetText(FText::FromString(FString::FromInt(music_volume_ * 100.f)));
}

void USettingWidget::SFXSliderChanged(float value)
{
	sfx_volume_ = value;
	sfx_text_->SetText(FText::FromString(FString::FromInt(sfx_volume_ * 100.f)));
}

void USettingWidget::MasterSliderCaptureEnd()
{
	UAudioManagerSubsystem::Get(this)->SetMasterVolume(master_volume_);
}

void USettingWidget::MusicSliderCaptureEnd()
{
	UAudioManagerSubsystem::Get(this)->SetBGMVolume(music_volume_);
}

void USettingWidget::SFXSliderCaptureEnd()
{
	UAudioManagerSubsystem::Get(this)->SetSFXVolume(sfx_volume_);
}

void USettingWidget::OnConfirmButtonClicked()
{
	SaveSettingData();

	// In order to prevent using deprecated api,
	RemoveFromParent();
}

void USettingWidget::SaveSettingData()
{
	// Save data in save game thread
	// May cause hitches because it writes to the disc

	USaveSettings* save_game_instance = Cast<USaveSettings>(UGameplayStatics::CreateSaveGameObject(USaveSettings::StaticClass()));
	if (save_game_instance)
	{
		save_game_instance->master_volume_ = master_volume_;
		save_game_instance->music_volume_ = music_volume_;
		save_game_instance->sfx_volume_ = sfx_volume_;
	}

	UGameplayStatics::SaveGameToSlot(save_game_instance, save_game_instance->GetSaveSlotName(), 0);
}

void USettingWidget::InitLanguageDropdown()
{
	language_box_->OnSelectionChanged.AddDynamic(this, &USettingWidget::OnLanguageSelected);
	
	PopulateDropdown();

	const FString current = UKismetInternationalizationLibrary::GetCurrentCulture();

	for (const auto& [label, code] : label_to_code_)
	{
		if (code == current)
		{
			language_box_->SetSelectedOption(label);
			break;
		}
	}
}

void USettingWidget::OnLanguageSelected(FString selected, ESelectInfo::Type selection_type)
{
	if (const FString* code = label_to_code_.Find(selected))
	{
		UKismetInternationalizationLibrary::SetCurrentCulture(*code, true);
	}
}

void USettingWidget::PopulateDropdown()
{
	language_box_->ClearOptions();

	label_to_code_.Empty();

	const TArray<FString> culture_codes = UKismetInternationalizationLibrary::GetLocalizedCultures(true, false, false, false);

	for (const FString& code : culture_codes)
	{
		const FString display = UKismetInternationalizationLibrary::GetCultureDisplayName(code, true);
		const FString label = FString::Printf(TEXT("%s [%s]"), *display, *code);

		language_box_->AddOption(label);
		label_to_code_.Add(label, code);
	}
}