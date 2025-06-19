/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.03.2024
Summary : Header file for Bullet.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Structs/DamageData.h"
#include "Weapons/PooledActor.h"
#include "Bullet.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UNiagaraSystem;

UCLASS(Abstract)
class PROJECT_IK_API ABullet : public APooledActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void SetShooter(TWeakObjectPtr<AActor> shooter);

	UFUNCTION()
	void SetDamageData(FDamageData data);
	void SetCollisionPreset(bool is_hero);

	UFUNCTION()
	void AddOnHitComponent(TSubclassOf<class UBulletOnHitEffectComponent> target_component);
	void RemoveOnHitComponent(TSubclassOf<class UBulletOnHitEffectComponent> target_component);
	void Clear();

	virtual void SetInUse(bool in_use) override;

	USceneComponent* GetSceneComponent() const;
	void ApplyMaterial(int32 element_index, UMaterialInterface* material);

	// Destructor of pooled actors
	virtual void ReturnToPool() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void ClearComponentsAttachedOnMesh();


	void SpawnImpactParticle(FVector impact_location, FVector impact_normal);
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Particles")
	TObjectPtr<UNiagaraSystem> impact_particle_;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Bullet")
	TObjectPtr<USphereComponent> collision_;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, BlueprintReadWrite, Category = "Bullet")
	TObjectPtr<UProjectileMovementComponent> movement_;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Bullet")
	TObjectPtr<UStaticMeshComponent> bullet_mesh_;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Bullet")
	TArray<TObjectPtr<UBulletOnHitEffectComponent>> on_hit_components_;

	UPROPERTY(VisibleAnywhere, Category = "Bullet")
	TWeakObjectPtr<AActor> shooter_;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Bullet")
	FDamageData dmg_data_;

	TWeakObjectPtr<UMaterialInterface> original_material_;
};
