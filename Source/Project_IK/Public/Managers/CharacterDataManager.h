/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 11.10.2024
Summary : Header file for managing characters data.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include "Managers/EnumCluster.h"
#include "CharacterDataManager.generated.h"

struct FCharacterData;
enum class ECharacterStatType : uint8;

UCLASS()
class PROJECT_IK_API UCharacterDataManager : public UObject
{
	GENERATED_BODY()
public:
	UCharacterDataManager();

	FCharacterData* GetCharacterData(EHeroType hero_type) const;
	FString EnumToString(EHeroType dp_type) const;

	void EnhanceCharacterData(EHeroType hero_type, ECharacterStatType stat_type, float increase_amount);
	void DiminishCharacterData(EHeroType hero_type, ECharacterStatType stat_type, float diminish_amount);

protected:
	class UDataTable* character_table;
};