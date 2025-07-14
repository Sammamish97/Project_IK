/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.20.2024
Summary : Source file for unit.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Characters/Unit.h"

#include "BrainComponent.h"
#include "AI/MeleeAIController.h"
#include "Components/CharacterStatComponent.h"
#include "Components/CrowdControlComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/OutlineComponent.h"

#include "UI/HitPointsUI.h"
#include "Components/ObjectPoolComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Structs/BuffUIData.h"
#include "UI/DamageUI.h"

#include "Subsystems/GlobalBuffSubsystem.h"

#include "Structs/BuffStatusData.h"
#include "Subsystems/DelegateBridgeSubsystem.h"
#include "UI/HPUICore.h"

// Sets default values
AUnit::AUnit()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	character_stat_component_ = CreateDefaultSubobject<UCharacterStatComponent>(TEXT("CharacterStatComponent"));
	hp_UI_ = CreateDefaultSubobject<UWidgetComponent>(TEXT("HP UI"));
	
	cc_component_ = CreateDefaultSubobject<UCrowdControlComponent>(TEXT("CC Component"));
	object_pool_component_ = CreateDefaultSubobject<UObjectPoolComponent>(TEXT("ObjectPool"));
	outline_component_ = CreateDefaultSubobject<UOutlineComponent>(TEXT("OutlineComponent"));

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));
	USkeletalMeshComponent* skeletal = GetMesh();
	if (skeletal)
	{
		skeletal->SetGenerateOverlapEvents(true);
		// It want ragdollings, need to turn it on.
		skeletal->SetSimulatePhysics(false);
		skeletal->bReceivesDecals = false;

	}
}

UCharacterStatComponent* AUnit::GetCharacterStat()
{
	return character_stat_component_;
}

UCrowdControlComponent* AUnit::GetCCComponent()
{
	return cc_component_;
}

FVector AUnit::GetForwardDir() const
{
	return forward_dir_;
}

void AUnit::SetForwardDir(const FVector& Forward_Dir)
{
	forward_dir_ = Forward_Dir;
}

void AUnit::SetCurHidingCover(AActor* cover)
{
	cur_hiding_cover_ = cover;
}

AActor* AUnit::GetCurHidingCover() const
{
	return cur_hiding_cover_.Get();
}

void AUnit::SetAttackTarget(AActor* target)
{
	return Cast<AMeleeAIController>(GetController())->SetTargetActor(target);
}

AActor* AUnit::GetAttackTarget()
{
	return Cast<AMeleeAIController>(GetController())->GetTargetActor();
}

void AUnit::SetOutlineState(EOutlineState state)
{
	if(auto target = GetComponentByClass<UPrimitiveComponent>())
	{
		outline_component_->SwitchOutline(target, state);
	}
}

void AUnit::Attack(AActor* target)
{
	if (is_first_attack_)
	{
		OnEnterBattleOnce();
		is_first_attack_ = false;
	}
}

ECharacterType AUnit::GetCharacterType() const
{
	return character_type_;
}

EUnitBoneType AUnit::GetBoneType() const
{
	return bone_type_;
}

bool AUnit::IsHero() const
{
	return is_hero_;
}

// Called when the game starts or when spawned
void AUnit::BeginPlay()
{
	Super::BeginPlay();
	SpawnDefaultController();
	GetGameInstance()->GetSubsystem<UGlobalBuffSubsystem>()->ApplyBuff(this);

	UCapsuleComponent* capsule_comp = FindComponentByClass<UCapsuleComponent>();
	if (capsule_comp)
	{
		capsule_half_height_ = capsule_comp->GetUnscaledCapsuleHalfHeight() / 2.f;
		capsule_radius_ = capsule_comp->GetUnscaledCapsuleRadius();
	}
	if (auto casted_controller = Cast<AMeleeAIController>(GetController()))
	{
		casted_controller->SetAIFindTargetType(ai_find_target_type_);
	}

	if (hp_UI_class_)
	{
		hp_UI_->SetWidgetClass(hp_UI_class_);
		hp_UI_->InitWidget();
		hp_UI_->SetWidgetSpace(EWidgetSpace::Screen);
	}
	UDelegateBridgeSubsystem* subsystem = GetWorld()->GetSubsystem<UDelegateBridgeSubsystem>();

	if (UHPUICore* hp_widget = Cast<UHPUICore>(hp_UI_->GetWidget()))
	{
		hp_widget->InitHPWidget(character_stat_component_->GetMaxHitPoint(), character_stat_component_->GetHitPoint());
		subsystem->BindOnHPOrShieldChanged(character_stat_component_, hp_widget, &UHPUICore::UpdateWidget);
	}
	hp_UI_->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	hp_UI_->SetDrawSize({ 100, 15 });
}

