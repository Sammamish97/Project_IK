/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 1.25.2024
Summary : Header file for character data.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Managers/EnumCluster.h"
#include "Structs/StatusData.h"
#include "CharacterData.generated.h"

class AUnit;
USTRUCT(BlueprintType)
struct FCharacterData
{
	GENERATED_BODY()

public:
	// Unit Type
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TSubclassOf<AUnit> unit_class_ = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FName character_name_ = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	EUnitBoneType bone_type_;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StatusData")
	FStatusData status_data_ = FStatusData{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AgilityData")
	float sight_range_ = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AgilityData")
	float move_speed_ = 0.f;
};