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

enum class ECombatEndState : uint8;
class UCombatResultUI;
class UEquipmentRewardWidget;
/**
 * 
 */
UCLASS(Blueprintable)
class PROJECT_IK_API UCombatLevelResultManager : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION()
	void InitializeUI();

	UFUNCTION()
	void DisplayCombatResult(const TArray<AActor*>& heroes, const TMap<TWeakObjectPtr<AActor>, float>& damage_map);

	UFUNCTION()
	void SwitchUIByState(ECombatEndState state);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UCombatResultUI> combat_result_widget_class_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UEquipmentRewardWidget> equipment_reward_widget_class_;

protected:
	UPROPERTY()
	TObjectPtr<UCombatResultUI> combat_result_widget_;

	UPROPERTY()
	TObjectPtr<UEquipmentRewardWidget> equipment_reward_widget_;
};
