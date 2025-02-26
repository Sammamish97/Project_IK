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

USTRUCT()
struct PROJECT_IK_API FWeaponData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "WeaponData")
	EWeaponType type = EWeaponType::Pistol;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "WeaponData")
	TSubclassOf<class AGun> weapon_class;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "WeaponData")
	UTexture2D* thumbnail = nullptr;

	//TODO: 이 방식은 이 총을 사용하는 모든 Unit의 Skeletal Bone구조가 동일한 경우 사용 가능하다.
	//TODO: 만약 영웅별로 사용하는 Skeletal Bone구조가 다르다면 다른 방식이 필요하다.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gunner", meta = (AllowPrivateAccess = "true", BindWidget))
	UAnimMontage* fire_montage_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gunner", meta = (AllowPrivateAccess = "true", BindWidget))
	UAnimMontage* reload_montage_;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "WeaponData")
	FString flavor_text;
};
