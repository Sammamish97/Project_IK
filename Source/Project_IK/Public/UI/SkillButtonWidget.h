/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 6.03.2025
Summary : Header file for Skill Button Widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SkillButtonWidget.generated.h"

UCLASS()
class PROJECT_IK_API USkillButtonWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	
	UFUNCTION()
	void OnSkillInvoked(float cool_time);

	void SetThumbnailTexture(UTexture2D* thumbnail);
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UBorder> border_;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> button_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UProgressBar> progress_bar_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> cool_down_text_;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UTexture2D> empty_texture_;

protected:
	float left_cool_down_;
	float cool_time_;
};
