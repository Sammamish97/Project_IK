/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 03.02.2025
Summary : Header file of a manager that handles UI controls after runs.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RunResultManager.generated.h"

class UToMainMenuWidget;
class URunRewardWidget;

enum class ERunResultState : uint8;

/**
 * 
 */
UCLASS(Blueprintable)
class PROJECT_IK_API URunResultManager : public UObject
{
	GENERATED_BODY()
public:
	void StartRunResultSequence();

	void SwitchUIByState(ERunResultState state);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UToMainMenuWidget> main_menu_ui_class_ = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<URunRewardWidget> run_reward_ui_class_ = nullptr;
protected:

	UPROPERTY()
	TObjectPtr<UToMainMenuWidget> main_menu_ui_ = nullptr;

	UPROPERTY()
	TObjectPtr<URunRewardWidget> run_reward_ui_ = nullptr;
};
