/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 09.14.2024
Summary : Source file for Character Stat class.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Project_IK/Public/Components/CharacterStatComponent.h"

#include "Math/UnrealMathUtility.h"

#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Project_IK/Public/WorldSettings/IKGameInstance.h"
#include "WorldSettings/IKGameModeBase.h"

#include "UI/DamageUI.h"
#include "Components/ObjectPoolComponent.h"

#include "Managers/CharacterDataManager.h"
#include "Structs/CharacterData.h"
#include "Structs/DamageData.h"


// Sets default values
UCharacterStatComponent::UCharacterStatComponent()
	: character_id_(EHeroType::Hero1), max_hit_points_(0.f)
{
	PrimaryComponentTick.bCanEverTick = true;

	bWantsInitializeComponent = true;
}

void UCharacterStatComponent::InitializeComponent()
{
	Super::InitializeComponent();

	auto ik_game_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (ik_game_instance)
	{
		FCharacterData* character_data = ik_game_instance->GetCharacterDataManager()->GetCharacterData(character_id_);

		stat_.ability_power_ = character_data->ability_power_;
		stat_.attack_ = character_data->attack_;
		stat_.attack_speed_ = character_data->attack_speed_;
		stat_.hit_point_ = character_data->hit_point_;
		stat_.magazine_ = character_data->magazine_;

		stat_.fire_range_ = character_data->fire_range_;
		stat_.move_speed_ = character_data->move_speed_;
		stat_.sight_range_ = character_data->sight_range_;


		// They are initial data of each attributes. Theoretical limitation will be implemented later
		max_hit_points_ = stat_.hit_point_;
		shield_ = 0.f;
		max_shield_ = 100.f;
	}
}

// Called when the game starts or when spawned
void UCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCharacterStatComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorld()->GetTimerManager().ClearTimer(shield_timer_);

	Die.Clear();
	OnHPChanged.Clear();
	OnShieldChanged.Clear();
	OnBuffChanged.Clear();
}

// Called every frame
void UCharacterStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunctionoverride)
{
	Super::TickComponent(DELTA, TickType, ThisTickFunctionoverride);

	for (FBuff& buff : buffs_)
	{
		if (buff.is_permanent_)
		{
			continue;
		}
		buff.time_remaining_ -= DeltaTime;
	}

	int32 num_removed = buffs_.RemoveAll([](const FBuff& buff)
		{
			return buff.is_permanent_ == false && buff.time_remaining_ <= 0.f;
		});

	if (num_removed > 0)
	{
		OnBuffChanged.Broadcast();
	}
}

