/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 09.14.2024
Summary : Source file for Character Stat class.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Project_IK/Public/Components/CharacterStatComponent.h"

#include "Managers/DataTableManager.h"
#include "Math/UnrealMathUtility.h"

#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Project_IK/Public/WorldSettings/IKGameInstance.h"
#include "WorldSettings/IKGameModeBase.h"

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
		FCharacterData* character_data = nullptr;
		if (UDataTableManager* data_table_manager = ik_game_instance->GetDataTableManager())
		{
			character_data = data_table_manager->GetCharacterData(character_id_);
		}
		//TODO: nullptr를 참조할 수 있다...!
		stat_= *character_data;


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

	if (data_ref.attacker.IsValid())
	{
		AIKGameModeBase* game_mode = Cast<AIKGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
		game_mode->RecordDamage(data_ref.atk_base_dmg, data_ref.attacker);
	}

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
	return CalculateStat(ECharacterStatType::Shield);
}

void UCharacterStatComponent::SetAttackPower(float attack_power) noexcept
{
	stat_.attack_power_ = attack_power;
}

void UCharacterStatComponent::SetAttackSpeed(float attack_speed) noexcept
{
	stat_.attack_speed_ = attack_speed;
}

void UCharacterStatComponent::SetCriticalHitRate(float critical_hit_rate) noexcept
{
	stat_.critical_hit_rate_= critical_hit_rate;
}

void UCharacterStatComponent::SetAccuracy(float accuracy) noexcept
{
	stat_.accuracy_= accuracy;
}

void UCharacterStatComponent::SetMagazineBonus(float magazine_bonus) noexcept
{
	stat_.magazine_bonus_= magazine_bonus;
}

void UCharacterStatComponent::SetLifeSteal(float life_steal) noexcept
{
	stat_.life_steal_ = life_steal;
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

void UCharacterStatComponent::SetEvasionRate(float evasion_rate) noexcept
{
	stat_.evasion_rate_= evasion_rate;
}

void UCharacterStatComponent::SetArmor(float armor) noexcept
{
	stat_.armor_= armor;
}

void UCharacterStatComponent::SetSurvivability(float survivability) noexcept
{
	stat_.survivability_ = survivability;
}

void UCharacterStatComponent::SetMoveSpeed(float move_speed) noexcept
{
	stat_.move_speed_ = move_speed;
}

void UCharacterStatComponent::SetSkillPower(float skill_power) noexcept
{
	stat_.skill_power_= skill_power;
}

void UCharacterStatComponent::SetSkillCooldown(float skill_cooldown) noexcept
{
	stat_.skill_cool_down_= skill_cooldown;
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
	case ECharacterStatType::AttackPower:
		return stat_.attack_power_;
		break;
	case ECharacterStatType::AttackSpeed:
		return stat_.attack_speed_;
		break;
	case ECharacterStatType::CriticalHitRate:
		return stat_.critical_hit_rate_;
		break;
	case ECharacterStatType::Accuracy:
		return stat_.accuracy_;
		break;
	case ECharacterStatType::MagazineBonus:
		return stat_.magazine_bonus_;
		break;
	case ECharacterStatType::LifeSteal:
		return stat_.life_steal_;
		break;
	case ECharacterStatType::HitPoints:
		return stat_.hit_point_;
		break;
	case ECharacterStatType::EvasionRate:
		return stat_.evasion_rate_;
		break;
	case ECharacterStatType::Armor:
		return stat_.armor_;
		break;
	case ECharacterStatType::Survivability:
		return stat_.survivability_;
		break;
	case ECharacterStatType::SightRange:
		return stat_.sight_range_;
		break;
	case ECharacterStatType::MoveSpeed:
		return stat_.move_speed_;
		break;
	case ECharacterStatType::SkillPower:
		return stat_.skill_power_;
		break;
	case ECharacterStatType::SkillCoolDown:
		return stat_.skill_cool_down_;
		break;
	case ECharacterStatType::Shield:
		return shield_;
		break;
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
