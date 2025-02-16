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
#include "Gun.generated.h"

class UObjectPoolComponent;
class USphereComponent;
UCLASS()
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
	virtual void FireWeapon(FVector target_pos, FDamageData damage);

	bool IsMagazineEmpty() const;
	float GetFireInterval() const;
	void SetFireInterval(float Fire_Interval);
	float GetReloadDuration() const;
	void SetReloadDuration(float Reload_Duration);
	UFUNCTION()
	void SetGunOwner(TWeakObjectPtr<AActor> gun_owner);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gun", meta = (AllowPrivateAccess = "true", BindWidget))
	USkeletalMeshComponent* gun_mesh_;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gun", meta = (AllowPrivateAccess = "true", BindWidget))
	USphereComponent* muzzle_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gun", meta = (AllowPrivateAccess = "true", BindWidget))
	UObjectPoolComponent* object_pool_component_;

	UPROPERTY(VisibleAnywhere, Category = "Gun")
	TWeakObjectPtr<AActor> gun_owner_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet", meta = (AllowPrivateAccess = "true", AllowedClass = "Bullet"))
	TSubclassOf<class ABullet> bullet_class_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation", meta = (AllowPrivateAccess = "true", AllowedClass = "Animation"))
	TSubclassOf<UAnimInstance> anim_instance_class_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gun", meta = (AllowPrivateAccess = "true"))
	int max_megazine_ = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gun", meta = (AllowPrivateAccess = "true"))
	int cur_megazine_ = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gun", meta = (AllowPrivateAccess = "true"))
	float fire_interval_ = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gun", meta = (AllowPrivateAccess = "true"))
	float reload_duration_ = 0;
};
