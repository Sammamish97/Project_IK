/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 8.27.2025
Summary : Header file for Hero Data Asset.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Structs/HeroData.h"
#include "Managers/EnumCluster.h"
#include "HeroDataAsset.generated.h"

//만약 영웅이 가지고 있어야 하는데 SpawnData, 혹은 Character Data에 넣을 수 없다면 여기에 넣는다.
UCLASS()
class PROJECT_IK_API UHeroDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	FHeroData GetHeroData(EHeroType type);

private:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TMap<EHeroType, FHeroData> hero_data_map_;
};
