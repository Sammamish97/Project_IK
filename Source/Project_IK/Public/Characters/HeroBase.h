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
#include "Interfaces/Attackable.h"
#include "Managers/EnumCluster.h"
#include "HeroBase.generated.h"

DECLARE_DELEGATE_RetVal_OneParam(FDamageData, FOnDamage, FDamageData);

UCLASS()
class PROJECT_IK_API AHeroBase : public AUnit, public IAttackable
{
	GENERATED_BODY()
public:
	AHeroBase();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	virtual void Initialize();
	virtual void Die() override;

	virtual FDamageData Attack(AActor* target) override;
	virtual void GetDamage(FDamageData data) override;
	virtual void GetStunned(float stun_duration) override;
	virtual void OnStunned() override;
	EHeroType GetHeroType() const;

public:
	TMap<EHeroEvent, TArray<FOnDamage>> hero_dmg_event_map_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Hero", meta = (AllowPrivateAccess = "true", BindWidget))
	class USphereComponent* oopart_pos_;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Hero", meta = (AllowPrivateAccess = "true", BindWidget))
	class USkillContainer* skill_container_;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Hero", meta = (AllowPrivateAccess = "true", BindWidget))
	class UWeaponMechanics* weapon_mechanics_;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Hero", meta = (AllowPrivateAccess = "true", BindWidget))
	class UPassiveSkillMechanics* passive_skill_mechanics_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Hero", meta = (AllowPrivateAccess = "true", BindWidget))
	class UEquipMechanics* equip_mechanics_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Hero", meta = (AllowPrivateAccess = "true", BindWidget))
	class UOopartMechanics* oopart_mechanics_;

private:
	EHeroType hero_type_;
};
