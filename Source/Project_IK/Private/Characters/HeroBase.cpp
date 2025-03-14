/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.20.2024
Summary : Source file for hero base.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Characters/HeroBase.h"

#include "Abilities/SkillContainer.h"
#include "AI/GunnerAIController.h"
#include "Components/EquipMechanics.h"
#include "Components/CapsuleComponent.h"
#include "Components/CharacterStatComponent.h"
#include "Components/OopartMechanics.h"
#include "Components/PassiveSkillMechanics.h"
#include "Components/WeaponMechanics.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "WorldSettings/IKGameModeBase.h"

AHeroBase::AHeroBase()
{
	skill_container_ = CreateDefaultSubobject<USkillContainer>(TEXT("SkillContainer"));
	weapon_mechanics_ = CreateDefaultSubobject<UWeaponMechanics>(TEXT("WeaponMechanics"));
	passive_skill_mechanics_ = CreateDefaultSubobject<UPassiveSkillMechanics>(TEXT("PassiveMechanics"));
	equip_mechanics_ = CreateDefaultSubobject<UEquipMechanics>(TEXT("EquipMechanics"));
	oopart_mechanics_ = CreateDefaultSubobject<UOopartMechanics>(TEXT("OopartMechanics"));

	oopart_pos_ = CreateDefaultSubobject<USphereComponent>(TEXT("Oopart Pos"));
	oopart_pos_->SetupAttachment(GetRootComponent());
	oopart_pos_->SetRelativeLocation({ 0, -49, 90 });

	GetCharacterMovement()->bUseRVOAvoidance = true;
	GetCharacterMovement()->AvoidanceConsiderationRadius = 100;

	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("HeroPreset"));

	forward_dir_ = { 1,0, 0 };
}

void AHeroBase::BeginPlay()
{
	Super::BeginPlay();
	//TODO: Two lines are Test purpose. Need to remove later.
	weapon_mechanics_->EquipWeapon(EWeaponType::AssaultRifle);
	equip_mechanics_->EquipArmor(EArmorType::TestSkillArmor);
	equip_mechanics_->EquipTrinket(ETrinketType::TestSkillTrinket);
	passive_skill_mechanics_->EquipPassiveSkill(EPassiveSkillType::FixedDmgReduce);
	oopart_mechanics_->EquipOopart(EOopartType::AttackSpeedBoost);
	skill_container_->EquipActiveSkill(EActiveSkillType::Thunder);
}

void AHeroBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Die();
	Super::EndPlay(EndPlayReason);
}

void AHeroBase::Initialize()
{

}

void AHeroBase::Die()
{
	weapon_mechanics_->OnDestroy();
	if (auto casted_gunner_aic = Cast<AGunnerAIController>(GetController()))
	{
		casted_gunner_aic->OnDie();
	}
	AIKGameModeBase* casted_mode = Cast<AIKGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (casted_mode) casted_mode->RemoveHero(this);
	Super::Die();
}

FDamageData AHeroBase::Attack(AActor* target)
{
	FDamageData damage_data;
	damage_data.damage_type = EDamageType::Projectile;
	damage_data.attacker = this;
	if (dmg_event_map_.Find(EHeroEvent::OnFire))
	{
		if (dmg_event_map_[EHeroEvent::OnFire].IsEmpty() == false)
		{
			for (auto& delegate : dmg_event_map_[EHeroEvent::OnFire])
			{
				if (delegate.IsBound())
				{
					damage_data = delegate.Execute(damage_data);
				}
			}
		}
	}
	weapon_mechanics_->SetDamageData(GetCharacterStat()->GetCharacterData(), damage_data);
	weapon_mechanics_->BeginFire(target);

	return damage_data;
}

void AHeroBase::GetStunned(float stun_duration)
{
	Super::GetStunned(stun_duration);
}

void AHeroBase::OnStunned()
{
	UE_LOG(LogTemp, Warning, TEXT("Hero Stunned"));
	Super::OnStunned();
	weapon_mechanics_->OnStunned();
}

EHeroType AHeroBase::GetHeroType() const
{
	return hero_type_;
}
