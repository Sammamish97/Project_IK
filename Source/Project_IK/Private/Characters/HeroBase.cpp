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
#include "Components/PassiveSkillMechanics.h"
#include "Components/RuneMechanics.h"
#include "Components/SphereComponent.h"
#include "Components/WeaponMechanics.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystems/DelegateBridgeSubsystem.h"
#include "UI/HeroWidget.h"
#include "UI/HP_UI_Widget.h"
#include "WorldSettings/IKGameModeBase.h"

AHeroBase::AHeroBase()
{
	skill_container_ = CreateDefaultSubobject<USkillContainer>(TEXT("SkillContainer"));
	weapon_mechanics_ = CreateDefaultSubobject<UWeaponMechanics>(TEXT("WeaponMechanics"));
	passive_skill_mechanics_ = CreateDefaultSubobject<UPassiveSkillMechanics>(TEXT("PassiveMechanics"));
	rune_mechanics_ = CreateDefaultSubobject<URuneMechanics>(TEXT("RuneMechanics"));
	ui_position_ = CreateDefaultSubobject<USphereComponent>(TEXT("ui position"));
	ui_position_->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	
	GetCharacterMovement()->bUseRVOAvoidance = true;
	GetCharacterMovement()->AvoidanceConsiderationRadius = 100;

	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("HeroPreset"));
	ui_position_->SetCollisionProfileName(TEXT("NoCollision"));
	
	forward_dir_ = { 1,0, 0 };
	is_hero_ = true;
}

//TODO: 특수 효과같은 경우, 장착과 발동이 달라야 한다. BeginPlay에 넣으면 구별할 수가 없다.
void AHeroBase::BeginPlay()
{
	Super::BeginPlay();
	switch (GetCharacterType())
	{
	case ECharacterType::Hero1:
		hero_type_ = EHeroType::Hero1;
		break;
	case ECharacterType::Hero2:
		hero_type_ = EHeroType::Hero2;
		break;
	case ECharacterType::Hero3:
		hero_type_ = EHeroType::Hero3;
		break;
	case ECharacterType::Hero4:
		hero_type_ = EHeroType::Hero4;
		break;

	default:
		checkNoEntry();
	}
	
	//TEST PURPOSE
	if (weapon_mechanics_->GetWeaponActor() == nullptr)
	{
		weapon_mechanics_->EquipWeapon(default_weapon_class_);
	}
	
	rune_mechanics_->EquipRune(ERuneSetType::Dagger, 0);
	rune_mechanics_->EquipRune(ERuneSetType::Dagger, 2);
	rune_mechanics_->EquipRune(ERuneSetType::Dagger, 4);
	//
	
	UDelegateBridgeSubsystem* subsystem = GetWorld()->GetSubsystem<UDelegateBridgeSubsystem>();
	if (UHeroWidget* hero_widget = Cast<UHeroWidget>(hp_UI_->GetWidget()))
	{
		hero_widget->InitHeroWidget(rune_mechanics_, character_stat_component_->GetMaxHitPoint(), character_stat_component_->GetHitPoint());
		subsystem->BindOnHPOrShieldChanged(character_stat_component_, hero_widget->GetHPWidget(), &UHP_UI_Widget::UpdateWidget);
	}
	
	hp_UI_->AttachToComponent(ui_position_, FAttachmentTransformRules::KeepRelativeTransform);
	hp_UI_->SetDrawSize({ 250, 50 });
}

void AHeroBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AHeroBase::EquipGears(FSpawnData spawn_data)
{
	if (spawn_data.weapon_data_.IsSet())
	{
		weapon_mechanics_->EquipWeapon(spawn_data.weapon_data_.GetValue().weapon_class_);
	}
	else
	{
		weapon_mechanics_->EquipWeapon(default_weapon_class_);
	}
	if (spawn_data.passive_skill_data_.IsSet())
	{
		passive_skill_mechanics_->EquipPassiveSkill(spawn_data.passive_skill_data_.GetValue().type);
	}
	if (spawn_data.active_skill_data_.IsSet())
	{
		skill_container_->EquipActiveSkill(spawn_data.active_skill_data_.GetValue().type);
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
	if (casted_mode) casted_mode->RemoveHero(hero_type_);
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
	//weapon_mechanics_->OnStunned();
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

void AHeroBase::ReduceCooltime(float reduce_time)
{
	skill_container_->ReduceCooltime(reduce_time);
}

void AHeroBase::ReduceCooltimeByPercentage(float percentage)
{
	skill_container_->ReduceCooltimeByPercentage(percentage);
}

UWeaponMechanics* AHeroBase::GetWeaponMechanics()
{
	return weapon_mechanics_;
}

class URuneMechanics* AHeroBase::GetRuneMechanics()
{
	return rune_mechanics_;
}
