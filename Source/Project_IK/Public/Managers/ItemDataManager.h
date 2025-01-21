/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 11.27.2024
Summary : Header file for Manager that controls item data.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "RarityAbstractObject.h"
#include "EnumCluster.h"
#include "ItemDataManager.generated.h"

USTRUCT(BlueprintType)
struct FItemData : public FRarityData
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, Category = "Item")
	FString item_name_;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	UTexture2D* item_icon_;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	FString item_description_;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	EItemLogicType item_logic_;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	ETargetingMode targeting_mode_;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	ETargetType target_type_;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	float range_;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	float radius_;
};

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UItemDataManager : public URarityAbstractObject
{
	GENERATED_BODY()
public:
	UItemDataManager();

	FItemData* GetItemData(int32 item_id) const;
	FItemData* GetItemDataRandomly(ERarity rarity = ERarity::B) const;
	TArray<FItemData*> GetUniqueItemDataRandomly(int32 n = 1, ERarity rarity = ERarity::B) const;

protected:
	class UDataTable* item_table_;
};
