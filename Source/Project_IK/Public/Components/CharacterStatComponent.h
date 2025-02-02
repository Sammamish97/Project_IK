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
#include "Structs/CharacterData.h"
#include <optional>
#include "CharacterStatComponent.generated.h"

class ADamageUI;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDieDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHPChangedDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnShieldChangedDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBuffChangedDelegate);

UENUM(BlueprintType)
enum class ECharacterStatType : uint8
{
	AbillityPower UMETA(DisplayName = "AbilityPower"),
	Attack UMETA(DisplayName = "Attack"),
	AttackSpeed UMETA(DisplayName = "AttackSpeed"),
	HitPoints UMETA(DisplayName = "HitPoints"),
	Magazine UMETA(DisplayName = "Magazine"),
	FireRange UMETA(DisplayName = "FireRange"),
	MoveSpeed UMETA(DisplayName = "MoveSpeed"),
	SightRange UMETA(DisplayName = "SightRange"),
	Evasion UMETA(DisplayName = "Evasion"),
	Shield UMETA(DisplayName = "Shield"),
};

USTRUCT(BlueprintType)
struct FBuff
{
public:
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Buff")
	FName buff_name_;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Buff")
	ECharacterStatType  stat_type_;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Buff")
	float value_;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Buff")
	bool is_percentage_;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Buff")
	bool is_permanent_;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Buff")
	float duration_;

	UPROPERTY(VisibleAnywhere, Transient, BlueprintReadOnly, Category = "Buff")
	float time_remaining_;



	FBuff()
		: stat_type_(ECharacterStatType::Attack), value_(0.f), is_percentage_(false), is_permanent_(false), duration_(0.f), time_remaining_(0.f)
	{}

	FBuff(FName Name, ECharacterStatType StatType, float Value, bool IsPercentage, float Duration)
		: buff_name_(Name), stat_type_(StatType), value_(Value), is_percentage_(IsPercentage), is_permanent_(false), duration_(Duration), time_remaining_(Duration)
	{}

	FBuff(FName Name, ECharacterStatType StatType, float Value, bool IsPercentage, bool IsPermanent)
		: buff_name_(Name), stat_type_(StatType), value_(Value), is_percentage_(IsPercentage), is_permanent_(true), duration_(0.f), time_remaining_(0.f)
	{}
};

UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJECT_IK_API UCharacterStatComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	UCharacterStatComponent();

	virtual void InitializeComponent() override;
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunctionoverride);

	UFUNCTION(BlueprintCallable)
	float CalcDamage(FDamageData data);
	UFUNCTION(BlueprintCallable)
	void GetDamage(float damage);
	UFUNCTION(BlueprintCallable)
	void Heal(float HealAmount);
	UFUNCTION(BlueprintCallable)
	void AcquireShield(float ShieldAmount, float Duration);
	void DestroyShield();

	// Getters&Setters of member variables
	UFUNCTION(BlueprintPure)
	float GetAbilityPower() const noexcept;
	UFUNCTION(BlueprintPure)
	float GetAttack() const noexcept;
	UFUNCTION(BlueprintPure)
	float GetAttackSpeed() const noexcept;
	UFUNCTION(BlueprintPure)
	float GetHitPoint() const noexcept;
	UFUNCTION(BlueprintPure)
	float GetMagazine() const noexcept;
	UFUNCTION(BlueprintPure)
	float GetFireRange() const noexcept;
	UFUNCTION(BlueprintPure)
	float GetMoveSpeed() const noexcept;
	UFUNCTION(BlueprintPure)
	float GetSightRange() const noexcept;
	UFUNCTION(BlueprintPure)
	float GetEvasion() const noexcept;
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
	
	//Getter & Setter for Drone Plugins.
	UFUNCTION(BlueprintPure)
	EDPType GetPeriodicDP() const noexcept;

	UFUNCTION(BlueprintCallable)
	void SetPeriodicDP(const EDPType& dp_data) noexcept;

	UFUNCTION(BlueprintPure)
	EDPType GetGeneralDP() const noexcept;

	UFUNCTION(BlueprintCallable)
	void SetGeneralDP(const EDPType& dp_data) noexcept;

	UFUNCTION(BlueprintCallable)
	float CalculateStat(ECharacterStatType StatType) const;

	UFUNCTION(BlueprintCallable)
	float GetBaseStat(ECharacterStatType StatType) const;

	UFUNCTION(BlueprintCallable)
	void ApplyBuff(FBuff buff);

	UFUNCTION(BlueprintCallable)
	bool RemoveBuff(FName BuffName);

	UFUNCTION(BlueprintPure)
	TArray<FBuff> GetBuffs() const;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FDieDelegate Die;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnHPChangedDelegate OnHPChanged;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnShieldChangedDelegate OnShieldChanged;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnBuffChangedDelegate OnBuffChanged;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	//TODO: 현재는 HeroType으로 되어있지만, Character stat은 Hero뿐만이 아닌 Enemy역시 사용하므로 이후 리펙토링이 되어야 한다.
	UPROPERTY(EditAnywhere, Category = "Stats")
	EHeroType character_id_;
	
	UFUNCTION(BlueprintCallable)
	void SetAbilityPower(float ability_power) noexcept;
	UFUNCTION(BlueprintCallable)
	void SetAttack(float attack) noexcept;
	UFUNCTION(BlueprintCallable)
	void SetAttackSpeed(float attack_speed) noexcept;
	UFUNCTION(BlueprintCallable)
	void SetHitPoint(float hit_point) noexcept;
	UFUNCTION(BlueprintCallable)
	void SetMagazine(float magazine) noexcept;
	UFUNCTION(BlueprintCallable)
	void SetFireRange(float fire_range) noexcept;
	UFUNCTION(BlueprintCallable)
	void SetMoveSpeed(float move_speed) noexcept;
	UFUNCTION(BlueprintCallable)
	void SetSightRange(float sight_range) noexcept;
	UFUNCTION(BlueprintCallable)
	void SetShield(float shield) noexcept;
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ADamageUI> damage_UI_class_;

	UPROPERTY(VisibleInstanceOnly, Category = Stats, Meta = (AllowPrivateAccess = true))
	FCharacterData stat_;

	UPROPERTY(VisibleInstanceOnly, Category = Stats, meta = (AllowPrivateAccess = true))
	float shield_;

	float max_shield_;
	FTimerHandle shield_timer_;

	float max_hit_points_;

	TArray<FBuff> buffs_;
};
