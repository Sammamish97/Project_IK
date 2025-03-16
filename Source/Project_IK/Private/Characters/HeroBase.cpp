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
#include "Components/CapsuleComponent.h"
#include "Components/CharacterStatComponent.h"
#include "Components/OopartMechanics.h"
#include "Components/PassiveSkillMechanics.h"
#include "Components/RuneMechanics.h"
#include "Components/WeaponMechanics.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystems/LevelTransitionSubsystem.h"
#include "WorldSettings/IKGameInstance.h"
#include "WorldSettings/IKGameModeBase.h"

AHeroBase::AHeroBase()
{
	skill_container_ = CreateDefaultSubobject<USkillContainer>(TEXT("SkillContainer"));
	weapon_mechanics_ = CreateDefaultSubobject<UWeaponMechanics>(TEXT("WeaponMechanics"));
	passive_skill_mechanics_ = CreateDefaultSubobject<UPassiveSkillMechanics>(TEXT("PassiveMechanics"));
	rune_mechanics_ = CreateDefaultSubobject<URuneMechanics>(TEXT("RuneMechanics"));
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

//TODO: 특수 효과같은 경우, 장착과 발동이 달라야 한다. BeginPlay에 넣으면 구별할 수가 없다.
void AHeroBase::BeginPlay()
{
	Super::BeginPlay();

	weapon_mechanics_->EquipWeapon(EWeaponType::AssaultRifle);
	passive_skill_mechanics_->EquipPassiveSkill(EPassiveSkillType::FixedDmgReduce);
	oopart_mechanics_->EquipOopart(EOopartType::AttackSpeedBoost);
	skill_container_->EquipActiveSkill(EActiveSkillType::Thunder);
	
	rune_mechanics_->EquipRune(ERuneSetType::Chariot, 0);
	rune_mechanics_->EquipRune(ERuneSetType::Chariot, 1);
	rune_mechanics_->EquipRune(ERuneSetType::Chariot, 2);
	rune_mechanics_->EquipRune(ERuneSetType::Chariot, 3);
	rune_mechanics_->EquipRune(ERuneSetType::Chariot, 4);
	rune_mechanics_->EquipRune(ERuneSetType::Chariot, 5);
	
	rune_mechanics_->ApplySetBonuses();
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
	for (auto& delegate_array : hero_dmg_event_map_)
	{
		for (auto& delegate_elem : delegate_array.Value)
		{
			delegate_elem.Unbind();
		}
	}
	Super::Die();
}

FDamageData AHeroBase::Attack(AActor* target)
{
	FDamageData damage_data;
	damage_data.attacker = this;
	if (hero_dmg_event_map_.Find(EHeroEvent::OnFire))
	{
		if (hero_dmg_event_map_[EHeroEvent::OnFire].IsEmpty() == false)
		{
			for (auto& delegate : hero_dmg_event_map_[EHeroEvent::OnFire])
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

void AHeroBase::GetDamage(FDamageData data)
{
	Super::GetDamage(data);
	if (hero_dmg_event_map_.Find(EHeroEvent::OnHitBeforeCalc))
	{
		if (hero_dmg_event_map_[EHeroEvent::OnHitBeforeCalc].IsEmpty() == false)
		{
			for (auto& delegate : hero_dmg_event_map_[EHeroEvent::OnHitBeforeCalc])
			{
				if (delegate.IsBound())data = delegate.Execute(data);
			}
		}
	}

	bool is_evaded = character_stat_component_->CalcDamage(data);
	if (is_evaded == false)
	{
		if (hero_dmg_event_map_.Find(EHeroEvent::OnHitAfterCalc))
		{
			if (hero_dmg_event_map_[EHeroEvent::OnHitAfterCalc].IsEmpty() == false)
			{
				for (auto& delegate : hero_dmg_event_map_[EHeroEvent::OnHitAfterCalc])
				{
					if (delegate.IsBound()) data = delegate.Execute(data);
				}
			}
		}
		character_stat_component_->GetDamage(data.atk_base_dmg);
	}
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
}

EHeroType AHeroBase::GetHeroType() const
{
	return hero_type_;
}
