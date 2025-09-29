/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 9.29.2025
Summary : Header file for opening widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OpeningWidget.generated.h"

class UTextManager;
class UTextBlock;
class UImage;

UCLASS()
class PROJECT_IK_API UOpeningWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	UFUNCTION(BlueprintCallable)
	void PlayFadeIn(float PlayRate = 1.f);
	UFUNCTION(BlueprintCallable)
	void PlayFadeOut(float PlayRate = 1.f);
	UFUNCTION()
	void OnFadeInFinished();
	UFUNCTION()
	void OnFadeOutFinished();
	
private:
	UPROPERTY(Transient)
	TObjectPtr<UTextManager> text_manager_cache_;
	
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TArray<TObjectPtr<UTexture2D>> images_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> image_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> subtitle_;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> fade_in_;

	UPROPERTY(Transient, meta = (BindWidgetAnimOptional))
	TObjectPtr<UWidgetAnimation> fade_out_;
	
	int32 counter_ = 0;
};
