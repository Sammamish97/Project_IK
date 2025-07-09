/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 1.25.2024
Summary : Header file for spawn data that used to share across sessions.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "ActiveSkillData.h"
#include "PassiveSkillData.h"
#include "RuneData.h"
#include "WeaponData.h"
#include "Structs/CharacterData.h"
#include "SpawnData.generated.h"

USTRUCT(BlueprintType)
struct PROJECT_IK_API FSpawnData
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SpawnData")
	bool is_dead_ = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SpawnData")
	FCharacterData character_data_;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SpawnData")
	TOptional<FWeaponData> weapon_data_;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SpawnData")
	TOptional<FPassiveSkillData> passive_skill_data_1_;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SpawnData")
	TOptional<FPassiveSkillData> passive_skill_data_2_;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SpawnData")
	TOptional<FPassiveSkillData> passive_skill_data_3_;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SpawnData")
	TOptional<FActiveSkillData> active_skill_data_;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SpawnData")
	TOptional<FRuneData> rune_data_1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SpawnData")
	TOptional<FRuneData> rune_data_2;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SpawnData")
	TOptional<FRuneData> rune_data_3;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SpawnData")
	TOptional<FRuneData> rune_data_4;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SpawnData")
	TOptional<FRuneData> rune_data_5;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SpawnData")
	TOptional<FRuneData> rune_data_6;
};