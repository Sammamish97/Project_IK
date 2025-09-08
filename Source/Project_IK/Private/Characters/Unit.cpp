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
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Components/CharacterStatComponent.h"
#include "Components/CrowdControlComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/OutlineComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Kismet/KismetMathLibrary.h"

#include "Subsystems/GlobalBuffSubsystem.h"

#include "Structs/BuffStatusData.h"
#include "Subsystems/DelegateBridgeSubsystem.h"
#include "UI/Combat/HPUICore.h"

#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

// Sets default values
AUnit::AUnit()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	character_stat_component_ = CreateDefaultSubobject<UCharacterStatComponent>(TEXT("CharacterStatComponent"));
	hp_widget_component_ = CreateDefaultSubobject<UWidgetComponent>(TEXT("HP Widget Component"));

	cc_component_ = CreateDefaultSubobject<UCrowdControlComponent>(TEXT("CC Component"));
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

UWidgetComponent* AUnit::GetHPUIWidgetComponent()
{
	return hp_widget_component_;
}

FVector AUnit::GetForwardDir() const
{
	return forward_dir_;
}

void AUnit::SetForwardDir(const FVector& Forward_Dir)
{
	forward_dir_ = Forward_Dir;
}

void AUnit::SetAttackTarget(AActor* target)
{
	AMeleeAIController* controller = Cast<AMeleeAIController>(GetController());
	if (controller)
	{
		controller->SetTargetActor(target);
	}
}

AActor* AUnit::GetAttackTarget()
{
	AMeleeAIController* controller = Cast<AMeleeAIController>(GetController());
	if (controller)
	{
		return controller->GetTargetActor();
	}
	else
	{
		return nullptr;
	}
}

void AUnit::SetOutlineState(EOutlineState state)
{
	if (auto target = GetComponentByClass<UPrimitiveComponent>())
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

bool AUnit::IsHero() const
{
	return is_hero_;
}

void AUnit::FinishAction()
{
	AAIController* controller = Cast<AAIController>(GetController());
	if (controller)
	{
		auto bt_component = Cast<UBehaviorTreeComponent>(controller->GetBrainComponent());
		OnFinishAction.Broadcast(bt_component, false);
	}
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
		hp_widget_component_->SetWidgetClass(hp_UI_class_);
		hp_widget_component_->InitWidget();
		hp_widget_component_->SetWidgetSpace(EWidgetSpace::Screen);
	}
	hp_widget_component_->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	hp_widget_component_->SetDrawSize({ 100, 15 });
}

void AUnit::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	GetWorld()->GetTimerManager().ClearTimer(stun_timer_);
}

bool AUnit::IsDead() const
{
	return is_dead_;
}

void AUnit::SetDamageUI(FDamageData data, bool is_evaded)
{
	UNiagaraComponent* damage_ui = UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, damage_ui_system_, hp_widget_component_->GetComponentLocation());

	damage_ui->SetBoolParameter(FName("IsMissed"), is_evaded);
	damage_ui->SetFloatParameter(FName("DamageAmount"), data.atk_base_dmg_ + data.skill_power_base_dmg_);
	if (data.is_critical_shot_)
	{
		damage_ui->SetColorParameter(FName("Color"), FLinearColor::Red / 5.f);
		damage_ui->SetFloatParameter(FName("SizeMultiplier"), 3.f);
	}
	else
	{
		damage_ui->SetColorParameter(FName("Color"), FLinearColor::Blue / 5.f);
	}
}

void AUnit::GetDamage(FDamageData data)
{
	if (GetCharacterStat()->GetHitPoint() + GetCharacterStat()->GetShield() - data.atk_base_dmg_ - data.skill_power_base_dmg_ <= 0.f)
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

	UNiagaraComponent* damage_ui = UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, damage_ui_system_, hp_widget_component_->GetComponentLocation());
	damage_ui->SetFloatParameter(FName("DamageAmount"), heal);
	damage_ui->SetColorParameter(FName("Color"), FLinearColor::Green / 5.f);
}

void AUnit::ApplyStatusBuff(EBuffType buff_type, FBuffStatusData buff_status)
{
	character_stat_component_->ApplyBuff(buff_type, buff_status);
}

void AUnit::AddBuffUI(EBuffType type, UTexture2D* thumbnail)
{
	OnApplyBuff.Broadcast(type, thumbnail, true, -1.f);
}

void AUnit::AddBuffUI(EBuffType type, UTexture2D* thumbnail, float duration)
{
	OnApplyBuff.Broadcast(type, thumbnail, false, duration);
}

void AUnit::RemoveBuffUI(EBuffType type)
{
	OnBuffExpired.Broadcast(type);
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
	AMeleeAIController* controller = Cast<AMeleeAIController>(GetController());
	if (controller)
	{
		controller->GetStunned();
	}
	PlayAnimMontage(stun_montage_);
}

void AUnit::FinishStun()
{
	//IKTODO: AI_BEHAVIOR TREE와 연결해야 함.
}


void AUnit::SetUnitStateWithInterrupt(EUnitState type)
{

}

void AUnit::ResetUnitState()
{
	AMeleeAIController* controller = Cast<AMeleeAIController>(GetController());
	if (controller)
	{
		controller->ResetUnitState();
	}
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
	is_dead_ = true;

	DispatchUnitEvent(EUnitEvent::OnDie);
	for (auto& delegate_map : on_unit_event_)
	{
		delegate_map.Value.Clear();
	}

	GetCharacterMovement()->DisableMovement();
	DetachFromControllerPendingDestroy();
	PlayRagdollAnimation(GetMesh());
	FVector impulse = -GetActorForwardVector() * FMath::RandRange(2500.f, 4500.f);
	GetMesh()->AddImpulse(impulse, NAME_None, true);
	hp_widget_component_->SetVisibility(false);

	GetWorldTimerManager().SetTimer(destroy_timer_, this, &AUnit::OnUnitDied, 3.f);
}

void AUnit::OnUnitDied()
{
	PlayDieEffect(GetMesh());
	GetWorldTimerManager().SetTimer(destroy_timer_, this, &AUnit::OnDieFinished, 1.f);
}

void AUnit::PlayRagdollAnimation(UPrimitiveComponent* component)
{
	component->SetCollisionProfileName(TEXT("Ragdoll"));
	component->SetSimulatePhysics(true);
}

void AUnit::PlayDieEffect(USceneComponent* component)
{
	if (death_fx_system_)
	{
		component->SetVisibility(false);
		UNiagaraComponent* fx = UNiagaraFunctionLibrary::SpawnSystemAttached(death_fx_system_, component, FName(""), FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::Type::SnapToTarget, true);
	}
}

void AUnit::OnDieFinished()
{
	Destroy();
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