/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.03.2024
Summary : Header file for WeaponMechanics.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Managers/EnumCluster.h"
#include "Structs/CharacterData.h"
#include "Structs/DamageData.h"
#include "Structs/WeaponData.h"
#include "WeaponMechanics.generated.h"

class AUnit;
class UCharacterStatComponent;
class AGun;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_IK_API UWeaponMechanics : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponMechanics();

public:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	void OnDestroy();

	void SetDamageData(FCharacterData char_data, FDamageData dmg_data);
	
	void BeginFire(AActor* target);
	void OnFire(AActor* target);
	void FireWeapon(AActor* target);
	void FinishFire();
	void FinishBurstCooldown();
	
	void Reload();
	void OnReload();
	
	bool IsMagazineEmpty() const;
	FWeaponData GetWeaponData();

	void OnStunned();
	
	UFUNCTION()
	void EquipWeapon(EWeaponType type);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponMechanics", meta = (AllowPrivateAccess = "true"))
	FDamageData damage_data_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponMechanics", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AGun> weapon_class_ = nullptr;
	
	UPROPERTY(Transient)
	TObjectPtr<AGun> weapon_actor_ = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponMechanics", meta = (AllowPrivateAccess = "true"))
	FName head_socket_name_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponMechanics", meta = (AllowPrivateAccess = "true"))
	FName gun_socket_name_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponMechanics", meta = (AllowPrivateAccess = "true"))
	FName owned_cover_key_name_;

	UPROPERTY(Transient)
	FTimerHandle fire_timer_handle_;

	UPROPERTY(Transient)
	FTimerHandle reload_timer_handle_;

	UPROPERTY(Transient)
	FTimerHandle burst_timer_handle_;
	
	UPROPERTY(Transient)
	TObjectPtr<AUnit> gunner_ref_ = nullptr;

	UPROPERTY(Transient)
	int32 burst_count_ = 0;

	UPROPERTY(Transient)
	bool on_burst_cool_down_ = false;
};
