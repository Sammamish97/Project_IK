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
#include "CharacterData.generated.h"

class AUnit;
USTRUCT(BlueprintType)
struct FCharacterData : public FTableRowBase
{
	GENERATED_BODY()

public:
	// Unit Type
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TSubclassOf<AUnit> unit_class_ = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Data")
	FName character_name_ = "";

	UPROPERTY(VisibleAnywhere, Category = "AttackData")
	float attack_power_ = 0.f;
	UPROPERTY(VisibleAnywhere, Category = "AttackData")
	float attack_speed_ = 0.f;
	UPROPERTY(VisibleAnywhere, Category = "AttackData")
	float critical_hit_rate_ = 0.f;
	UPROPERTY(VisibleAnywhere, Category = "AttackData")
	float accuracy_ = 0.f;
	UPROPERTY(VisibleAnywhere, Category = "AttackData")
	float magazine_bonus_ = 0.f;
	UPROPERTY(VisibleAnywhere, Category = "AttackData")
	float life_steal_ = 0.f;


	UPROPERTY(VisibleAnywhere, Category = "DefenseData")
	float hit_point_ = 0.f;
	UPROPERTY(VisibleAnywhere, Category = "DefenseData")
	float evasion_rate_ = 0.f;
	UPROPERTY(VisibleAnywhere, Category = "DefenseData")
	float armor_ = 0.f;
	UPROPERTY(VisibleAnywhere, Category = "DefenseData")
	float survivability_ = 0.f;

	UPROPERTY(VisibleAnywhere, Category = "AgilityData")
	float move_speed_ = 0.f;

	UPROPERTY(VisibleAnywhere, Category = "SkillData")
	float active_skill_power_ = 0.f;
	UPROPERTY(VisibleAnywhere, Category = "SkillData")
	float active_skill_cooldown_ = 0.f;
	UPROPERTY(VisibleAnywhere, Category = "SkillData")
	float passive_skill_power_ = 0.f;
	UPROPERTY(VisibleAnywhere, Category = "SkillData")
	float passive_skill_cooldown_ = 0.f;
};