void AUnit::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	GetWorld()->GetTimerManager().ClearTimer(stun_timer_);
}

void AUnit::SetDamageUI(FDamageData data, bool is_evaded)
{
	if (is_evaded)
	{
		ADamageUI* missed_ui = SpawnDamageUI();
		if (missed_ui)
		{
			missed_ui->SetMissed();
		}
	}
	else
	{
		if (data.atk_base_dmg_ > 0.f)
		{
			ADamageUI* atk_ui = SpawnDamageUI();
			if (atk_ui)
			{
				atk_ui->SetDamageAmount(data.atk_base_dmg_, FLinearColor::White);
			}
		}
		else if (data.atk_base_dmg_ < 0.f)
		{
			UE_LOG(LogTemp, Error, TEXT("atk_base_dmg less than 0 has come."));
		}

		if (data.skill_power_base_dmg_ > 0.f)
		{
			ADamageUI* skill_ui = SpawnDamageUI();
			if (skill_ui)
			{
				skill_ui->SetDamageAmount(data.skill_power_base_dmg_, FLinearColor::Blue);
			}
		}
		else if (data.skill_power_base_dmg_ < 0.f)
		{
			UE_LOG(LogTemp, Error, TEXT("skill_power_base_dmg less than 0 has come."));
		}
	}
}

void AUnit::GetDamage(FDamageData data)
{
	if (GetCharacterStat()->GetHitPoint() + GetCharacterStat()->GetShield() - data.atk_base_dmg_  - data.skill_power_base_dmg_ <= 0.f )
	{
 		if (AActor* attacker_ptr = data.attacker_.Get())
		{
			Cast<AUnit>(attacker_ptr)->DispatchUnitEvent(EUnitEvent::OnEliminate);
		}
	}
	switch (data.damage_type_)
	{
	case EDamageType::Projectile:
	case EDamageType::Explosive:
	case EDamageType::Melee:
		GetDamageByPEM(data);
		break;
	case EDamageType::Dot:
		GetDamageByDot(data);
		break;
	case EDamageType::Magic:
		GetDamageByMagic(data);
		break;
	default:
		break;
	}
}

void AUnit::Heal(float heal)
{
	character_stat_component_->Heal(heal);

	ADamageUI* ui = SpawnDamageUI();
	if (ui)
	{
		ui->SetHealAmount(heal);
	}
}

void AUnit::ApplyBuff(EBuffType buff_type, FBuffStatusData buff_status)
{
	character_stat_component_->ApplyBuff(buff_type, buff_status);
}

void AUnit::RemoveBuff(EBuffType buff_type)
{
	character_stat_component_->RemoveBuff(buff_type);
}

void AUnit::ApplyCrowdControl(ECCType cc_type, float duration)
{
	cc_component_->ApplyCrowdControl(cc_type, duration);
}

void AUnit::AcquireShield(float ShieldAmount, float Duration)
{
	character_stat_component_->AcquireShield(ShieldAmount, Duration);
}

void AUnit::GetStunned(float stun_duration)
{
	UE_LOG(LogTemp, Display, TEXT("AUnit::GetStunned"));
	DispatchUnitEvent(EUnitEvent::OnStun);
	if (GetWorld()->GetTimerManager().IsTimerActive(stun_timer_) == false)
	{
		OnStunned();
		GetWorld()->GetTimerManager().SetTimer(stun_timer_, this, &AUnit::FinishStun, stun_duration);
	}
}

void AUnit::OnStunned()
{
	//BT 역시 stun시키기
	Cast<AMeleeAIController>(GetController())->GetStunned();
	PlayAnimMontage(stun_montage_);
}

