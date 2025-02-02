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
#include "AI/GunnerAIController.h"
#include "Components/ArmorMechanics.h"
#include "Components/CapsuleComponent.h"
#include "Components/CharacterStatComponent.h"
#include "Components/SphereComponent.h"
#include "Components/WeaponMechanics.h"
#include "Components/CharacterStatComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Weapons/Drone.h"
#include "WorldSettings/IKGameModeBase.h"
#include "Weapons/Drone.h"

AHeroBase::AHeroBase()
{
	skill_container_ = CreateDefaultSubobject<USkillContainer>(TEXT("SkillContainer"));
	weapon_mechanics_ = CreateDefaultSubobject<UWeaponMechanics>(TEXT("WeaponMechanics"));
	passive_mechanics_ = CreateDefaultSubobject<UPassiveMechanics>(TEXT("PassiveMechanics"));
	armor_mechanics_ = CreateDefaultSubobject<UArmorMechanics>(TEXT("ArmorMechanics"));
	drone_location_ = CreateDefaultSubobject<USphereComponent>("Drone Location");

	drone_location_->SetCollisionProfileName(TEXT("NoCollision"));
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("HeroPreset"));
	
	drone_location_->SetupAttachment(RootComponent);
	drone_location_->SetRelativeLocation({0, -49, 90});

	forward_dir_ = {1,0, 0};
}

void AHeroBase::BeginPlay()
{
	Super::BeginPlay();

	drone_ = GetWorld()->SpawnActor<ADrone>(drone_bp_class_, drone_location_->GetComponentTransform());
	weapon_mechanics_->SetWeaponOwner(this);
	//TODO: Test purpose. Need to remove later.
	armor_mechanics_->EquipArmor(EArmorType::TestSkillArmor);

	if(drone_ == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed To create Drone!"));
	}
	else
	{
		Cast<ADrone>(drone_)->Initialize(this	);
		drone_->AttachToComponent(drone_location_, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	}
}

void AHeroBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Die();
	Super::EndPlay(EndPlayReason);
}

void AHeroBase::Initialize()
{
	if(drone_)
	{
		drone_->SetPlugins(character_stat_component_->GetPeriodicDP(), character_stat_component_->GetGeneralDP());
	}
}

void AHeroBase::Die()
{
	weapon_mechanics_->OnDestroy();
	if(auto casted_gunner_aic = Cast<AGunnerAIController>(GetController()))
	{
		casted_gunner_aic->OnDie();
	}
	if(auto casted_drone = Cast<ADrone>(drone_))
	{
		casted_drone->Die();
	}
	AIKGameModeBase* casted_mode = Cast<AIKGameModeBase>(UGameplayStatics::GetGameMode(this));
	if(casted_mode) casted_mode->RemoveHero(this);
	Super::Die();
}

void AHeroBase::GetDamage(FDamageData data)
{
	Super::GetDamage(data);
	float calculated_dmg = character_stat_component_->CalcDamage(data);
	data.damage = calculated_dmg;
	UArmorMechanics* armor_mechanics = Cast<UArmorMechanics>(GetComponentByClass(UArmorMechanics::StaticClass()));
	if (armor_mechanics)
	{
		if (armor_mechanics->OnArmorHitFunction != nullptr)
		{
			data = armor_mechanics->OnArmorHitFunction(armor_mechanics, data);
		}
	}
	character_stat_component_->GetDamage(data.damage);
	SetDamageUI(data.damage);
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

void AHeroBase::SetPeriodicDP(EDPType dp_type)
{
	character_stat_component_->SetPeriodicDP(dp_type);
}

void AHeroBase::SetGenericDP(EDPType dp_type)
{
	character_stat_component_->SetGeneralDP(dp_type);
}
