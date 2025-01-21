/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 01.15.2025
Summary : Header file for HUD that used in StoreLevel.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "IKStoreHUD.generated.h"

class UStoreWidget;

/**
 * 
 */
UCLASS(Blueprintable)
class PROJECT_IK_API AIKStoreHUD : public AHUD
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UStoreWidget> store_widget_class_;

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY()
	TObjectPtr<UStoreWidget> store_widget_;
};
