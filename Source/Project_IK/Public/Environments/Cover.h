/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.03.2024
Summary : Header file for Cover.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "Interfaces/Damageable.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cover.generated.h"

class UCharacterStatComponent;
class USphereComponent;
class UBoxComponent;

UCLASS()
class PROJECT_IK_API ACover : public AActor, public IDamageable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACover();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	bool HasCoveringOwner() const;
	void SetCoveringOwner(bool bHas_Covering_Owner);
	bool IsBroken() const;
	void SetIsBroken(bool bIs_Broken);
	virtual void GetDamage(FDamageData data) override;
	void SetHitPoints(float hit_points);
	float GetHitPoints();

	UFUNCTION()
	virtual void Die() override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Cover", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBoxComponent> cover_collider_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Cover", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent> cover_position_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Cover", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> cover_mesh_;

	bool has_covering_owner_ = false;
	bool is_broken_ = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Cover", meta = (AllowPrivateAccess = "true"))
	float hit_points_ = 100.f;
};
