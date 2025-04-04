/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 04.02.2025
Summary : Header file for Item data asset.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "Managers/EnumCluster.h"
#include "Structs/ItemData.h"

#include "ItemDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UItemDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	FItemData GetItemData(EItemType type);
	FItemData GetItemDataRandomly(ERarity weight_rarity = ERarity::Common);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	TMap<EItemType, FItemData> item_data_map_;
};
