/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 8.06.2025
Summary : Header file for Lobby level hud.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "IKLobbyLevelHUD.generated.h"

class ULobbyWidget;

UCLASS()
class PROJECT_IK_API AIKLobbyLevelHUD : public AHUD
{
	GENERATED_BODY()
public:
	// Need to add TSubclassOf and ptr of MapWidget
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<ULobbyWidget> lobby_widget_class_;
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	TObjectPtr<ULobbyWidget> lobby_widget_;
};
