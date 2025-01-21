/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 11.27.2024
Summary : Source file for Manager that controls item data.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Managers/ItemDataManager.h"
#include "Components/TargetingComponent.h"
#include "Managers/EnumCluster.h"

UItemDataManager::UItemDataManager()
	:Super::URarityAbstractObject()
{
	FString item_data_path = TEXT("/Script/Engine.DataTable'/Game/Resources/IK_Proto_ItemData.IK_Proto_ItemData'");
	static ConstructorHelpers::FObjectFinder<UDataTable> dt_item_data(*item_data_path);
	if (dt_item_data.Succeeded() == false)
	{
		UE_LOG(LogTemp, Error, TEXT("GameInstance has failed to load a game file data (IK_Proto_ItemData)"));
	}
	item_table_ = dt_item_data.Object;

	CategorizeByRarity(item_table_);
}

FItemData* UItemDataManager::GetItemData(int32 item_id) const
{
	if (item_table_)
	{
		return item_table_->FindRow<FItemData>(*FString::FromInt(item_id), TEXT(""));
	}
	return nullptr;
}

FItemData* UItemDataManager::GetItemDataRandomly(ERarity weight_rarity) const
{
	if (!item_table_)
	{
		return nullptr;
	}

	return reinterpret_cast<FItemData*>(GetRandomDataByRarity(GetRarityRandomly(weight_rarity)));
}

TArray<FItemData*> UItemDataManager::GetUniqueItemDataRandomly(int32 n, ERarity rarity) const
{
	TArray<FItemData*> return_array;
	if (!item_table_)
	{
		return return_array;
	}

	TArray<FRarityData*> raw_array = GetUniqueRandomData(GetRaritiesRandomly(rarity, n));
	return_array.Reserve(raw_array.Num());
	for (FRarityData* raw_data : raw_array)
	{
		return_array.Add(reinterpret_cast<FItemData*>(raw_data));
	}

	return return_array;
}
