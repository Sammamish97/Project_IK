/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 09.14.2024
Summary : Source file for Character Stat class.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Project_IK/Public/Components/CharacterStatComponent.h"

#include "Characters/Unit.h"
#include "Managers/DataTableManager.h"
#include "Math/UnrealMathUtility.h"

#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Project_IK/Public/WorldSettings/IKGameInstance.h"
#include "Structs/BuffData.h"
#include "WorldSettings/IKGameModeBase.h"

#include "Structs/CharacterData.h"
#include "Structs/DamageData.h"
// Sets default values
UCharacterStatComponent::UCharacterStatComponent()
	: max_hit_points_(0.f)
{
	PrimaryComponentTick.bCanEverTick = true;

	bWantsInitializeComponent = true;
}

void UCharacterStatComponent::InitializeComponent()
{
	Super::InitializeComponent();
	if (auto ik_game_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		if (UDataTableManager* data_table_manager = ik_game_instance->GetDataTableManager())
		{
			character_data_ = data_table_manager->GetCharacterData(Cast<AUnit>(GetOwner())->GetCharacterType());
		}
		// They are initial data of each attributes. Theoretical limitation will be implemented later
		max_hit_points_ = character_data_.status_data_.hit_point_;
		shield_ = 0.f;
		max_shield_ = 100.f;
	}
}

// Called when the game starts or when spawned
void UCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();
	max_hit_points_ = character_data_.status_data_.hit_point_;
	shield_ = 0.f;
	max_shield_ = 100.f;
}

void UCharacterStatComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	GetWorld()->GetTimerManager().ClearTimer(shield_timer_);
	OnHPChanged.Clear();
	OnHPChangedWithOwner.Clear();
	OnShieldChanged.Clear();
	OnApplyBuff.Clear();
	OnBuffExpired.Clear();
}

// Called every frame
void UCharacterStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunctionoverride)
{
	Super::TickComponent(DELTA, TickType, ThisTickFunctionoverride);
}

bool UCharacterStatComponent::CalcDamage(FDamageData& data_ref)
{
	float evasion_rand = FMath::RandRange(0.f, 1.f);
	bool is_evaded = evasion_rand < GetEvasionRate();

	if (is_evaded)
	{
		return is_evaded;
	}

	float armor = GetArmor();
	data_ref.atk_base_dmg *= 100.f / (100.f + armor);

	// Calculation of shields
	float remaining_damage = data_ref.atk_base_dmg;

	if (shield_ > 0.f)
	{
		float damage_to_shield = FMath::Min(remaining_damage, shield_);
		SetShield(shield_ - damage_to_shield);
		remaining_damage -= damage_to_shield;

		if (shield_ <= 0.f)
		{
			DestroyShield();
			GetWorld()->GetTimerManager().ClearTimer(shield_timer_);
		}
	}

	RecordDamage(data_ref);

	data_ref.atk_base_dmg = remaining_damage;
	return is_evaded;
}

void UCharacterStatComponent::GetDamage(float damage)
{
	SetHitPoint(GetHitPoint() - damage);
}

void UCharacterStatComponent::Heal(float HealAmount)
{
	SetHitPoint(GetHitPoint() + HealAmount);
}

void UCharacterStatComponent::AcquireShield(float ShieldAmount, float Duration)
{
	SetShield(ShieldAmount);
	max_shield_ = ShieldAmount;

	UWorld* world = GetWorld();
	if (world)
	{
		FTimerManager& timer_manager = world->GetTimerManager();
		timer_manager.ClearTimer(shield_timer_);
		timer_manager.SetTimer(shield_timer_, this, &UCharacterStatComponent::DestroyShield, Duration);
	}
}

void UCharacterStatComponent::DestroyShield()
{
	SetShield(0.f);
}

float UCharacterStatComponent::GetAttackPower() const noexcept
{
	return CalculateStat(ECharacterStatType::AttackPower);
}

float UCharacterStatComponent::GetAttackSpeed() const noexcept
{
	return CalculateStat(ECharacterStatType::AttackSpeed);
}

float UCharacterStatComponent::GetCriticalHitRate() const noexcept
{
	return CalculateStat(ECharacterStatType::CriticalHitRate);
}

float UCharacterStatComponent::GetAccuracy() const noexcept
{
	return CalculateStat(ECharacterStatType::Accuracy);
}

float UCharacterStatComponent::GetLifeSteal() const noexcept
{
	return CalculateStat(ECharacterStatType::LifeSteal);
}

float UCharacterStatComponent::GetHitPoint() const noexcept
{
	return CalculateStat(ECharacterStatType::HitPoints);
}

float UCharacterStatComponent::GetMagazineBonus() const noexcept
{
	return CalculateStat(ECharacterStatType::MagazineBonus);
}

