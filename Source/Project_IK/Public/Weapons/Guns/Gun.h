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
#include "Gun.generated.h"

UCLASS(Abstract)
class PROJECT_IK_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
		
	virtual void Reload();
	virtual void Reload(int32 amount);
	virtual void FireWeapon(FVector target_pos, FDamageData damage);

	bool IsMagazineEmpty() const;
	void SetWeaponData(FWeaponData weapon_data);
	FWeaponData GetWeaponData();
	UFUNCTION()
	void SetGunOwner(TWeakObjectPtr<AActor> gun_owner);

	void OnFireStub();
	void OnReloadStub();

	UFUNCTION()
	void AddOnHitComponent(TSubclassOf<class UBulletOnHitEffectComponent> target_component);
	void RemoveOnHitComponent(TSubclassOf<class UBulletOnHitEffectComponent> target_component);
	void ClearOnHitComponents();

	void AddAfterReloadOnHitComponent(TSubclassOf<class UBulletOnHitEffectComponent> target_component);
	void RemoveAfterReloadOnHitComponent(TSubclassOf<class UBulletOnHitEffectComponent> target_component);
	void ClearAfterReloadOnHitComponents();

private:
	void FireSingleBullet(FVector muzzle_location, FVector target_pos, FDamageData dmg_data);
	void FireBuckShot(FVector muzzle_location, FVector target_pos, FDamageData dmg_data);
	void SpawnBullet(const FTransform& transform, const FDamageData& dmg_data);
	
protected:
	UPROPERTY(BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UStaticMeshComponent> weapon_mesh_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UNiagaraComponent> niagara_component_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAudioComponent> audio_component_;
	
	UPROPERTY(BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	FWeaponData weapon_data_;

	UPROPERTY(Transient)
	int32 cur_magazine_;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UObjectPoolComponent> object_pool_component_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<class UBulletOnHitEffectComponent>> on_hit_effect_classes_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<class UBulletOnHitEffectComponent>> on_hit_after_reload_;
	
	UPROPERTY(VisibleAnywhere, Category = "Gun")
	TWeakObjectPtr<AActor> gun_owner_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true", AllowedClass = "Animation"))
	TSubclassOf<UAnimInstance> anim_instance_class_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	FName muzzle_socket_name_;

	bool is_first_bullet_on_magazine_ = true;
};
