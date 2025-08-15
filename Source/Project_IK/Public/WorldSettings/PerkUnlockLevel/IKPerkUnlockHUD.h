/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 2.4.2025
Summary : Header file for HUD using PerkUnlockLevel.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "IKPerkUnlockHUD.generated.h"

class UPerkHUDWidget;
class UPerkUnlockWidget;

/**
 * 
 */
UCLASS()
class PROJECT_IK_API AIKPerkUnlockHUD : public AHUD
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UPerkHUDWidget> perk_unlock_widget_class_;

	TObjectPtr<UPerkHUDWidget> GetPerkHUDWidget();
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	TObjectPtr<UPerkHUDWidget> perk_hud_widget_;
};
