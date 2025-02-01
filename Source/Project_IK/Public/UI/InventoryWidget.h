/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 1.10.2025
Summary : Header file for the Inventory Widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

class UScrollBox;
class UDPSlot;
class UWrapBox;
class UButton;
class UTextBlock;
class UInventoryManager;
UCLASS()
class PROJECT_IK_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	
	void InitInventoryWidget(UInventoryManager* inventory_component);
	void LoadInventoryComponent();
	void ApplyHeroDP();
	void ApplyInventoryComponent();

	UFUNCTION()
	void SwitchToLeftHero();
	UFUNCTION()
	void SwitchToRightHero();


private:
	UInventoryManager* inventory_manager_ref_;
	int cur_hero_idx_;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta=(AllowPrivateAccess=true, BindWidget))
	UTextBlock* hero_name_text_;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta=(AllowPrivateAccess=true, BindWidget))
	FName cur_hero_name_;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta=(AllowPrivateAccess=true, BindWidget))
	UButton* switch_hero_left_button_;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta=(AllowPrivateAccess=true, BindWidget))
	UButton* switch_hero_right_button_;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	TSubclassOf<UDPSlot> slot_BP_class_;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta=(AllowPrivateAccess=true, BindWidget))
	UDPSlot* heroDP_periodic_;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta=(AllowPrivateAccess=true, BindWidget))
	UDPSlot* heroDP_generic_;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta=(AllowPrivateAccess=true, BindWidget))
	UWrapBox* wrap_box_;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta=(AllowPrivateAccess=true, BindWidget))
	UScrollBox* scroll_box_;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta=(AllowPrivateAccess=true))
	TArray<UDPSlot*> inventory_slots_;
};
