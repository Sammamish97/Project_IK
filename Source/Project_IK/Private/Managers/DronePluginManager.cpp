/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 12.04.2024
Summary : Source file for structure that explain each of drone plugin.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Managers/DronePluginManager.h"
#include "Managers/EnumCluster.h"
#include "Structs/DPData.h"

UDronePluginManager::UDronePluginManager()
	:Super::URarityAbstractObject()
{
	FString dp_data_path = TEXT("/Script/Engine.DataTable'/Game/Resources/IK_Proto_DP_Data.IK_Proto_DP_Data'");
	static ConstructorHelpers::FObjectFinder<UDataTable> dt_dp_data(*dp_data_path);
	if (dt_dp_data.Succeeded() == false)
	{
		UE_LOG(LogTemp, Error, TEXT("GameInstance has failed to load a dp file data (IK_Proto_Drone_Plugin_Data)"));
	}
	dp_table_= dt_dp_data.Object;

	CategorizeByRarity(dp_table_);
}

//BP에서는 struct의 pointer를 return할 수 없다. 그러므로, 복사본으로 넘긴다.
FDPData UDronePluginManager::GetDPData(EDPType dp_id) const
{
	if (dp_table_)
	{
		return *dp_table_->FindRow<FDPData>(*EnumToString(dp_id), TEXT(""));
	}
	return *dp_table_->FindRow<FDPData>(*EnumToString(EDPType::Empty), TEXT(""));
}

FDPData UDronePluginManager::GetDPDataRandomly(ERarity weight_rarity) const
{
	if (!dp_table_)
	{
		return *dp_table_->FindRow<FDPData>(*EnumToString(EDPType::Empty), TEXT(""));
	}

	FDPData* ptr = reinterpret_cast<FDPData*>(GetRandomDataByRarity(GetRarityRandomly(weight_rarity)));
	if (ptr)
	{
		return *ptr;
	}
	else
	{
		return *dp_table_->FindRow<FDPData>(*EnumToString(EDPType::Empty), TEXT(""));
	}
}

TArray<FDPData> UDronePluginManager::GetUniqueDPDataRandomly(int32 n, ERarity rarity) const
{
	TArray<FDPData> return_array;
	if (!dp_table_)
	{
		return return_array;
	}

	TArray<FRarityData*> raw_array = GetUniqueRandomData(GetRaritiesRandomly(rarity, n));
	return_array.Reserve(raw_array.Num());
	for (FRarityData* raw_data : raw_array)
	{
		return_array.Add(*reinterpret_cast<FDPData*>(raw_data));
	}

	return return_array;
}

FString UDronePluginManager::EnumToString(EDPType dp_type) const
{
	FString dp_string;
	switch (dp_type)
	{
	case EDPType::FireRateBurst:
		dp_string = TEXT("FireRateBurst");
		break;
	case EDPType::FireRange:
		dp_string = TEXT("FireRange");
		break;
	case EDPType::HealingWaves:
		dp_string = TEXT("HealingWaves");
		break;
	case EDPType::LaserBeam:
		dp_string = TEXT("LaserBeam");
		break;
	default:
		dp_string = TEXT("Empty");
		break;
	}
	return dp_string;
}