void AUnit::FinishStun()
{
	UE_LOG(LogTemp, Display, TEXT("AUnit::FinishStunned"));
	FAIMessage Msg(TEXT("StunFinished"), this, stun_ai_request_id_, FAIMessage::Success);
	FAIMessage::Send(this, Msg);
}

void AUnit::EnterBTSkillMotionState()
{
	Cast<AMeleeAIController>(GetController())->SetUnitState(EUnitState::OnActiveSkill);
}

void AUnit::ResetUnitState()
{
	Cast<AMeleeAIController>(GetController())->ResetUnitState();
}

void AUnit::OnEnterBattleOnce()
{
	DispatchUnitEvent(EUnitEvent::OnEnterBattle);
}

float AUnit::GetPitchDiffBetweenTarget()
{
	if (auto controller = Cast<AMeleeAIController>(GetController()))
	{
		if (AActor* target = controller->GetTargetActor())
		{
			return UKismetMathLibrary::FindLookAtRotation(Owner->GetActorLocation(), target->GetActorLocation()).Pitch;
		}
	}
	return 0.f;
}

void AUnit::Die()
{
	DispatchUnitEvent(EUnitEvent::OnDie);
	for (auto& delegate_map : on_unit_event_)
	{
		delegate_map.Value.Clear();
	}
	Destroy();
}

ADamageUI* AUnit::SpawnDamageUI()
{
	// Randomize spawn locations
	FTransform transform = GetActorTransform();
	FVector rand_offsets = FVector(0.f, capsule_radius_ + FMath::RandRange(-10.f, 50.f), capsule_half_height_ + FMath::RandRange(-10.f, 50.f));

	APlayerController* player_controller = GetWorld()->GetFirstPlayerController();
	if (player_controller && player_controller->PlayerCameraManager)
	{
		rand_offsets = player_controller->PlayerCameraManager->GetCameraRotation().RotateVector(rand_offsets);
	}

	transform.SetLocation(transform.GetLocation() + rand_offsets);


	return Cast<ADamageUI>(object_pool_component_->SpawnFromPool(transform.Rotator(), transform.GetLocation()));
}

void AUnit::GetDamageByDot(FDamageData data)
{
	character_stat_component_->GetDamage(data.atk_base_dmg_);
	character_stat_component_->GetDamage(data.skill_power_base_dmg_);
	character_stat_component_->RecordDamage(data);
	SetDamageUI(data, false);
}

void AUnit::GetDamageByPEM(FDamageData data)
{
	bool is_evaded = character_stat_component_->CalcDamage(data);
	if (is_evaded == false)
	{
		RecoverAttackerByLifeSteal(data);
		character_stat_component_->GetDamage(data.atk_base_dmg_);
		character_stat_component_->GetDamage(data.skill_power_base_dmg_);
	}
	SetDamageUI(data, is_evaded);
}

void AUnit::GetDamageByMagic(FDamageData data)
{
	bool is_evaded = character_stat_component_->CalcDamage(data);
	if (is_evaded == false)
	{
		character_stat_component_->GetDamage(data.atk_base_dmg_);
		character_stat_component_->GetDamage(data.skill_power_base_dmg_);
	}
	SetDamageUI(data, is_evaded);
}

void AUnit::DispatchUnitEvent(EUnitEvent type)
{
	if (on_unit_event_.Find(type))
	{
		on_unit_event_[type].Broadcast();
	}
}

void AUnit::RecoverAttackerByLifeSteal(FDamageData data)
{
	if (data.atk_base_dmg_ <= 0.f)
	{
		return;
	}

	AActor* attacker = data.attacker_.Get();
	if (attacker)
	{
		AUnit* unit = Cast<AUnit>(attacker);
		if (unit)
		{
			float attacker_life_steal = unit->GetCharacterStat()->GetLifeSteal();
			if (attacker_life_steal > 0.f)
			{
				unit->Heal(data.atk_base_dmg_ * attacker_life_steal);
			}
		}
	}
}

float AUnit::GetStunRequestID() const
{
	return stun_ai_request_id_;
}
