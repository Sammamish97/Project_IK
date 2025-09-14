/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.03.2024
Summary : Header file for Gun.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Structs/DamageData.h"
#include "Structs/WeaponData.h"
#include "GunBase.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnCriticalRateCalculationDelegate, float&);
DECLARE_MULTICAST_DELEGATE(FOnFireWeapon);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnFinishReload, UBehaviorTreeComponent*, bt_component, bool, is_interrupted);

class UNiagaraComponent;
class UNiagaraSystem;
enum class EAudioType : uint8;

UCLASS(Abstract)
class PROJECT_IK_API AGunBase : public AActor
{
	GENERATED_BODY()

	friend class UDelegateBridgeSubsystem;

public:	
	AGunBase();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

	virtual void InstantReload();
	virtual void Reload();
	virtual void OnReload();
	virtual void StopReload();
	
	virtual void BeginFire(AActor* target);
	virtual void FinishFire();

	virtual void Die();
	
	bool IsMagazineEmpty() const;
	FWeaponStatusData GetWeaponStatusData() const;
	TObjectPtr<USkeletalMeshComponent> GetWeaponSkeletalMesh() const;
	FName GetGrabSocketName() const;
	FName GetMuzzleSocketName() const;

	FDamageData GetWeaponFireDamageData();

	void SetHoldAction(bool hold_action);

	UFUNCTION()
	void InitWeapon(const FWeaponData& data, TWeakObjectPtr<AUnit> gun_owner, bool is_hero);
	
	UFUNCTION()
	void AddOnHitComponent(TSubclassOf<class UBulletOnHitEffectComponent> target_component);
	void RemoveOnHitComponent(TSubclassOf<class UBulletOnHitEffectComponent> target_component);
	void ClearOnHitComponents();

	void AddAfterReloadOnHitComponent(TSubclassOf<class UBulletOnHitEffectComponent> target_component);
	void RemoveAfterReloadOnHitComponent(TSubclassOf<class UBulletOnHitEffectComponent> target_component);
	void ClearAfterReloadOnHitComponents();

	void ChangeGunShotSoundTemporariliy(EAudioType temporary_gunshot_audio, float duration = 0.f);

protected:
	void FireSingleBullet(FVector target_pos, const FDamageData& dmg_data);
	void FireBuckShot(FVector target_pos, const FDamageData& dmg_data);
	void SpawnBullet(const FRotator& rotation, const FVector& translation, const FDamageData& dmg_data);

	void PlayFireFXs() const;
	void PlayFireSound() const;

	UFUNCTION()
	void OnGunDied();

	UFUNCTION()
	void OnDieFinished();

	UFUNCTION()
	void RecoverGunShotSound();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon" )
	TObjectPtr<USkeletalMeshComponent> weapon_skeletal_mesh_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon" )
	TObjectPtr<class USphereComponent> root_sphere_mesh_;

	UPROPERTY()
	FWeaponData weapon_data_cache_;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Weapon" )
	TObjectPtr<UAnimMontage> fire_montage_;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Weapon" )
	TObjectPtr<UAnimMontage> reload_montage_;

	UPROPERTY(Transient)
	int32 cur_magazine_;
	
	UPROPERTY(Transient)
	float HARD_CODED_ACCURACY = 10.f;
	
	UPROPERTY(Transient)
	FTimerHandle fire_timer_handle_;
	UPROPERTY(Transient)
	FTimerHandle reload_timer_handle_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon" )
	TObjectPtr<class UObjectPoolComponent> bullet_pool_component_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon" )
	TArray<TSubclassOf<class UBulletOnHitEffectComponent>> on_hit_effect_classes_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon" )
	TArray<TSubclassOf<class UBulletOnHitEffectComponent>> on_hit_after_reload_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particles")
	TObjectPtr<UNiagaraComponent> ejection_particle_component_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particles")
	TObjectPtr<UNiagaraComponent> fire_particle_component_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Death")
	TObjectPtr<UNiagaraSystem> death_fx_system_;
	
	UPROPERTY(Transient)
	TWeakObjectPtr<class AUnit> weak_gun_owner_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponMechanics" )
	FName head_socket_name_;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon" )
	FName grab_socket_name_;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon" )
	FName muzzle_socket_name_;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponMechanics" )
	FName owned_cover_key_name_;
	
	bool is_first_bullet_on_magazine_ = true;

	bool hold_action_ = false;
	
	FTimerHandle die_timer_;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio")
	EAudioType gunshot_audio_type_ = EAudioType::NONE;

	TArray<EAudioType> temporary_gunshot_audio_type_stack_;

public:
	FOnFinishReload OnFinishReload;
	FOnCriticalRateCalculationDelegate OnCriticalRateCalculation;
	FOnFireWeapon OnFireWeapon;
};
