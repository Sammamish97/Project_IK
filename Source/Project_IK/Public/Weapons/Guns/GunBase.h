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
#include "AITypes.h"
#include "NiagaraSystem.h"
#include "GunBase.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnCriticalRateCalculationDelegate, float&);

UCLASS(Abstract)
class PROJECT_IK_API AGunBase : public AActor
{
	GENERATED_BODY()

	friend class UDelegateBridgeSubsystem;

public:	
	AGunBase();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

	virtual void Reload();
	virtual void OnReload();
	virtual void BeginFire(AActor* target);
	
	virtual void FinishFire();
	
	bool IsMagazineEmpty() const;
	FWeaponData GetWeaponData();
	TObjectPtr<USkeletalMeshComponent> GetWeaponSkeletalMesh();
	FName GetGrabSocketName();

	FDamageData GetWeaponFireDamageData();

	UFUNCTION()
	void SetGunOwner(TWeakObjectPtr<AUnit> gun_owner, bool is_hero);

	UFUNCTION()
	void AddOnHitComponent(TSubclassOf<class UBulletOnHitEffectComponent> target_component);
	void RemoveOnHitComponent(TSubclassOf<class UBulletOnHitEffectComponent> target_component);
	void ClearOnHitComponents();

	void AddAfterReloadOnHitComponent(TSubclassOf<class UBulletOnHitEffectComponent> target_component);
	void RemoveAfterReloadOnHitComponent(TSubclassOf<class UBulletOnHitEffectComponent> target_component);
	void ClearAfterReloadOnHitComponents();

protected:
	void FireSingleBullet(FVector target_pos, const FDamageData& dmg_data);
	void SpawnBullet(const FTransform& transform, const FDamageData& dmg_data);

public:
	void AttachParticleEffect(UNiagaraSystem* niagara_system);
	void RemoveParticleEffect(UNiagaraSystem* niagara_system);
	void ClearParticleEffects();
	void AddParticleParameterFloat(UNiagaraSystem* niagara_system, FName name, float float_data);
	void AddParticleParameterVector(UNiagaraSystem* niagara_system, FName name, const FVector& vector_data);

	void ApplyMaterial(UMaterialInterface* material);
	void RemoveMaterial(UMaterialInterface* material);
	void ClearMaterials();
	
	FORCEINLINE FAIRequestID GetReloadRequestId() const { return reload_request_id_; }

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> weapon_skeletal_mesh_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USphereComponent> root_sphere_mesh_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	FWeaponData weapon_data_;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> fire_montage_;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> reload_montage_;

	UPROPERTY(Transient)
	int32 cur_magazine_;
	
	UPROPERTY(Transient)
	FTimerHandle fire_timer_handle_;
	UPROPERTY(Transient)
	FTimerHandle reload_timer_handle_;

	FOnCriticalRateCalculationDelegate OnCriticalRateCalculation;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UObjectPoolComponent> object_pool_component_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<class UBulletOnHitEffectComponent>> on_hit_effect_classes_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<class UBulletOnHitEffectComponent>> on_hit_after_reload_;
	
	UPROPERTY(Transient)
	TWeakObjectPtr<class AUnit> weak_gun_owner_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponMechanics", meta = (AllowPrivateAccess = "true"))
	FName head_socket_name_;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	FName grab_socket_name_;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	FName muzzle_socket_name_;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponMechanics", meta = (AllowPrivateAccess = "true"))
	FName owned_cover_key_name_;
	
	FAIRequestID reload_request_id_ = 0;

	UPROPERTY()
	TArray<UNiagaraSystem*> niagara_systems_;

	UPROPERTY()
	TArray<UMaterialInterface*> materials_;

	TMap<UNiagaraSystem*, TMap<FName, float>> float_parameters_;
	TMap<UNiagaraSystem*, TMap<FName, FVector>> vector_parameters_;

	bool is_first_bullet_on_magazine_ = true;

protected:
	UPROPERTY(Transient)
	float HARD_CODED_ACCURACY = 10.f;
};
