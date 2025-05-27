/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 5.15.2025
Summary : Header file for the Weapon Anim structure.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Managers/EnumCluster.h"
#include "WeaponAnimStruct.generated.h"

USTRUCT(BlueprintType)
struct PROJECT_IK_API FWeaponAnimStruct
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Weapon Anim Data")
	TSoftObjectPtr<UAnimMontage> fire_montage_;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Weapon Anim Data")
	TSoftObjectPtr<UAnimMontage> reload_montage_;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Weapon Anim Data")
	TSoftObjectPtr<UAnimBlueprint> weapon_anim_instance_;
	
	const TSoftObjectPtr<UAnimMontage>& operator[] (EWeaponAction action_type) const
	{
		switch (action_type)
		{
		case EWeaponAction::Fire:
			return fire_montage_;

		case EWeaponAction::Reload:
			return reload_montage_;

		case EWeaponAction::INVALID:
		default:
			checkNoEntry()
		}
		return fire_montage_;
	}
	
	TSoftObjectPtr<UAnimMontage>& operator[] (EWeaponAction rhs)
	{
		return const_cast<TSoftObjectPtr<UAnimMontage>&>(const_cast<const FWeaponAnimStruct*>(this)->operator[](rhs));
	}
};
