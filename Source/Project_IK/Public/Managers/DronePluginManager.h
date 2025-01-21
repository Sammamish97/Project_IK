/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 12.04.2024
Summary : Header file for structure that explain each of drone plugin.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Structs/DPData.h"
#include "DronePluginManager.generated.h"

UCLASS(Blueprintable)
class PROJECT_IK_API UDronePluginManager : public URarityAbstractObject
{
	GENERATED_BODY()
public:
	UDronePluginManager();

	UFUNCTION(BlueprintCallable, Category = "DronePluginManager")
	FDPData GetDPData(EDPType dp_id) const;

	UFUNCTION(BlueprintCallable, Category = "DronePluginManager")
	FDPData GetDPDataRandomly(ERarity weight_rarity = ERarity::B) const;

	TArray<FDPData> GetUniqueDPDataRandomly(int32 n = 1, ERarity rarity = ERarity::B) const;
	
	FString EnumToString(EDPType dp_type) const;
	
private:
	class UDataTable* dp_table_;
};