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
#include "Components/BulletChainEffectComponent.h"
#include "Components/WeaponMechanics.h"
#include "Weapons/Guns/GunBase.h"

UAT_MagnetizedBullet::UAT_MagnetizedBullet()
{
	target_param_ = FTargetParameters(ETargetingMode::Actor, ETargetType::Allies, 0.f, 0.f, true);
	cool_time_ = 5.f;
	duration_ = 3.f;
}

bool UAT_MagnetizedBullet::ActivateSkill(const FTargetResult& TargetResult)
{
	//1. 지속시간동안 다음의 효과를 일으켜야 함
		//a. 총알이 3명의 적에게 도탄 되어야 함.
		//b. 총알을 맞은 적은 추가 데미지와 함께 스택이 쌓임.
		//c. 스택이 n스택이 되면 터지면서 효과 발생.
	AHeroBase* hero = Cast<AHeroBase>(skill_owner_);
	if (hero)
	{
		auto weapon_actor = hero->GetWeaponMechanics()->GetWeaponActor();
		weapon_actor->AddOnHitComponent(UBulletChainEffectComponent::StaticClass());
		weapon_actor->AttachParticleEffect(skill_particle_system_);
		weapon_actor->AddParticleParameterFloat(skill_particle_system_, FName("SphereRadius"), 10.f);
		weapon_actor->AddParticleParameterVector(skill_particle_system_, FName("BulletVelocity"), hero->GetActorForwardVector());
		weapon_actor->ApplyMaterial(skill_bullet_material_);


		FTimerDelegate timer_delegate = FTimerDelegate::CreateUObject(this, &UAT_MagnetizedBullet::OnFinishSkill);
		GetWorld()->GetTimerManager().SetTimer(duration_timer_handle_, timer_delegate, duration_, false);
		return true;
	}
	return false;
}

void UAT_MagnetizedBullet::OnFinishSkill()
{
	TWeakObjectPtr<AHeroBase> owner_hero_ptr = Cast<AHeroBase>(skill_owner_);
	if (auto hero = owner_hero_ptr.Get())
	{
		auto weapon_actor = hero->GetWeaponMechanics()->GetWeaponActor();
		weapon_actor->RemoveOnHitComponent(UBulletChainEffectComponent::StaticClass());
		weapon_actor->RemoveParticleEffect(skill_particle_system_);
		weapon_actor->RemoveMaterial(skill_bullet_material_);
		GetWorld()->GetTimerManager().ClearTimer(duration_timer_handle_);
	}
}