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
#include "Managers/EnumCluster.h"
#include "HeroBase.generated.h"

UCLASS()
class PROJECT_IK_API AHeroBase : public AUnit
{
	GENERATED_BODY()
public:
	AHeroBase();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	virtual void Initialize();
	virtual void Die() override;

	virtual void GetDamage(FDamageData data) override;
	virtual void GetStunned(float stun_duration) override;
	virtual void OnStunned() override;

	UFUNCTION(BlueprintCallable)
	void SetPeriodicDP(EDPType dp_type);
	UFUNCTION(BlueprintCallable)
	void SetGenericDP(EDPType dp_type);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Hero", meta = (AllowPrivateAccess = "true", BindWidget))
	class USkillContainer* skill_container_;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Hero", meta = (AllowPrivateAccess = "true", BindWidget))
	class UWeaponMechanics* weapon_mechanics_;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Hero", meta = (AllowPrivateAccess = "true", BindWidget))
	class UPassiveMechanics* passive_mechanics_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Hero", meta = (AllowPrivateAccess = "true", BindWidget))
	class UArmorMechanics* armor_mechanics_;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero", meta = (AllowPrivateAccess = "true", AllowedClass = "Drone", BindWidget))
	UClass* drone_bp_class_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero", meta = (AllowPrivateAccess = "true"))
	class USphereComponent* drone_location_;
	
	class ADrone* drone_;
};
