/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 1.3.2025
Summary : Header file for a user widget to display gotcha result.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GotchaResultWidget.generated.h"

class UGotchaSlot;
class UGridPanel;
class UImage;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnResultFinished);

/**
 * 
 */
UCLASS(Blueprintable)
class PROJECT_IK_API UGotchaResultWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void DisplayResults(TArray<UTexture2D*> textures);
	void DisplayResult(UTexture2D* texture);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UGotchaSlot> gotcha_slot_class_;

	UPROPERTY(BlueprintAssignable, Category = "UI")
	FOnResultFinished OnResultFinished;
protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	UFUNCTION()
	void ContinueAnimation();
	void StartAnimationSquence(int32 animation_max_);
	void PlayNextAnimation();
	void StopAllAnimations();


	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TWeakObjectPtr<UGridPanel> image_containers_;

	TArray<TWeakObjectPtr<UGotchaSlot>> slots_;

	static constexpr int32 MAX_IMAGE = 10;
	int32 animation_max;

	int32 current_animation_index_;

	FTimerHandle animation_timer_handle_;
	bool is_running_;
};
