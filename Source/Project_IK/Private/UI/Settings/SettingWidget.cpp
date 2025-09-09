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

#include "Subsystems/AudioManagerSubsystem.h"

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
	RemoveFromViewport();
}
