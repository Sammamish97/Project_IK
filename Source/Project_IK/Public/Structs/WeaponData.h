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

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "WeaponData")
	TSubclassOf<class AGunBase> weapon_class_ = nullptr;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "WeaponData")
	EWeaponType type = EWeaponType::INVALID;
	
	//TODO: 이후 현지화를 생각하면 FString대신, Table의 위치를 넣어야 할 수 있다.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "WeaponData")
	FString flavor_text;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "WeaponData")
	TObjectPtr<UTexture2D> thumbnail = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponData")
	ERarity rarity_;
};