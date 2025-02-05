/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.20.2024
Summary : Source file for hero base.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Characters/HeroBase.h"

#include "Abilities/PassiveMechanics.h"
#include "Abilities/SkillContainer.h"
#include "Abilities/EquipSkills/EquipSkillBase.h"
#include "AI/GunnerAIController.h"
#include "Components/EquipMechanics.h"
#include "Components/CapsuleComponent.h"
#include "Components/CharacterStatComponent.h"
#include "Components/WeaponMechanics.h"
#include "Kismet/GameplayStatics.h"
#include "WorldSettings/IKGameModeBase.h"

AHeroBase::AHeroBase()
{
	skill_container_ = CreateDefaultSubobject<USkillContainer>(TEXT("SkillContainer"));
	weapon_mechanics_ = CreateDefaultSubobject<UWeaponMechanics>(TEXT("WeaponMechanics"));
	passive_mechanics_ = CreateDefaultSubobject<UPassiveMechanics>(TEXT("PassiveMechanics"));
	equip_mechanics_ = CreateDefaultSubobject<UEquipMechanics>(TEXT("EquipMechanics"));
	
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("HeroPreset"));
	
	forward_dir_ = {1,0, 0};
}

void AHeroBase::BeginPlay()
{
	Super::BeginPlay();
	weapon_mechanics_->SetWeaponOwner(this);
	//TODO: Two lines are Test purpose. Need to remove later.
	equip_mechanics_->EquipArmor(EArmorType::TestSkillArmor);
	equip_mechanics_->EquipTrinket(ETrinketType::TestAttack);
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
	if(auto casted_gunner_aic = Cast<AGunnerAIController>(GetController()))
	{
		casted_gunner_aic->OnDie();
	}
	AIKGameModeBase* casted_mode = Cast<AIKGameModeBase>(UGameplayStatics::GetGameMode(this));
	if(casted_mode) casted_mode->RemoveHero(this);
	for (auto& delegate : hero_dmg_event_map_)
	{
		delegate.Value.Unbind();
	}
	Super::Die();
}

void AHeroBase::GetDamage(FDamageData data)
{
	Super::GetDamage(data);
	if (hero_dmg_event_map_.Find(EHeroEvent::OnHitBeforeCalc))
	{
		if (hero_dmg_event_map_[EHeroEvent::OnHitBeforeCalc].IsBound())
		{
			data = hero_dmg_event_map_[EHeroEvent::OnHitBeforeCalc].Execute(data);
		}
	}
	
	bool is_evaded = character_stat_component_->CalcDamage(data);
	if (hero_dmg_event_map_.Find(EHeroEvent::OnHitAfterCalc))
	{
		if (is_evaded == false && hero_dmg_event_map_[EHeroEvent::OnHitAfterCalc].IsBound())
		{
			data = hero_dmg_event_map_[EHeroEvent::OnHitAfterCalc].Execute(data);
		}
	}
	character_stat_component_->GetDamage(data.damage);
	SetDamageUI(data, is_evaded);
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
	passive_mechanics_->OnStunned();
}