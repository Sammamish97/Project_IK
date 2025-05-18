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

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "WeaponData")
	TObjectPtr<USkeletalMesh> weapon_mesh = nullptr;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "WeaponData")
	TSubclassOf<class ABullet> bullet_class_ = nullptr;

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
	
	//발사 애니메이션
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gunner", meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<UAnimMontage> fire_montage_ = nullptr;

	//장전 애니메이션
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gunner", meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<UAnimMontage> reload_montage_ = nullptr;

	//머즐 플래쉬 vfx
	UPROPERTY(EditAnywhere, Category = "Firing")
	TObjectPtr<class UNiagaraSystem> fire_muzzle_effect_;

	//발사 sfx
	UPROPERTY(EditAnywhere, Category = "Firing")
	TObjectPtr<class USoundBase> fire_sound_;

	//장전 sfx
	UPROPERTY(EditAnywhere, Category = "Firing")
	TObjectPtr<class USoundBase> reload_sound_;

	//TODO: 이후 현지화를 생각하면 FString대신, Table의 위치를 넣어야 할 수 있다.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "WeaponData")
	FString flavor_text;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponData")
	ERarity rarity_;
};