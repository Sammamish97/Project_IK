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

/**
 * 
 */
class AUnit;
USTRUCT(BlueprintType)
struct FCharacterData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FCharacterData() : ability_power_(0.f), attack_(0.f), attack_speed_(0.f), hit_point_(0.f), magazine_(0.f),
		fire_range_(0.f), move_speed_(0.f), sight_range_(0.f)
	{};

	// Unit Type
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TSubclassOf<AUnit> unit_class_;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Data")
	FName character_name_;
	
	// Scaling powers
	UPROPERTY(VisibleAnywhere, Category = "Data")
	float ability_power_;
	UPROPERTY(VisibleAnywhere, Category = "Data")
	float attack_;
	UPROPERTY(VisibleAnywhere, Category = "Data")
	float attack_speed_;
	UPROPERTY(VisibleAnywhere, Category = "Data")
	float hit_point_;
	UPROPERTY(VisibleAnywhere, Category = "Data")
	float magazine_;

	// Fixed powers
	UPROPERTY(VisibleAnywhere, Category = "Data")
	float fire_range_;
	UPROPERTY(VisibleAnywhere, Category = "Data")
	float move_speed_;
	UPROPERTY(VisibleAnywhere, Category = "Data")
	float sight_range_;
	UPROPERTY(VisibleAnywhere, Category = "Data")
	float evasion_;

	//Drone Plugins
	UPROPERTY(VisibleAnywhere, Category = "Data")
	EDPType periodic_dp_;
	UPROPERTY(VisibleAnywhere, Category = "Data")
	EDPType general_dp_;

	//Hero Upgrade
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Data")
	int upgrade_level_;
};

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