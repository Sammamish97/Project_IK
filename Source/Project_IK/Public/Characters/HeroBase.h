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
#include "Structs/TargetParameters.h"
#include "Managers/EnumCluster.h"
#include "Structs/SpawnData.h"
#include "HeroBase.generated.h"

UCLASS()
class PROJECT_IK_API AHeroBase : public AUnit
{
	GENERATED_BODY()
public:
	AHeroBase();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	virtual void SyncWithSpawnData(const FSpawnData& spawn_data);
	virtual void Die() override;

	virtual void SetUnitStateWithInterrupt(EUnitState type) override;
	virtual void ResetUnitState() override;
	
	virtual void Attack(AActor* target) override;
	virtual void GetStunned(float stun_duration) override;
	virtual void OnStunned() override;
	
	EHeroType GetHeroType() const;
	FTargetParameters GetActiveSkillTargetParameters() const;
	
	bool HasActiveSkill() const;
	const FItemData& GetActiveSkillItemData() const;
	void ReduceActiveSkillCoolDown(float amount);
	void ReduceActiveSkillCoolDownPercentage(float percentage);

	void Reposition(FVector target_location);
	void SetAttackTarget(AActor* target);
	void BeginMaintaining();
	
	AActor* GetAttackTarget() const;
	
	class UWeaponMechanics* GetWeaponMechanics();
	class URuneMechanics* GetRuneMechanics();
	class UActiveSkillMechanics* GetActiveSkillMechanics();
	class USkillBase* GetActiveSkill();
	class UPassiveSkillMechanics* GetPassiveSkillMechanics();


	void ChangeGunShotSoundTemporariliy(EAudioType temporary_gunshot_audio, float duration = 0.f);

protected:
	//Mechanics
	UPROPERTY(EditDefaultsOnly, Category = "Hero", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UActiveSkillMechanics> active_skill_mechanics_;
	
	UPROPERTY(EditDefaultsOnly, Category = "Hero", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UWeaponMechanics> weapon_mechanics_;
	
	UPROPERTY(EditDefaultsOnly, Category = "Hero", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UPassiveSkillMechanics> passive_skill_mechanics_;

	UPROPERTY(EditDefaultsOnly, Category = "Hero", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class URuneMechanics> rune_mechanics_;
	
	//Maintaining
	UPROPERTY(EditDefaultsOnly, Category = "Hero", meta = (AllowPrivateAccess = true))
	TSubclassOf<class UBuffHandler> maintain_buff_class_;

	UPROPERTY(Transient);
	TObjectPtr<class UBuffHandler> maintain_buff_;
	
public:
	//UI
	UPROPERTY(EditDefaultsOnly, Category = "Hero", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USphereComponent> ui_position_ = nullptr;
	
protected:
	UPROPERTY(EditDefaultsOnly)
	EHeroType hero_type_;
};
