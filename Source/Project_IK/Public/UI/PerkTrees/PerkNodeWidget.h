/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 8.13.2025
Summary : Header file for perk node widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structs/PerkConnectionColor.h"
#include "Structs/PerkNodeDetail.h"
#include "PerkNodeWidget.generated.h"

class UPerkConnectionWidget;
class UPerkProgressSubsystem;
class UImage;
class UButton;
class UOverlay;
class UAudioComponent;

UCLASS(Blueprintable)
class PROJECT_IK_API UPerkNodeWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	void SaveSkill();
	
	void UnlockSkill();
	void PurchaseSkill();
	bool CanPurchase();
	void RemoveSkillPoint(int32 amount);
	bool IsPurchased();
	UFUNCTION(BlueprintCallable)
	void ConnectPerkNodes();
	TArray<UPerkNodeWidget*> GetConnectedSkills();
	TArray<UPerkNodeWidget*> GetAllSkills();
	FLinearColor LinearColorLerp(float duration);

	UFUNCTION(BlueprintCallable)
	void SetAlignment();

public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	ESlateVisibility SetUnlockedImageVisibility();
	UFUNCTION(BlueprintCallable, BlueprintPure)
	ESlateVisibility SetLockIconVisibility();
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FLinearColor SetIconColor();
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FSlateBrush SetIconBrush();
	UFUNCTION(BlueprintCallable, BlueprintPure)
	ESlateVisibility SetCheckVisibility();

private:
	UFUNCTION()
	void OnButtonPressed();
	UFUNCTION()
	void OnButtonReleased();
	UFUNCTION()
	void OnButtonHovered();
	UFUNCTION()
	void OnButtonUnhovered();

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UOverlay> skill_connection_overlay_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> button_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> thumbnail_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> lock_icon_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> unlocked_image;

	//
	UPROPERTY(EditAnywhere)
	TArray<int32> connected_indices_;

	UPROPERTY(EditAnywhere)
	int32 perk_index_;

	UPROPERTY(EditAnywhere)
	FPerkNodeDetail perk_detail_;

	UPROPERTY(EditAnywhere)
	FPerkConnectionColor perk_connection_color_ = {FLinearColor::White, 1.0, {0.791667, 0.441022, 0}, 1.0};

	FLinearColor purchased_color_ = {0.791667, 0.441022, 0};

	float timer_;
	//

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UPerkConnectionWidget> perk_connection_widget_class_;

	UPROPERTY(Transient)
	TObjectPtr<UPerkProgressSubsystem> progress_system_cache_;

	UAudioComponent* unlocking_sfx_ = nullptr;
};
