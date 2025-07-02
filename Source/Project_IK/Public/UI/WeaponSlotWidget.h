/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.1.2025
Summary : Header file for Weapon Slot Widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "InventorySlot.h"
#include "Structs/WeaponData.h"
#include "WeaponSlotWidget.generated.h"

UCLASS()
class PROJECT_IK_API UWeaponSlotWidget : public UInventorySlot
{
	GENERATED_BODY()
public:
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	void SetWeaponSlotData(FWeaponData weapon_data);
	FWeaponData GetStoredWeaponData();
	virtual void SetImageTexture() override;
	
private:
	FWeaponData weapon_data_cache_;
};
