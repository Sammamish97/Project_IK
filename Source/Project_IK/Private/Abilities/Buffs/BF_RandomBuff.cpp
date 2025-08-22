/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 08.02.2025
Summary : Source file for a random status buff.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Abilities/Buffs/BF_RandomBuff.h"
#include "Characters/Unit.h"
#include "Structs/BuffStatusData.h"

void UBF_RandomBuff::ApplyBuff(AUnit* target)
{
	Super::ApplyBuff(target);

	FBuffStatusData buff = GetRandomBuff();
	buff.duration_ = duration_;
	buff.is_permanent_ = is_permanent_;

	target->ApplyStatusBuff(buff_type_, buff);
	if (is_permanent_)
	{
		target->AddBuffUI(buff_type_, display_data_);
	}
	else
	{
		target->AddBuffUI(buff_type_, display_data_, duration_);
	}
}

void UBF_RandomBuff::RemoveBuff(AUnit* target)
{
	Super::RemoveBuff(target);
}

FBuffStatusData UBF_RandomBuff::GetRandomBuff() const
{
	FBuffStatusData data;

	data.stat_type_ = GetRandomStatType();
	GetRandomStatValue(data);

	return data;
}

inline ECharacterStatType UBF_RandomBuff::GetRandomStatType() const
{
	return static_cast<ECharacterStatType>(FMath::RandRange(
		static_cast<int32>(ECharacterStatType::AttackPower),
		static_cast<int32>(ECharacterStatType::SkillCoolDown)
	));
}

void UBF_RandomBuff::GetRandomStatValue(FBuffStatusData buff_data) const
{
	switch (buff_data.stat_type_)
	{
		// Works with percentage calculations
	case ECharacterStatType::AttackPower:
	case ECharacterStatType::AttackSpeed:
	case ECharacterStatType::Accuracy: // Not used yet
	case ECharacterStatType::HitPoints:
	case ECharacterStatType::SightRange:
	case ECharacterStatType::MoveSpeed: // Not used yet
		buff_data.value_ = FMath::RandRange(0.1f, 0.3f);
		buff_data.is_percentage_ = true;
		break;
	case ECharacterStatType::CriticalHitRate: // 0~1
	case ECharacterStatType::ReloadSpeedBonus: // 0~1
	case ECharacterStatType::LifeSteal: // 0~1
	case ECharacterStatType::EvasionRate: // 0~1
		buff_data.value_ = FMath::RandRange(0.1f, 0.3f);
		buff_data.is_percentage_ = false;
		break;
	case ECharacterStatType::MagazineBonus: // 0~10
		buff_data.value_ = FMath::RandRange(1, 10);
		buff_data.is_percentage_ = false;
		break;
	case ECharacterStatType::SkillPower: // 0~100
	case ECharacterStatType::SkillCoolDown: // 0~100
	case ECharacterStatType::Armor: // 0~100 or more
		buff_data.value_ = FMath::RandRange(10, 50);
		buff_data.is_percentage_ = false;
		break;
	default:
		break;
	}

	if (!is_negative_value_)
	{
		buff_data.value_ *= -1.f;
	}
}
