/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 3.8.2025
Summary : Header file for the Status Data.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once
#include "CoreMinimal.h"
#include "Managers/EnumCluster.h"
#include "StatusData.generated.h"
USTRUCT(BlueprintType)
struct PROJECT_IK_API FStatusData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category = "AttackData")
	float attack_power_ = 0.f;
	UPROPERTY(EditAnywhere, Category = "AttackData")
	float attack_speed_ = 0.f;
	UPROPERTY(EditAnywhere, Category = "AttackData")
	float critical_hit_rate_ = 0.f;
	UPROPERTY(EditAnywhere, Category = "AttackData")
	float accuracy_ = 0.f;
	
	UPROPERTY(EditAnywhere, Category = "AttackData")
	float magazine_bonus_ = 0.f;
	UPROPERTY(EditAnywhere, Category = "AttackData")
	float reload_speed_bonus_ = 0.f;
	
	UPROPERTY(EditAnywhere, Category = "AttackData")
	float life_steal_ = 0.f;

	UPROPERTY(EditAnywhere, Category = "DefenseData")
	float hit_point_ = 0.f;
	UPROPERTY(EditAnywhere, Category = "DefenseData")
	float evasion_rate_ = 0.f;
	UPROPERTY(EditAnywhere, Category = "DefenseData")
	float armor_ = 0.f;
	UPROPERTY(EditAnywhere, Category = "DefenseData")
	float survivability_ = 0.f;

	UPROPERTY(EditAnywhere, Category = "SkillData")
	float skill_power_ = 0.f;
	UPROPERTY(EditAnywhere, Category = "SkillData")
	float skill_cool_down_ = 0.f;
	
	const float& operator[] (ECharacterStatType rhs) const
	{
		switch (rhs)
		{
		case ECharacterStatType::AttackPower:
			return attack_power_;
		case ECharacterStatType::AttackSpeed:
			return attack_speed_;
		case ECharacterStatType::CriticalHitRate:
			return critical_hit_rate_;
		case ECharacterStatType::Accuracy:
			return accuracy_;
		case ECharacterStatType::MagazineBonus:
			return magazine_bonus_;
		case ECharacterStatType::ReloadSpeedBonus:
			return reload_speed_bonus_;
		case ECharacterStatType::LifeSteal:
			return life_steal_;
			
		case ECharacterStatType::HitPoints:
			return hit_point_;
		case ECharacterStatType::EvasionRate:
			return evasion_rate_;
		case ECharacterStatType::Armor:
			return armor_;
		case ECharacterStatType::Survivability:
			return survivability_;
			
		case ECharacterStatType::SkillPower:
			return skill_power_;
		case ECharacterStatType::SkillCoolDown:
			return skill_cool_down_;
			
		default:
			checkNoEntry()
			return survivability_;
		}
	}

	float& operator[] (ECharacterStatType rhs)
	{
		return const_cast<float&>(const_cast<const FStatusData*>(this)->operator[](rhs));
	}
	
	FStatusData operator+(const FStatusData& rhs)
	{
		FStatusData result = *this;
		
		result.attack_power_ += rhs.attack_power_;
		result.attack_speed_ += rhs.attack_speed_;
		result.critical_hit_rate_ += rhs.critical_hit_rate_;
		result.accuracy_ += rhs.accuracy_;
		result.magazine_bonus_ += rhs.magazine_bonus_;
		result.life_steal_ += rhs.life_steal_;

		result.hit_point_ += rhs.hit_point_;
		result.evasion_rate_ += rhs.evasion_rate_;
		result.armor_ += rhs.armor_;
		result.survivability_ += rhs.survivability_;
		
		result.skill_power_ += rhs.skill_power_;
		result.skill_cool_down_ += rhs.skill_cool_down_;
		
		return result;
	}
	
	FStatusData& operator+=(const FStatusData& rhs)
	{
		(*this) = (*this) + rhs;
		return (*this);
	}
};
