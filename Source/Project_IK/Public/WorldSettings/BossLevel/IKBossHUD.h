/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 03.02.2025
Summary : Header file for HUD in BossLevel.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "IKBossHUD.generated.h"

class URunResultManager;

/**
 * 
 */
UCLASS()
class PROJECT_IK_API AIKBossHUD : public AHUD
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI")
	TSubclassOf<URunResultManager> run_result_manager_class_;

	void StartRunResultSequence();

protected:

	virtual void BeginPlay() override;


	UPROPERTY()
	TObjectPtr<URunResultManager> run_result_manager_;
};
