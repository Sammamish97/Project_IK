/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 09.21.2024
Summary : Header file for HUD class.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "IKHUD.generated.h"

class UButtonBarWidget;
class UCombatResultUI;
class UItemPickerUI;
class UCombatLevelResultManager;

enum class ECombatEndState : uint8;

UCLASS()
class PROJECT_IK_API AIKHUD : public AHUD
{
	GENERATED_BODY()
public:
	UFUNCTION()
	virtual void BeginPlay() override;
	void DisplayCombatResult(const TArray<AActor*>& heroes, const TMap<TWeakObjectPtr<AActor>, float>& damage_map);

	UFUNCTION()
	void SwitchUIByState(ECombatEndState state);

	UFUNCTION()
	void SynchroItemButtons();

	UFUNCTION()
	void SilenceSkill(AActor* character);
	void UnsilenceSkill(AActor* character);

	UFUNCTION(BlueprintCallable)
	void ToggleInventory();

	// Reference to the Widget Blueprint class to create
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UButtonBarWidget> button_widget_class_;
	// Reference to the Widget Blueprint class to create
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UCombatLevelResultManager> combat_level_widget_class_;
	
protected:

	// Reference to the widget instance
	UPROPERTY()
	TObjectPtr<UButtonBarWidget> button_widget_;

	UPROPERTY()
	TObjectPtr<UCombatLevelResultManager> combat_level_result_manager_;

	
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UInventoryWidget> inventory_widget_class_;
	
	UPROPERTY()
	TObjectPtr<UInventoryWidget> inventory_widget_;
};
