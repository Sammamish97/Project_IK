/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.20.2024
Summary : Header file for hero base. Every hero should inherit this class.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Characters/Unit.h"
#include "Structs/TargetResult.h"
#include "Structs/TargetParameters.h"
#include "Managers/EnumCluster.h"
#include "Structs/SpawnData.h"
#include "HeroBase.generated.h"

UCLASS(Abstract)
class PROJECT_IK_API AHeroBase : public AUnit
{
	GENERATED_BODY()
public:
	AHeroBase();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	virtual void EquipGears(FSpawnData spawn_data);
	virtual void Die() override;
	
	virtual void Attack(AActor* target) override;
	virtual void GetStunned(float stun_duration) override;
	virtual void OnStunned() override;
	
	EHeroType GetHeroType() const;
	TOptional<FTargetParameters> GetActiveSkillTargetParameters() const;

	void InvokeActiveSkill(FTargetResult target_result);
	bool IsActiveSkillOnCoolDown() const;
	bool HasActiveSkill() const;
	void ReduceCooltime(float reduce_time);
	// percentage range [0.f, 1.f]
	void ReduceCooltimeByPercentage(float percentage);

	void Reposition(FVector target_location);
	void SetAttackTarget(AActor* target);
	void SetIsCovered(bool is_covered);

	AActor* GetAttackTarget() const;
	
	class UWeaponMechanics* GetWeaponMechanics();
	class URuneMechanics* GetRuneMechanics();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Hero", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AGunBase> default_weapon_class_ = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Hero", meta = (AllowPrivateAccess = "true"))
	class USkillContainer* skill_container_;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Hero", meta = (AllowPrivateAccess = "true"))
	class UWeaponMechanics* weapon_mechanics_;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Hero", meta = (AllowPrivateAccess = "true"))
	class UPassiveSkillMechanics* passive_skill_mechanics_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Hero", meta = (AllowPrivateAccess = "true"))
	class URuneMechanics* rune_mechanics_;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Hero", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USphereComponent> ui_position_ = nullptr;
	
private:
	EHeroType hero_type_;
	bool is_covered_ = false;
};
