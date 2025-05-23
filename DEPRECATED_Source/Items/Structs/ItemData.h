/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 04.02.2025
Summary : Structure for Item data.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Managers/EnumCluster.h"
#include "Structs/TargetParameters.h"
#include "ItemData.generated.h"



USTRUCT(BlueprintType)
struct FItemData
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	EItemType item_type_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	UTexture2D* item_icon_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FString item_description_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FTargetParameters target_params_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	ERarity rarity_;
};