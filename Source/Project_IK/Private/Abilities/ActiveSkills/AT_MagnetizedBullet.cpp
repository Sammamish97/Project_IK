/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 04.17.2025
Summary : Source file for Magnetized Bullet Active Skill.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "Abilities/ActiveSkills/AT_MagnetizedBullet.h"

#include "Characters/HeroBase.h"
#include "Components/WeaponMechanics.h"

UAT_MagnetizedBullet::UAT_MagnetizedBullet()
{
	target_param_ = FTargetParameters(ETargetingMode::Actor, ETargetType::Allies, 1000.f);
	cool_time_ = 5.f;
	duration_ = 2.f;
}

bool UAT_MagnetizedBullet::ActivateSkill_Implementation(const FTargetResult& TargetResult)
{
	//1. 지속시간동안 다음의 효과를 일으켜야 함
		//a. 총알이 3명의 적에게 도탄 되어야 함.
		//b. 총알을 맞은 적은 추가 데미지와 함께 스택이 쌓임.
		//c. 스택이 n스택이 되면 터지면서 효과 발생.
	TWeakObjectPtr<AHeroBase> owner_hero_ptr = Cast<AHeroBase>(skill_owner_);
	if (auto hero = owner_hero_ptr.Get())
	{
		auto weapon_mechanics_cache = hero->GetWeaponMechanics();
		//weapon_mechanics_cache->
		return true;
	}
	return false;
}
