/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.20.2024
Summary : Source file for hero base.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Characters/HeroBase.h"

#include "BrainComponent.h"
#include "Abilities/Buffs/BuffHandler.h"
#include "AI/GunnerAIController.h"
#include "AI/HeroAIController.h"

#include "Components/PassiveSkillMechanics.h"
#include "Components/RuneMechanics.h"
#include "Components/SphereComponent.h"
#include "Components/WeaponMechanics.h"
#include "Components/ActiveSkillMechanics.h"
#include "Components/WidgetComponent.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/DataTableManager.h"
#include "Subsystems/DelegateBridgeSubsystem.h"
#include "UI/Combat/HPUICore.h"
#include "WorldSettings/IKGameModeBase.h"
#include "WorldSettings/IKGameState.h"

#include "NiagaraFunctionLibrary.h"
#include "Subsystems/AudioManagerSubsystem.h"

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
	hp_widget_component_->InitWidget();

	UDelegateBridgeSubsystem* subsystem = GetWorld()->GetSubsystem<UDelegateBridgeSubsystem>();
	if (TObjectPtr<UHPUICore> hp_core = Cast<UHPUICore>(hp_widget_component_->GetWidget()))
	{
		//IKTODO: 현재 HP/UI 색상이 하드코드 되었다. 더 좋은 방법을 찾아야 한다.
		hp_core->SetHPBarColor(FLinearColor::Red);
		hp_core->InitHPWidget(character_stat_component_->GetMaxHitPoint(), character_stat_component_->GetHitPoint());
		subsystem->BindOnHPOrShieldChanged(character_stat_component_, hp_core.Get(), &UHPUICore::UpdateWidget);
	}

	maintain_buff_ = NewObject<UBuffHandler>(this, maintain_buff_class_);
}

void AHeroBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	OnApplyBuff.Clear();
	OnBuffExpired.Clear();
}

void AHeroBase::SyncWithSpawnData(const FSpawnData& spawn_data)
{
	character_stat_component_->SetCharacterData(spawn_data.character_data_);

	if (spawn_data.weapon_data_.type_ != EWeaponType::INVALID)
	{
		weapon_mechanics_->EquipWeapon(spawn_data.weapon_data_);
	}
	else
	{
		UIKGameInstance* instance = Cast<UIKGameInstance>(GetGameInstance());
		auto weapon_data = instance->GetDataTableManager()->GetWeaponData(EWeaponType::Pistol_B);
		weapon_mechanics_->EquipWeapon(weapon_data);
	}

	if (spawn_data.active_skill_data_.type_ != EActiveSkillType::INVALID)
	{
		active_skill_mechanics_->EquipActiveSkill(spawn_data.active_skill_data_);
	}
	
	if (spawn_data.passive_skill_data_1_.type_ != EPassiveSkillType::INVALID)
	{
		passive_skill_mechanics_->EquipPassiveSkill(spawn_data.passive_skill_data_1_, 0);
	}
	if (spawn_data.passive_skill_data_2_.type_ != EPassiveSkillType::INVALID)
	{
		passive_skill_mechanics_->EquipPassiveSkill(spawn_data.passive_skill_data_2_, 1);
	}
	if (spawn_data.passive_skill_data_3_.type_ != EPassiveSkillType::INVALID)
	{
		passive_skill_mechanics_->EquipPassiveSkill(spawn_data.passive_skill_data_3_, 2);
	}
	
	TArray rune_data_array = {spawn_data.rune_data_1, spawn_data.rune_data_2, spawn_data.rune_data_3, spawn_data.rune_data_4, spawn_data.rune_data_5, spawn_data.rune_data_6};
	for (int32 i = 0; i < rune_data_array.Num(); i++)
	{
		if (rune_data_array[i].set_type != ERuneSetType::INVALID)
		{
			rune_mechanics_->EquipRune(rune_data_array[i].set_type, i);
		}
	}
	rune_mechanics_->ApplySetBonuses();
}

void AHeroBase::Die()
{
	AIKGameModeBase* casted_mode = Cast<AIKGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (casted_mode) casted_mode->RemoveHero(hero_type_);

	weapon_mechanics_->DieWeaponActor();
	UAudioManagerSubsystem::Get(this)->PlayAtLocation(EAudioType::HeroDied, GetActorLocation());

	Super::Die();
}

void AHeroBase::Attack(AActor* target)
{
	Super::Attack(target);
	weapon_mechanics_->BeginFire(target);
}

void AHeroBase::SetUnitStateWithInterrupt(EUnitState type)
{
	Cast<AMeleeAIController>(GetController())->SetUnitState(type);
	switch (type)
	{
	case EUnitState::OnStunned:
		Cast<AHeroAIController>(GetController())->StopMovement();
		
	case EUnitState::OnRepositioning:
		active_skill_mechanics_->StopActiveSkill();
		
	case EUnitState::OnActiveSkill:
	{
		weapon_mechanics_->StopReload();
	}
		
	case EUnitState::OnReloading:
	{
		weapon_mechanics_->FinishFire();
		weapon_mechanics_->SetHoldAction(true);
	}
	
	default:
		break;
		//IKTODO: 예외처리
	}
}

void AHeroBase::ResetUnitState()
{
	Super::ResetUnitState();
	weapon_mechanics_->SetHoldAction(false);
}

void AHeroBase::GetStunned(float stun_duration)
{
	Super::GetStunned(stun_duration);
}

void AHeroBase::OnStunned()
{
	UE_LOG(LogTemp, Warning, TEXT("Hero Stunned"));
	Super::OnStunned();
}

EHeroType AHeroBase::GetHeroType() const
{
	return hero_type_;
}

void AHeroBase::Reposition(FVector target_location)
{
	DispatchUnitEvent(EUnitEvent::OnReposition);
	Cast<AHeroAIController>(GetController())->RepositionHero(target_location);
	SetUnitStateWithInterrupt(EUnitState::OnRepositioning);
}

void AHeroBase::SetAttackTarget(AActor* target)
{
	ResetUnitState();
	if (AHeroAIController* controller = Cast<AHeroAIController>(GetController()))
	{
		controller->SetAttackTarget(target);
	}
}

void AHeroBase::BeginMaintaining()
{
	maintain_buff_->ApplyBuff(this);
}

AActor* AHeroBase::GetAttackTarget() const
{
	if (AHeroAIController* controller = Cast<AHeroAIController>(GetController()))
	{
		return controller->GetTargetActor();
	}
	return nullptr;
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

UPassiveSkillMechanics* AHeroBase::GetPassiveSkillMechanics()
{
	return passive_skill_mechanics_;
}

void AHeroBase::ChangeGunShotSoundTemporariliy(EAudioType temporary_gunshot_audio, float duration)
{
	weapon_mechanics_->ChangeGunShotSoundTemporariliy(temporary_gunshot_audio, duration);
}

void AHeroBase::RecoverGunShotSound()
{
	weapon_mechanics_->RecoverGunShotSound();
}