float UCharacterStatComponent::GetSightRange() const noexcept
{
	return CalculateStat(ECharacterStatType::SightRange);
}

float UCharacterStatComponent::GetMoveSpeed() const noexcept
{
	return CalculateStat(ECharacterStatType::MoveSpeed);
}

float UCharacterStatComponent::GetEvasionRate() const noexcept
{
	return CalculateStat(ECharacterStatType::EvasionRate);
}

float UCharacterStatComponent::GetArmor() const noexcept
{
	return CalculateStat(ECharacterStatType::Armor);
}

float UCharacterStatComponent::GetSurvivability() const noexcept
{
	return CalculateStat(ECharacterStatType::Survivability);
}

float UCharacterStatComponent::GetSkillPower() const noexcept
{
	return CalculateStat(ECharacterStatType::SkillPower);
}

float UCharacterStatComponent::GetSkillCooldown() const noexcept
{
	return CalculateStat(ECharacterStatType::SkillCoolDown);
}

float UCharacterStatComponent::GetShield() const noexcept
{
	return shield_;
}

void UCharacterStatComponent::SetAttackPower(float attack_power) noexcept
{
	character_data_.status_data_.attack_power_ = attack_power;
}

void UCharacterStatComponent::SetAttackSpeed(float attack_speed) noexcept
{
	character_data_.status_data_.attack_speed_ = attack_speed;
}

void UCharacterStatComponent::SetCriticalHitRate(float critical_hit_rate) noexcept
{
	character_data_.status_data_.critical_hit_rate_= critical_hit_rate;
}

void UCharacterStatComponent::SetAccuracy(float accuracy) noexcept
{
	character_data_.status_data_.accuracy_= accuracy;
}

void UCharacterStatComponent::SetMagazineBonus(float magazine_bonus) noexcept
{
	character_data_.status_data_.magazine_bonus_= magazine_bonus;
}

void UCharacterStatComponent::SetLifeSteal(float life_steal) noexcept
{
	character_data_.status_data_.life_steal_ = life_steal;
}

void UCharacterStatComponent::SetHitPoint(float hit_point) noexcept
{
	character_data_.status_data_.hit_point_ = FMath::Min(hit_point, GetMaxHitPoint());
	OnHPChanged.Broadcast(GetHPRatio());
	OnHPOrShieldChanged.Broadcast(GetHitPoint(), GetShield());
	OnHPChangedWithOwner.Broadcast(GetHPRatio(), GetOwner());
	if (character_data_.status_data_.hit_point_ < KINDA_SMALL_NUMBER)
	{
		character_data_.status_data_.hit_point_ = 0.f;
		Cast<AUnit>(GetOwner())->Die();
	}
}

void UCharacterStatComponent::SetEvasionRate(float evasion_rate) noexcept
{
	character_data_.status_data_.evasion_rate_= evasion_rate;
}

void UCharacterStatComponent::SetArmor(float armor) noexcept
{	OnHPChanged.Broadcast(GetHPRatio());

	character_data_.status_data_.armor_= armor;
}

void UCharacterStatComponent::SetSurvivability(float survivability) noexcept
{
	character_data_.status_data_.survivability_ = survivability;
}

void UCharacterStatComponent::SetSightRange(float sight_range) noexcept
{
	character_data_.sight_range_ = sight_range;
}

void UCharacterStatComponent::SetMoveSpeed(float move_speed) noexcept
{
	character_data_.move_speed_ = move_speed;
}

void UCharacterStatComponent::SetSkillPower(float skill_power) noexcept
{
	character_data_.status_data_.skill_power_= skill_power;
}

void UCharacterStatComponent::SetSkillCooldown(float skill_cooldown) noexcept
{
	character_data_.status_data_.skill_cool_down_= skill_cooldown;
}

void UCharacterStatComponent::SetShield(float shield) noexcept
{
	shield_ = shield;
	OnShieldChanged.Broadcast(GetShieldRatio());
	OnHPOrShieldChanged.Broadcast(GetHitPoint(), GetShield());
}

void UCharacterStatComponent::RecordDamage(FDamageData& data_ref)
{
	if (data_ref.attacker.IsValid())
	{
		AIKGameModeBase* game_mode = Cast<AIKGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
		// @@ TODO: Record atk&skill dmg differently.
		game_mode->RecordDamage(data_ref.atk_base_dmg, data_ref.attacker);
		game_mode->RecordDamage(data_ref.skill_power_base_dmg, data_ref.attacker);
	}
}

float UCharacterStatComponent::GetHPRatio() const noexcept
{	// Don't calculate buffs because it calculates RATIO. The number caused by buffs will be simplified.
	if (max_hit_points_ < KINDA_SMALL_NUMBER)
	{
		return 0.f;
	}
	else
	{
		return character_data_.status_data_.hit_point_ / max_hit_points_;
	}
}

