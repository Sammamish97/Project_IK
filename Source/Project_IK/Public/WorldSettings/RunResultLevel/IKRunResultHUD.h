/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 03.31.2025
Summary : Header file for HUD class used in RunResultLevel.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "IKRunResultHUD.generated.h"

class URunRewardWidget;

/**
 * 
 */
UCLASS()
class PROJECT_IK_API AIKRunResultHUD : public AHUD
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<URunRewardWidget> run_reward_ui_class_ = nullptr;

	FReply HandleKeyboardAction(const FKeyEvent& InKeyEvent);
	
protected:
	virtual void BeginPlay() override;



	UPROPERTY()
	TObjectPtr<URunRewardWidget> run_reward_ui_ = nullptr;
};