bool UCharacterStatComponent::CalcDamage(FDamageData& data_ref)
{
	float evasion_rand = FMath::RandRange(0.f, 1.f);
	bool is_evaded = evasion_rand < GetEvasion();

	if (!is_evaded && data_ref.attacker.IsValid())
	{
		AIKGameModeBase* game_mode = Cast<AIKGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
		game_mode->RecordDamage(data_ref.damage, data_ref.attacker);
	}

	if (is_evaded)
	{
		return is_evaded;
	}

	// Calculation of shields
	float remaining_damage = data_ref.damage;

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
	data_ref.damage = remaining_damage;
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

float UCharacterStatComponent::GetAbilityPower() const noexcept
{
	return CalculateStat(ECharacterStatType::AbillityPower);
}

float UCharacterStatComponent::GetAttack() const noexcept
{
	return CalculateStat(ECharacterStatType::Attack);
}

float UCharacterStatComponent::GetAttackSpeed() const noexcept
{
	return CalculateStat(ECharacterStatType::AttackSpeed);
}

float UCharacterStatComponent::GetHitPoint() const noexcept
{
	return CalculateStat(ECharacterStatType::HitPoints);
}

float UCharacterStatComponent::GetMagazine() const noexcept
{
	return CalculateStat(ECharacterStatType::Magazine);
}

float UCharacterStatComponent::GetFireRange() const noexcept
{
	return CalculateStat(ECharacterStatType::FireRange);
}

float UCharacterStatComponent::GetMoveSpeed() const noexcept
{
	return CalculateStat(ECharacterStatType::MoveSpeed);
}

float UCharacterStatComponent::GetSightRange() const noexcept
{
	return CalculateStat(ECharacterStatType::SightRange);
}

float UCharacterStatComponent::GetEvasion() const noexcept
{
	return CalculateStat(ECharacterStatType::Evasion);
}

float UCharacterStatComponent::GetShield() const noexcept
{
	return CalculateStat(ECharacterStatType::Shield);
}

void UCharacterStatComponent::SetAbilityPower(float ability_power) noexcept
{
	stat_.ability_power_ = ability_power;
}

void UCharacterStatComponent::SetAttack(float attack) noexcept
{
	stat_.attack_ = attack;
}

void UCharacterStatComponent::SetAttackSpeed(float attack_speed) noexcept
{
	stat_.attack_speed_ = attack_speed;
}

void UCharacterStatComponent::SetHitPoint(float hit_point) noexcept
{
	stat_.hit_point_ = FMath::Min(hit_point, GetMaxHitPoint());

	OnHPChanged.Broadcast();
	if (stat_.hit_point_ < KINDA_SMALL_NUMBER)
	{
		stat_.hit_point_ = 0.f;
		Die.Broadcast();
	}
}

void UCharacterStatComponent::SetMagazine(float magazine) noexcept
{
	stat_.magazine_ = magazine;
}

void UCharacterStatComponent::SetFireRange(float fire_range) noexcept
{
	stat_.fire_range_ = fire_range;
}

void UCharacterStatComponent::SetMoveSpeed(float move_speed) noexcept
{
	stat_.move_speed_ = move_speed;
}

void UCharacterStatComponent::SetSightRange(float sight_range) noexcept
{
	stat_.sight_range_ = sight_range;
}

void UCharacterStatComponent::SetShield(float shield) noexcept
{
	shield_ = shield;
	OnShieldChanged.Broadcast();
}

float UCharacterStatComponent::GetHPRatio() const noexcept
{	// Don't calculate buffs because it calculates RATIO. The number caused by buffs will be simplified.
	if (max_hit_points_ < KINDA_SMALL_NUMBER)
	{
		return 0.f;
	}
	else
	{
		return stat_.hit_point_ / max_hit_points_;
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

	for (const FBuff& buff : buffs_)
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

	return (stat + value_bonus) * (1.f + percentage_bonus);
}

float UCharacterStatComponent::GetMaxShield() const noexcept
{
	float stat = max_shield_;
	float percentage_bonus = 0.f;
	float value_bonus = 0.f;

	for (const FBuff& buff : buffs_)
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

	return (stat + value_bonus) * (1.f + percentage_bonus);
}

FCharacterData UCharacterStatComponent::GetCharacterData() const noexcept
{
	return stat_;
}

void UCharacterStatComponent::SetCharacterData(const FCharacterData& character_data) noexcept
{
	stat_ = character_data;
	OnHPChanged.Broadcast();
}

float UCharacterStatComponent::CalculateStat(ECharacterStatType StatType) const
{
	float stat = GetBaseStat(StatType);

	float percentage_bonus = 1.f;
	float value_bonus = 0.f;

	for (const FBuff& buff : buffs_)
	{
		if (buff.stat_type_ == StatType)
		{
			if (buff.is_percentage_)
			{
				percentage_bonus *= buff.value_;
			}
			else
			{
				value_bonus += buff.value_;
			}
		}
	}

	return (stat + value_bonus) * percentage_bonus;
}

float UCharacterStatComponent::GetBaseStat(ECharacterStatType StatType) const
{
	switch (StatType)
	{
	case ECharacterStatType::AbillityPower:
		return stat_.ability_power_;
		break;
	case ECharacterStatType::Attack:
		return stat_.attack_;
		break;
	case ECharacterStatType::AttackSpeed:
		return stat_.attack_speed_;
		break;
	case ECharacterStatType::HitPoints:
		return stat_.hit_point_;
		break;
	case ECharacterStatType::Magazine:
		return stat_.magazine_;
		break;
	case ECharacterStatType::FireRange:
		return stat_.fire_range_;
		break;
	case ECharacterStatType::MoveSpeed:
		return stat_.move_speed_;
		break;
	case ECharacterStatType::SightRange:
		return stat_.sight_range_;
		break;
	case ECharacterStatType::Evasion:
		return stat_.evasion_;
	case ECharacterStatType::Shield:
		return shield_;
	default:
		break;
	}
	return 0.f;
}

void UCharacterStatComponent::ApplyBuff(FBuff buff)
{
	buffs_.Add(buff);
	OnBuffChanged.Broadcast();
}

bool UCharacterStatComponent::RemoveBuff(FName BuffName)
{
	int32 found_index = buffs_.IndexOfByPredicate([BuffName](const FBuff& buff) {
		return buff.buff_name_ == BuffName;
		});

	if (found_index != INDEX_NONE)
	{
		buffs_.RemoveAt(found_index);
		OnBuffChanged.Broadcast();
		return true;
	}

	return false;
}

TArray<FBuff> UCharacterStatComponent::GetBuffs() const
{
	return buffs_;
}
