/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 11.20.2024
Summary : Header file of a manager that handles UI controls after combats.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CombatLevelResultManager.generated.h"

enum class ELevelEndState : uint8;
/**
 * 
 */
UCLASS()
class PROJECT_IK_API UCombatLevelResultManager : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION()
	void InitializeUI(TSubclassOf<class UCombatResultUI> combat_result_widget_class, TSubclassOf<class UItemPickerUI> item_picker_widget_class, TSubclassOf<class UUserWidget> map_widget_class, UWorld* world);

	UFUNCTION()
	void DisplayCombatResult(const TArray<AActor*>& heroes, const TMap<TWeakObjectPtr<AActor>, float>& damage_map);

	UFUNCTION()
	void SwitchUIByState(ELevelEndState state);

protected:

	UPROPERTY()
	TObjectPtr<UCombatResultUI> combat_result_widget_;

	UPROPERTY()
	TObjectPtr<UItemPickerUI> item_picker_widget_;

	UPROPERTY()
	TObjectPtr<UUserWidget> map_widget_;
};
