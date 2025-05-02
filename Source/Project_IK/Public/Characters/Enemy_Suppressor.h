/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 4.30.2025
Summary : Header file for Suppressor enemy.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "Interfaces/Attackable.h"
#include "Enemy_Suppressor.generated.h"

UCLASS()
class PROJECT_IK_API AEnemy_Suppressor : public AEnemyBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy_Suppressor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnStunned() override;
	virtual void Die() override;

	virtual void OnEnterBattleOnce() override;

	virtual void Attack(AActor* target) override;

	void GetBonusPower();

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gunner", meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<class UWeaponMechanics> weapon_mechanics_;

	float preheat_duration_ = 5.f;
	float attack_speed_bonus_ = 30.f;

	UPROPERTY()
	FTimerHandle preheat_timer_;
};
