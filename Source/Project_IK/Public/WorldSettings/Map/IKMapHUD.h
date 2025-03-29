/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 02.27.2025
Summary : Header file for Map Level HUD class.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "IKMapHUD.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_IK_API AIKMapHUD : public AHUD
{
	GENERATED_BODY()

	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	void PopUpInventory();
	
	UFUNCTION(BlueprintCallable)
	void RemoveInventory();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<class UUserWidget> map_widget_class_;
	
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UInventoryWidget> inventory_widget_class_;

	UPROPERTY()
	TObjectPtr<UUserWidget> map_widget_;
	
	UPROPERTY()
	TObjectPtr<UInventoryWidget> inventory_widget_;
};
