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
#include "OopartData.h"
#include "PassiveSkillData.h"
#include "WeaponData.h"
#include "Structs/CharacterData.h"
#include "SpawnData.generated.h"

USTRUCT(BlueprintType)
struct PROJECT_IK_API FSpawnData
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SpawnData")
	FCharacterData character_data_;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SpawnData")
	FWeaponData weapon_data_;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SpawnData")
	FPassiveSkillData passive_skill_data_;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SpawnData")
	FActiveSkillData active_skill_data_;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SpawnData")
	FOopartData oopart_data_;

	//TODO: Rune Data역시 추가해야함.
};