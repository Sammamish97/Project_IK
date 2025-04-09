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
	EWeaponType type = EWeaponType::Pistol;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "WeaponData")
	TObjectPtr<UTexture2D> thumbnail = nullptr;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "WeaponData")
	TObjectPtr<UStaticMesh> weapon_mesh = nullptr;

	//1초에 몇발 사격하는가?
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "WeaponData")
	float fire_per_sec = 0.f;

	//한번에 몇발 발사하는가?(점사 한정)
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "WeaponData")
	int32 burst_amount = 0;

	//한번 사격이 끝난 후 얼마나 기다려야 하는가? (점사/볼트액션)
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "WeaponData")
	float wait_after_fire = 0.f;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "WeaponData")
	EFireType fire_type = EFireType::INVALID;

	//무기 사거리
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "WeaponData")
	float fire_range = 0.f;
	
	//기본 공격력
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "WeaponData")
	float basic_dmg_ = 0.f;
	
	//공격력 계수
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "WeaponData")
	float attack_ratio = 0.f;

	//무기 치명타 확률
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "WeaponData")
	float critical_hit_rate_ = 0.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gun", meta = (AllowPrivateAccess = "true"))
	int32 max_magazine = 0;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gun", meta = (AllowPrivateAccess = "true"))
	float reload_duration = 0.f;

	//TODO: 이 방식은 이 총을 사용하는 모든 Unit의 Skeletal Bone구조가 동일한 경우 사용 가능하다.
	//TODO: 만약 영웅별로 사용하는 Skeletal Bone구조가 다르다면 다른 방식이 필요하다.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gunner", meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<UAnimMontage> fire_montage_ = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gunner", meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<UAnimMontage> reload_montage_ = nullptr;

	//TODO: 이후 현지화를 생각하면 FString대신, Table의 위치를 넣어야 할 수 있다.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "WeaponData")
	FString flavor_text;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponData")
	ERarity rarity_;
};