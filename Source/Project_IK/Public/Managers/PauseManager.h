/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 8.06.2025
Summary : Header file for Pause manager.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "PauseManager.generated.h"
class UPauseWidget;

UCLASS(Blueprintable)
class PROJECT_IK_API UPauseManager : public UObject
{
	GENERATED_BODY()

public:
	void TogglePause(bool on_pause);
	
private:
	void OpenPauseWidget();
	void ClosePauseWidget();
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UPauseWidget> pause_widget_class_;
	
	UPROPERTY()
	TObjectPtr<UPauseWidget> pause_widget_;
};
