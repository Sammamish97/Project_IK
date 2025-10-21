/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 09.14.2024
Summary : Header file for Character Stat class.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once
#include "Managers/EnumCluster.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Structs/BuffStatusData.h"
#include "Structs/CharacterData.h"
#include "CharacterStatComponent.generated.h"


enum class ECharacterStatType : uint8;
class ADamageUI;
class UDelegateBridgeSubsystem;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHPChangedDelegate, float, hp_ratio);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnShieldChangedDelegate, float, shield_ratio);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHPOrShieldChanged, float, cur_hp, float, cur_shield);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHPChangedWithOwnerDelegate, float, hp_ratio, AActor*, owner_actor);

UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJECT_IK_API UCharacterStatComponent : public UActorComponent
{
	GENERATED_BODY()

	friend UDelegateBridgeSubsystem;
	
public:	
	// Sets default values for this actor's properties
	UCharacterStatComponent();
	virtual void InitializeComponent() override;
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunctionoverride);

	//만약 유닛 생성 시, 데이터 에셋에 있는 character stat에 상황에 따라 추가적인 값을 더하고 싶다면 유닛을 생성후 이 함수를 통해 조정한다.
	void ApplyExtraStatusForSummoned(const FStatusData& status);
	
	UFUNCTION(BlueprintCallable)
	bool CalcDamage(FDamageData& data_ref);

	void RecordDamage(FDamageData& data_ref);

	UFUNCTION(BlueprintCallable)
	void GetDamage(float damage);
	UFUNCTION(BlueprintCallable)
	void Heal(float HealAmount);
	UFUNCTION(BlueprintCallable)
	void AcquireShield(float ShieldAmount, float Duration);
	void DestroyShield();

	// Getters&Setters of member variables
	UFUNCTION(BlueprintPure)
	float GetAttackPower() const noexcept;
	UFUNCTION(BlueprintPure)
	float GetAttackSpeed() const noexcept;
	UFUNCTION(BlueprintPure)
	float GetCriticalHitRate() const noexcept;
	UFUNCTION(BlueprintPure)
	float GetAccuracy() const noexcept;
	UFUNCTION(BlueprintPure)
	float GetMagazineBonus() const noexcept;
	UFUNCTION(BlueprintPure)
	float GetReloadSpeedBonus() const noexcept;
	UFUNCTION(BlueprintPure)
	float GetLifeSteal() const noexcept;


	UFUNCTION(BlueprintPure)
	float GetHitPoint() const noexcept;
	UFUNCTION(BlueprintPure)
	float GetEvasionRate() const noexcept;
	UFUNCTION(BlueprintPure)
	float GetArmor() const noexcept;
	
	UFUNCTION(BlueprintPure)
	float GetSightRange() const noexcept;
	UFUNCTION(BlueprintPure)
	float GetMoveSpeed() const noexcept;
	
	UFUNCTION(BlueprintPure)
	float GetSkillPower() const noexcept;
	UFUNCTION(BlueprintPure)
	float GetSkillCooldown() const noexcept;

	UFUNCTION(BlueprintPure)
	float GetShield() const noexcept;

	UFUNCTION(BlueprintPure)
	float GetHPRatio() const noexcept;
	UFUNCTION(BlueprintPure)
	float GetShieldRatio() const noexcept;

	UFUNCTION(BlueprintPure)
	float GetMaxHitPoint() const noexcept;
	UFUNCTION(BlueprintPure)
	float GetMaxShield() const noexcept;

	UFUNCTION(BlueprintPure)
	FCharacterData GetCharacterData() const noexcept;

	UFUNCTION(BlueprintCallable)
	void SetCharacterData(const FCharacterData& character_data) noexcept;

	UFUNCTION(BlueprintCallable)
	float CalculateStat(ECharacterStatType StatType) const;

	UFUNCTION(BlueprintCallable)
	float GetBaseStat(ECharacterStatType StatType) const;

	void ApplyBuff(EBuffType buff_type, FBuffStatusData status_data);
	void RemoveBuff(EBuffType buff_type);
	void RemoveBuff(EBuffType buff_type, ECharacterStatType stat_type);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnHPChangedDelegate OnHPChanged;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnHPChangedWithOwnerDelegate OnHPChangedWithOwner;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnShieldChangedDelegate OnShieldChanged;
	
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnHPOrShieldChanged OnHPOrShieldChanged;

	UFUNCTION(BlueprintCallable)
	void SetAttackPower(float attack_power) noexcept;
	UFUNCTION(BlueprintCallable)
	void SetAttackSpeed(float attack_speed) noexcept;
	UFUNCTION(BlueprintCallable)
	void SetCriticalHitRate(float critical_hit_rate) noexcept;
	UFUNCTION(BlueprintCallable)
	void SetAccuracy(float accuracy) noexcept;
	UFUNCTION(BlueprintCallable)
	void SetMagazineBonus(float magazine_bonus) noexcept;
	UFUNCTION(BlueprintCallable)
	void SetLifeSteal(float life_steal) noexcept;

	UFUNCTION(BlueprintCallable)
	void SetHitPoint(float hit_point) noexcept;
	UFUNCTION(BlueprintCallable)
	void SetEvasionRate(float evasion_rate) noexcept;
	UFUNCTION(BlueprintCallable)
	void SetArmor(float armor) noexcept;

	UFUNCTION(BlueprintCallable)
	void SetSightRange(float sight_range) noexcept;
	UFUNCTION(BlueprintCallable)
	void SetMoveSpeed(float move_speed) noexcept;
	
	UFUNCTION(BlueprintCallable)
	void SetSkillPower(float active_skill_power) noexcept;
	UFUNCTION(BlueprintCallable)
	void SetSkillCooldown(float active_skill_cooldown) noexcept;

	UFUNCTION(BlueprintCallable)
	void SetShield(float shield) noexcept;
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ADamageUI> damage_UI_class_;

	UPROPERTY(VisibleInstanceOnly, Category = Stats, Meta = (AllowPrivateAccess = true))
	FCharacterData character_data_;

	UPROPERTY(VisibleInstanceOnly, Category = Stats, meta = (AllowPrivateAccess = true))
	float shield_;

	float max_shield_;
	FTimerHandle shield_timer_;

	float max_hit_points_;

	TMap<EBuffType, TMap<ECharacterStatType, FBuffStatusData>> buffs_;
	TMap<EBuffType, TMap<ECharacterStatType, FTimerHandle>> buff_timers_;
};