float UCharacterStatComponent::GetShieldRatio() const noexcept
{
	if (max_shield_ < KINDA_SMALL_NUMBER)
	{
		return 0.f;
	}
	else
	{
		return shield_ / max_shield_;
	}
}

float UCharacterStatComponent::GetMaxHitPoint() const noexcept
{
	float stat = max_hit_points_;
	float percentage_bonus = 0.f;
	float value_bonus = 0.f;

	for(const auto& buff_pair : buffs_)
	{
		const auto& buff_stats = buff_pair.Value.buff_status_;
		for (const auto& buff : buff_stats)
		{
			if (buff.stat_type_ == ECharacterStatType::HitPoints)
			{
				if (buff.is_percentage_)
				{
					percentage_bonus += buff.value_;
				}
				else
				{
					value_bonus += buff.value_;
				}
			}
		}
	}
	
	return (stat + value_bonus) * (1.f + percentage_bonus);
}

float UCharacterStatComponent::GetMaxShield() const noexcept
{
	float stat = max_shield_;
	float percentage_bonus = 0.f;
	float value_bonus = 0.f;

	for(const auto& buff_pair : buffs_)
	{
		const auto& buff_stats = buff_pair.Value.buff_status_;
		for (const auto& buff : buff_stats)
		{
			if (buff.stat_type_ == ECharacterStatType::Shield)
			{
				if (buff.is_percentage_)
				{
					percentage_bonus += buff.value_;
				}
				else
				{
					value_bonus += buff.value_;
				}
			}
		}
	}

	return (stat + value_bonus) * (1.f + percentage_bonus);
}

FCharacterData UCharacterStatComponent::GetCharacterData() const noexcept
{
	return character_data_;
}

void UCharacterStatComponent::SetCharacterData(const FCharacterData& character_data) noexcept
{
	character_data_ = character_data;
	OnHPChanged.Broadcast(GetHPRatio());
	OnHPOrShieldChanged.Broadcast(GetHitPoint(), GetShield());
	OnHPChangedWithOwner.Broadcast(GetHPRatio(), GetOwner());
}

float UCharacterStatComponent::CalculateStat(ECharacterStatType StatType) const
{
	float stat = GetBaseStat(StatType);

	float percentage_bonus = 1.f;
	float value_bonus = 0.f;

	for(const auto& buff_pair : buffs_)
	{
		const auto& buff_stats = buff_pair.Value.buff_status_;
		for (const auto& buff : buff_stats)
		{
			if (buff.stat_type_ == StatType)
			{
				if (buff.is_percentage_)
				{
					percentage_bonus += buff.value_;
				}
				else
				{
					value_bonus += buff.value_;
				}
			}
		}
	}

	return (stat + value_bonus) * percentage_bonus;
}

float UCharacterStatComponent::GetBaseStat(ECharacterStatType StatType) const
{
	switch (StatType)
	{
		case ECharacterStatType::SightRange:
			return character_data_.sight_range_;
		case ECharacterStatType::MoveSpeed:
			return character_data_.move_speed_;
	}
	return character_data_.status_data_[StatType];
}

void UCharacterStatComponent::ApplyBuff(FBuffData buff_data)
{
	//새로운 버프라면 타이머 역시 새로 생성.
	EBuffType buff_type = buff_data.buff_type_;
	if(buffs_.Contains(buff_type) == false)
	{
		buff_timers_.Add(buff_type, FTimerHandle());
	}

	if(buff_data.is_permanent_ == false)
	{
		FTimerDelegate expired_delegate = FTimerDelegate::CreateUObject(this, &UCharacterStatComponent::RemoveBuff, buff_data);
		GetWorld()->GetTimerManager().SetTimer(buff_timers_[buff_data.buff_type_], expired_delegate, buff_data.duration_, false);
	}
	
	if(buff_data.is_invisible_ == false)
	{
		OnApplyBuff.Broadcast(buff_data);
	}
	buffs_.Add(buff_type, buff_data);
}

void UCharacterStatComponent::PostInitBuffBroadCast()
{
	for(const auto& elem : buffs_)
	{
		if(elem.Value.is_invisible_ == false)
		{
			OnApplyBuff.Broadcast(elem.Value);
		}
	}
}

void UCharacterStatComponent::RemoveBuff(FBuffData buff_data)
{
	buffs_.Remove(buff_data.buff_type_);
	buff_timers_.Remove(buff_data.buff_type_);
	if(buff_data.is_invisible_ == false)
	{
		OnBuffExpired.Broadcast(buff_data);
	}
}
