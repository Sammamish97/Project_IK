/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 05.04.2025
Summary : Header file for data assets for character stats.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Structs/CharacterData.h"
#include "CharacterStatDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UCharacterStatDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	const FCharacterData& GetCharacterData(EHeroType hero_type);

	void EnhanceCharacterData(EHeroType hero_type, ECharacterStatType stat_type, float increase_amount);
	void DiminishCharacterData(EHeroType hero_type, ECharacterStatType stat_type, float decrease_amount);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EHeroType, FCharacterData> character_data_map_;
};
