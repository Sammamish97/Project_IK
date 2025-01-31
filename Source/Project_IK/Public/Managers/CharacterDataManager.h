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

UCLASS()
class PROJECT_IK_API UCharacterDataManager : public UObject
{
	GENERATED_BODY()
public:
	UCharacterDataManager();

	FCharacterData* GetCharacterData(EHeroType char_id) const;
	FString EnumToString(EHeroType dp_type) const;
protected:
	class UDataTable* character_table;
};