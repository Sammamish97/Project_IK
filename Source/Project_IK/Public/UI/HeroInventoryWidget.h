/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 2.06.2025
Summary : Header file for inventory widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HeroInventoryWidget.generated.h"

class UButton;
class UInventorySlot;
class UHeroInventoryManager;
UCLASS()
class PROJECT_IK_API UHeroInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	void InitInventoryWidget(UHeroInventoryManager* inventory_component);
	void LoadInventoryComponent();
	void ApplyInventoryComponent();

	UFUNCTION()
	void SwitchToLeftHero();
	UFUNCTION()
	void SwitchToRightHero();
private:
	UHeroInventoryManager* inventory_manager_ref_;
	int cur_hero_idx_;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta=(AllowPrivateAccess=true, BindWidget))
	class UTextBlock* hero_name_text_;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta=(AllowPrivateAccess=true, BindWidget))
	FName cur_hero_name_;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta=(AllowPrivateAccess=true, BindWidget))
	UButton* switch_hero_left_button_;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta=(AllowPrivateAccess=true, BindWidget))
	UButton* switch_hero_right_button_;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	TSubclassOf<class UInventorySlot> slot_BP_class_;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta=(AllowPrivateAccess=true, BindWidget))
	UInventorySlot* hero_armor_;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta=(AllowPrivateAccess=true, BindWidget))
	UInventorySlot* hero_trinket_;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta=(AllowPrivateAccess=true, BindWidget))
	class UWrapBox* wrap_box_;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta=(AllowPrivateAccess=true, BindWidget))
	class UScrollBox* scroll_box_;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta=(AllowPrivateAccess=true))
	TArray<UInventorySlot*> inventory_slots_;
};
