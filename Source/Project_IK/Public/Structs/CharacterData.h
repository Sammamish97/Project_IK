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
	FCharacterData() : unit_class_(), character_name_(), 
		attack_power_(0.f), attack_speed_(0.f), critical_hit_rate_(0.f), accuracy_(0.f), magazine_bonus_(0.f), life_steal_(0.f), 
		hit_point_(0.f), evasion_rate_(0.f), armor_(0.f), survivability_(0.f),
		move_speed_(0.f), 
		active_skill_power_(0.f), active_skill_cooldown_(0.f),
		passive_skill_power_(0.f), passive_skill_cooldown_(0.f),
		upgrade_level_(0.f)
	{};

	// Unit Type
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TSubclassOf<AUnit> unit_class_;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Data")
	FName character_name_;

	UPROPERTY(VisibleAnywhere, Category = "AttackData")
	float attack_power_;
	UPROPERTY(VisibleAnywhere, Category = "AttackData")
	float attack_speed_;
	UPROPERTY(VisibleAnywhere, Category = "AttackData")
	float critical_hit_rate_;
	UPROPERTY(VisibleAnywhere, Category = "AttackData")
	float accuracy_;
	UPROPERTY(VisibleAnywhere, Category = "AttackData")
	float magazine_bonus_;
	UPROPERTY(VisibleAnywhere, Category = "AttackData")
	float life_steal_;


	UPROPERTY(VisibleAnywhere, Category = "DefenseData")
	float hit_point_;
	UPROPERTY(VisibleAnywhere, Category = "DefenseData")
	float evasion_rate_;
	UPROPERTY(VisibleAnywhere, Category = "DefenseData")
	float armor_;
	UPROPERTY(VisibleAnywhere, Category = "DefenseData")
	float survivability_;

	UPROPERTY(VisibleAnywhere, Category = "AgilityData")
	float move_speed_;

	UPROPERTY(VisibleAnywhere, Category = "SkillData")
	float active_skill_power_;
	UPROPERTY(VisibleAnywhere, Category = "SkillData")
	float active_skill_cooldown_;
	UPROPERTY(VisibleAnywhere, Category = "SkillData")
	float passive_skill_power_;
	UPROPERTY(VisibleAnywhere, Category = "SkillData")
	float passive_skill_cooldown_;
};