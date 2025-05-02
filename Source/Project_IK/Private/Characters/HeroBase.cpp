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
#include "AI/HeroAIController.h"
#include "Components/CapsuleComponent.h"
#include "Components/CharacterStatComponent.h"
#include "Components/OopartMechanics.h"
#include "Components/PassiveSkillMechanics.h"
#include "Components/RuneMechanics.h"
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

	rune_mechanics_->EquipRune(ERuneSetType::Poet, 0);
	rune_mechanics_->EquipRune(ERuneSetType::Poet, 1);
	rune_mechanics_->EquipRune(ERuneSetType::Poet, 2);
	rune_mechanics_->EquipRune(ERuneSetType::Poet, 3);
	rune_mechanics_->EquipRune(ERuneSetType::Poet, 4);
	rune_mechanics_->EquipRune(ERuneSetType::Poet, 5);

	skill_container_->EquipActiveSkill(EActiveSkillType::Thunder);
}

void AHeroBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AHeroBase::Initialize(FSpawnData spawn_data)
{
	if (spawn_data.weapon_data_.IsSet())
	{
		weapon_mechanics_->EquipWeapon(spawn_data.weapon_data_.GetValue().type);
	}
	else
	{
		weapon_mechanics_->EquipWeapon(EWeaponType::DefaultPistol);
	}
	if (spawn_data.passive_skill_data_.IsSet())
	{
		passive_skill_mechanics_->EquipPassiveSkill(spawn_data.passive_skill_data_.GetValue().type);
	}
	if (spawn_data.active_skill_data_.IsSet())
	{
		skill_container_->EquipActiveSkill(spawn_data.active_skill_data_.GetValue().type);
	}
	if (spawn_data.oopart_data_.IsSet())
	{
		oopart_mechanics_->EquipOopart(spawn_data.oopart_data_.GetValue().type);
	}

	TArray rune_data_array = {spawn_data.rune_data_1, spawn_data.rune_data_2, spawn_data.rune_data_3, spawn_data.rune_data_4, spawn_data.rune_data_5, spawn_data.rune_data_6};

	for (int32 i = 0; i < rune_data_array.Num(); i++)
	{
		if (rune_data_array[i].IsSet())
		{
			rune_mechanics_->EquipRune(rune_data_array[i].GetValue().set_type, i);
		}
	}
	rune_mechanics_->ApplySetBonuses();
}

void AHeroBase::Die()
{
	AIKGameModeBase* casted_mode = Cast<AIKGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (casted_mode) casted_mode->RemoveHero(GetCharacterStat()->GetCharacterID());
	Super::Die();
}

void AHeroBase::Attack(AActor* target)
{
	Super::Attack(target);
	weapon_mechanics_->BeginFire(target);
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

void AHeroBase::InvokeActiveSkill(FTargetResult target_result)
{
	DispatchUnitEvent(EUnitEvent::OnActiveSkill);
	skill_container_->InvokeSkills(target_result);
}

void AHeroBase::Reposition(FVector target_location)
{
	DispatchUnitEvent(EUnitEvent::OnMove);
	Cast<AHeroAIController>(GetController())->RepositionHero(target_location);
}

void AHeroBase::SetAttackTarget(AActor* target)
{
	Cast<AHeroAIController>(GetController())->SetAttackTarget(target);
}

void AHeroBase::SetIsCovered(bool is_covered)
{
	is_covered_ = is_covered;
}

AActor* AHeroBase::GetAttackTarget() const
{
	return Cast<AMeleeAIController>(GetController())->GetTargetActor();
}

TOptional<FTargetParameters> AHeroBase::GetActiveSkillTargetParameters() const
{
	return skill_container_->GetTargetParameters();
}

bool AHeroBase::IsActiveSkillOnCoolDown() const
{
	return skill_container_->IsOnCoolDown();
}

bool AHeroBase::HasActiveSkill() const
{
	return skill_container_->HasActiveSkill();
}

UWeaponMechanics* AHeroBase::GetWeaponMechanics()
{
	return weapon_mechanics_;
}
