/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.20.2024
Summary : Source file for hero base.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Characters/HeroBase.h"

#include "AI/GunnerAIController.h"
#include "AI/HeroAIController.h"

#include "Components/CapsuleComponent.h"
#include "Components/PassiveSkillMechanics.h"
#include "Components/RuneMechanics.h"
#include "Components/SphereComponent.h"
#include "Components/WeaponMechanics.h"
#include "Components/ActiveSkillMechanics.h"
#include "Components/WidgetComponent.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystems/DelegateBridgeSubsystem.h"
#include "UI/HPUICore.h"
#include "WorldSettings/IKGameModeBase.h"
#include "WorldSettings/IKGameState.h"

AHeroBase::AHeroBase()
{
	active_skill_mechanics_ = CreateDefaultSubobject<UActiveSkillMechanics>(TEXT("ActiveMechanics"));
	weapon_mechanics_ = CreateDefaultSubobject<UWeaponMechanics>(TEXT("WeaponMechanics"));
	passive_skill_mechanics_ = CreateDefaultSubobject<UPassiveSkillMechanics>(TEXT("PassiveMechanics"));
	rune_mechanics_ = CreateDefaultSubobject<URuneMechanics>(TEXT("RuneMechanics"));
	ui_position_ = CreateDefaultSubobject<USphereComponent>(TEXT("ui position"));
	ui_position_->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	
	GetCharacterMovement()->bUseRVOAvoidance = true;
	GetCharacterMovement()->AvoidanceConsiderationRadius = 100;
	
	GetMesh()->SetCollisionProfileName(TEXT("HeroPreset"));

	forward_dir_ = { 1,0, 0 };
	is_hero_ = true;
}

//TODO: 특수 효과같은 경우, 장착과 발동이 달라야 한다. BeginPlay에 넣으면 구별할 수가 없다.
void AHeroBase::BeginPlay()
{
	Super::BeginPlay();
	UHPUICore* widget = Cast<UHPUICore>(hp_UI_->GetWidget());
	switch (GetCharacterType())
	{
	case ECharacterType::Hero1:
		rune_mechanics_->EquipRune(ERuneSetType::Dagger, 0);
		rune_mechanics_->EquipRune(ERuneSetType::Dagger, 2);
		rune_mechanics_->EquipRune(ERuneSetType::Dagger, 4);
		passive_skill_mechanics_->EquipPassiveSkill(EPassiveSkillType::LowProfile);
		hero_type_ = EHeroType::Hero1;
		break;
	case ECharacterType::Hero2:
		rune_mechanics_->EquipRune(ERuneSetType::Quake, 0);
		rune_mechanics_->EquipRune(ERuneSetType::Quake, 1);
		passive_skill_mechanics_->EquipPassiveSkill(EPassiveSkillType::Berserker);
		hero_type_ = EHeroType::Hero2;
		break;
	case ECharacterType::Hero3:
		rune_mechanics_->EquipRune(ERuneSetType::Viper, 0);
		rune_mechanics_->EquipRune(ERuneSetType::Viper, 2);
		rune_mechanics_->EquipRune(ERuneSetType::Viper, 4);
		rune_mechanics_->EquipRune(ERuneSetType::Quake, 1);
		rune_mechanics_->EquipRune(ERuneSetType::Quake, 3);
		rune_mechanics_->EquipRune(ERuneSetType::Quake, 5);
		passive_skill_mechanics_->EquipPassiveSkill(EPassiveSkillType::Agility);
		hero_type_ = EHeroType::Hero3;
		break;
	case ECharacterType::Hero4:
		rune_mechanics_->EquipRune(ERuneSetType::Quake, 0);
		rune_mechanics_->EquipRune(ERuneSetType::Quake, 2);
		rune_mechanics_->EquipRune(ERuneSetType::Quake, 4);
		rune_mechanics_->EquipRune(ERuneSetType::Quake, 1);
		rune_mechanics_->EquipRune(ERuneSetType::Quake, 3);
		rune_mechanics_->EquipRune(ERuneSetType::Quake, 5);
		passive_skill_mechanics_->EquipPassiveSkill(EPassiveSkillType::LowProfile);
		hero_type_ = EHeroType::Hero4;
		break;

	default:
		checkNoEntry();
	}
	widget->SetHPBarColor(hero_base_color_2_);

	//TEST PURPOSE
	if (weapon_mechanics_->GetWeaponActor() == nullptr)
	{
		weapon_mechanics_->EquipWeapon(default_weapon_class_);
	}

	active_skill_mechanics_->EquipActiveSkill(EActiveSkillType::ThunderStorm);
	//
}

void AHeroBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	OnApplyBuff.Clear();
	OnBuffExpired.Clear();
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
		active_skill_mechanics_->EquipActiveSkill(spawn_data.active_skill_data_.GetValue().type);
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


void AHeroBase::InitAfterHUD()
{
	passive_skill_mechanics_->InitPassiveSkill();
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

FColor AHeroBase::GetHeroBaseColor_1() const
{
	return hero_base_color_1_;
}

FColor AHeroBase::GetHeroBaseColor_2() const
{
	return hero_base_color_2_;
}

FTargetParameters AHeroBase::GetActiveSkillTargetParameters() const
{
	return active_skill_mechanics_->GetTargetParameters();
}

bool AHeroBase::HasActiveSkill() const
{
	return active_skill_mechanics_->HasActiveSkill();
}

void AHeroBase::ReduceActiveSkillCoolDown(float amount)
{
	auto game_state_cache_ = Cast<AIKGameState>(UGameplayStatics::GetGameState(GetWorld()));
	game_state_cache_->ReduceCoolDown(GetHeroType(), amount);
}

void AHeroBase::ReduceActiveSkillCoolDownPercentage(float percentage)
{
	auto game_state_cache_ = Cast<AIKGameState>(UGameplayStatics::GetGameState(GetWorld()));
	game_state_cache_->ReduceCoolDownPercentage(GetHeroType(), percentage);
}

void AHeroBase::AddBuffUI(FBuffUIData buff_ui_data)
{
	OnApplyBuff.Broadcast(buff_ui_data);
}

void AHeroBase::RemoveBuffUI(EBuffType buff_type)
{
	OnBuffExpired.Broadcast(buff_type);
}

UWeaponMechanics* AHeroBase::GetWeaponMechanics()
{
	return weapon_mechanics_;
}

URuneMechanics* AHeroBase::GetRuneMechanics()
{
	return rune_mechanics_;
}

UActiveSkillMechanics* AHeroBase::GetActiveSkillMechanics()
{
	return active_skill_mechanics_;
}

USkillBase* AHeroBase::GetActiveSkill()
{
	return active_skill_mechanics_->GetActiveSkill();
}
