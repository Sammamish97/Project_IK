/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 2.8.2025
Summary : Header file for the Weapon data structure.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Managers/EnumCluster.h"
#include "WeaponData.generated.h"

USTRUCT(BlueprintType)
struct PROJECT_IK_API FWeaponData
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "WeaponData")
	EWeaponType type = EWeaponType::INVALID;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "WeaponData")
	EBulletType bullet_type = EBulletType::INVALID;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "WeaponData")
	EWeaponAnimationType anim_type = EWeaponAnimationType::INVALID;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "WeaponData")
	TObjectPtr<UTexture2D> thumbnail = nullptr;

	//1초에 몇발 사격하는가?
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "WeaponData")
	float fire_per_sec = 0.f;
	
	//무기 사거리
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "WeaponData")
	float fire_range = 0.f;
	
	//기본 공격력
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "WeaponData")
	float basic_dmg_ = 0.f;
	
	//공격력 계수
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "WeaponData")
	float attack_scale = 0.f;

	//스킬 위력 계수
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "WeaponData")
	float skill_power_scale = 0.f;

	//무기 치명타 확률
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "WeaponData")
	float critical_hit_rate_ = 0.f;

	//최대 탄약
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gun", meta = (AllowPrivateAccess = "true"))
	int32 max_magazine = 0;

	//장전 소요 시간
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gun", meta = (AllowPrivateAccess = "true"))
	float reload_duration = 0.f;

	//예열 소요 시간
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gun", meta = (AllowPrivateAccess = "true"))
	float accuracy_ = 0.f;
	
	//TODO: 이후 현지화를 생각하면 FString대신, Table의 위치를 넣어야 할 수 있다.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "WeaponData")
	FString flavor_text;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponData")
	ERarity rarity_;
};