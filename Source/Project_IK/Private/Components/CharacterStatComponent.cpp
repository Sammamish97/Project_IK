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
#include "Characters/EnemyBase.h"
#include "Managers/DataTableManager.h"
#include "Math/UnrealMathUtility.h"

#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Project_IK/Public/WorldSettings/IKGameInstance.h"
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
			SetCharacterData(data_table_manager->GetCharacterData(Cast<AUnit>(GetOwner())->GetCharacterType()));
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
}

//만약 유닛 생성 시, 데이터 에셋에 있는 character stat에 상황에 따라 추가적인 값을 더하고 싶다면 유닛을 생성후 이 함수를 통해 조정한다.
void UCharacterStatComponent::ApplyExtraStatusForSummoned(const FStatusData& status)
{
	character_data_.status_data_ += status;
	max_hit_points_ = character_data_.status_data_.hit_point_;
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
	data_ref.atk_base_dmg_ *= 100.f / (100.f + armor);

	// Calculation of shields
	float remaining_atk_damage = data_ref.atk_base_dmg_;
	float remaining_skill_damage = data_ref.skill_power_base_dmg_;

	float shield = GetShield();
	if (shield > 0.f)
	{
		float skill_damage_to_shield = FMath::Min(remaining_skill_damage, shield);
		shield -= skill_damage_to_shield;
		remaining_skill_damage -= skill_damage_to_shield;

		float atk_damage_to_shield = FMath::Min(remaining_atk_damage, shield);
		shield -= atk_damage_to_shield;
		remaining_atk_damage -= atk_damage_to_shield;

		if (shield <= 0.f)
		{
			DestroyShield();
		}
		else
		{
			SetShield(shield);
		}
	}

	float hp = GetHitPoint();
	data_ref.atk_base_dmg_ = FMath::Min(remaining_atk_damage, hp);
	data_ref.skill_power_base_dmg_ = FMath::Min(remaining_skill_damage, hp - data_ref.atk_base_dmg_);

	RecordDamage(data_ref);
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
	GetWorld()->GetTimerManager().ClearTimer(shield_timer_);
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

float UCharacterStatComponent::GetReloadSpeedBonus() const noexcept
{
	return CalculateStat(ECharacterStatType::ReloadSpeedBonus);
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
	// Return immediately to prevent multiple Die event dispatches.
	if (character_data_.status_data_.hit_point_ <= 0.f)
	{
		return;
	}
	// Calculations became complex because of buffs.
	const float hp_ratio = FMath::Min(hit_point / GetMaxHitPoint(), 1.f);
	character_data_.status_data_.hit_point_ = max_hit_points_ * hp_ratio;
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
{
	OnHPChanged.Broadcast(GetHPRatio());
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
	// Calculations became complex because of buffs.
	const float shield_ratio = FMath::Min(shield / GetMaxShield(), 1.f);
	shield_ = max_shield_ * shield_ratio;
	OnShieldChanged.Broadcast(GetShieldRatio());
	OnHPOrShieldChanged.Broadcast(GetHitPoint(), GetShield());
}

void UCharacterStatComponent::RecordDamage(FDamageData& data_ref)
{
	AActor* attack_target = data_ref.attack_target_.Get();
	// Record damage if and only if the attack target is enemy.
	if (data_ref.attacker_.IsValid() && attack_target && attack_target->IsA<AEnemyBase>())
	{
		AIKGameModeBase* game_mode = Cast<AIKGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

		// @@ TODO: Record atk&skill dmg differently.
		game_mode->RecordDamage(data_ref.atk_base_dmg_, data_ref.attacker_);
		game_mode->RecordDamage(data_ref.skill_power_base_dmg_, data_ref.attacker_);
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
	float percentage_bonus = 1.f;
	float value_bonus = 0.f;

	for (const auto& elem : buffs_)
	{
		if (elem.Value.Contains(ECharacterStatType::HitPoints))
		{
			FBuffStatusData stat_data = elem.Value[ECharacterStatType::HitPoints];
			if (stat_data.is_percentage_)
			{
				percentage_bonus += stat_data.value_;
			}
			else
			{
				value_bonus += stat_data.value_;
			}
		}
	}
	return (stat + value_bonus) * (percentage_bonus);	
}

float UCharacterStatComponent::GetMaxShield() const noexcept
{
	float stat = max_shield_;
	float percentage_bonus = 1.f;
	float value_bonus = 0.f;

	for (const auto& elem : buffs_)
	{
		if (elem.Value.Contains(ECharacterStatType::Shield))
		{
			FBuffStatusData stat_data = elem.Value[ECharacterStatType::Shield];
			if (stat_data.is_percentage_)
			{
				percentage_bonus += stat_data.value_;
			}
			else
			{
				value_bonus += stat_data.value_;
			}
		}
	}
	return (stat + value_bonus) * (percentage_bonus);
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

	for (const auto& elem : buffs_)
	{
		if (elem.Value.Contains(StatType))
		{
			FBuffStatusData stat_data = elem.Value[StatType];
			if (stat_data.is_percentage_)
			{
				percentage_bonus += stat_data.value_;
			}
			else
			{
				value_bonus += stat_data.value_;
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
		case ECharacterStatType::Shield:
			return shield_;
	}
	return character_data_.status_data_[StatType];
}

void UCharacterStatComponent::ApplyBuff(EBuffType buff_type, FBuffStatusData status_data)
{
	RemoveBuff(buff_type, status_data.stat_type_);
	if (status_data.is_permanent_ == false)
	{
		auto& type_timer_map = buff_timers_.FindOrAdd(buff_type);
		auto& timer_handle = type_timer_map.FindOrAdd(status_data.stat_type_);
	
		FTimerDelegate expired_delegate = FTimerDelegate::CreateUObject(this, &UCharacterStatComponent::RemoveBuff, buff_type, status_data.stat_type_);
		GetWorld()->GetTimerManager().SetTimer(timer_handle, expired_delegate, status_data.duration_, false);
	}
	buffs_.FindOrAdd(buff_type).FindOrAdd(status_data.stat_type_, status_data);
}

void UCharacterStatComponent::RemoveBuff(EBuffType buff_type)
{
	buffs_.Remove(buff_type);
	if (buff_timers_.Contains(buff_type))
	{
		for (auto& buff_pair : buff_timers_[buff_type])
		{
			GetWorld()->GetTimerManager().ClearTimer(buff_pair.Value);
		}
	}
	buff_timers_.Remove(buff_type);
}

void UCharacterStatComponent::RemoveBuff(EBuffType buff_type, ECharacterStatType stat_type)
{
	if (buffs_.Contains(buff_type) && buff_timers_.Contains(buff_type))
	{
		if (buffs_[buff_type].Contains(stat_type) && buff_timers_[buff_type].Contains(stat_type))
		{
			buffs_[buff_type].Remove(stat_type);
			GetWorld()->GetTimerManager().ClearTimer(buff_timers_[buff_type][stat_type]);
			buff_timers_[buff_type].Remove(stat_type);
		}
	}
}