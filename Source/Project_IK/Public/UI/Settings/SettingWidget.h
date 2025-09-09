/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 09.08.2025
Summary : Header file for Setting UI.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SettingWidget.generated.h"

class UTextBlock;
class USlider;
class UButton;

/**
 * 
 */
UCLASS()
class PROJECT_IK_API USettingWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UFUNCTION()
	void MasterSliderChanged(float value);
	UFUNCTION()
	void MusicSliderChanged(float value);
	UFUNCTION()
	void SFXSliderChanged(float value);

	UFUNCTION()
	void MasterSliderCaptureEnd();
	UFUNCTION()
	void MusicSliderCaptureEnd();
	UFUNCTION()
	void SFXSliderCaptureEnd();

	UFUNCTION()
	void OnConfirmButtonClicked();

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USlider> master_slider_;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> master_text_;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USlider> music_slider_;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> music_text_;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USlider> sfx_slider_;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> sfx_text_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> confirm_button_;

	float master_volume_ = 0.f;
	float music_volume_ = 0.f;
	float sfx_volume_ = 0.f;
};
