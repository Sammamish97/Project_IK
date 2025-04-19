/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.20.2024
Summary : Source file for unit.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Characters/Unit.h"

#include "AI/MeleeAIController.h"
#include "Components/CharacterStatComponent.h"
#include "Components/CrowdControlComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/CapsuleComponent.h"

#include "UI/HitPointsUI.h"
#include "Components/ObjectPoolComponent.h"
#include "UI/DamageUI.h"

#include "Subsystems/GlobalBuffSubsystem.h"
#include "Subsystems/DelegateBridgeSubsystem.h"

#include "Structs/BuffData.h"

// Sets default values
AUnit::AUnit()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	character_stat_component_ = CreateDefaultSubobject<UCharacterStatComponent>(TEXT("CharacterStatComponent"));
	hp_UI_ = CreateDefaultSubobject<UWidgetComponent>(TEXT("HP UI"));

	hp_UI_->SetWidgetSpace(EWidgetSpace::Screen);
	hp_UI_->SetDrawSize({ 100, 50 });
	hp_UI_->SetupAttachment(RootComponent);


	cc_component_ = CreateDefaultSubobject<UCrowdControlComponent>(TEXT("CC Component"));

	object_pool_component_ = CreateDefaultSubobject<UObjectPoolComponent>(TEXT("ObjectPool"));
}

const UCharacterStatComponent* AUnit::GetCharacterStat() const
{
	return character_stat_component_;
}

FVector AUnit::GetForwardDir() const
{
	return forward_dir_;
}

void AUnit::SetForwardDir(const FVector& Forward_Dir)
{
	forward_dir_ = Forward_Dir;
}

// Called when the game starts or when spawned
void AUnit::BeginPlay()
{
	Super::BeginPlay();

	UDelegateBridgeSubsystem* subsystem = GetWorld()->GetSubsystem<UDelegateBridgeSubsystem>();
	subsystem->BindOnDied(character_stat_component_, this, &AUnit::Die);

	if (hp_UI_class_)
	{
		hp_UI_->SetWidgetClass(hp_UI_class_);
		hp_UI_->InitWidget();
	}
	UHitPointsUI* ui = Cast<UHitPointsUI>(hp_UI_->GetWidget());
	if (ui)
	{
		subsystem->BindOnCrowdControlChanged(cc_component_, ui, &UHitPointsUI::UpdateAppliedCCs);
		subsystem->BindOnHPChanged(character_stat_component_, ui, &UHitPointsUI::UpdateHPWidget);
		subsystem->BindOnShieldChanged(character_stat_component_, ui, &UHitPointsUI::UpdateShieldWidget);
		subsystem->BindOnBuffChanged(character_stat_component_, ui, &UHitPointsUI::UpdateAppliedBuffs);
	}

	GetGameInstance()->GetSubsystem<UGlobalBuffSubsystem>()->ApplyBuff(this);

	UCapsuleComponent* capsule_comp = FindComponentByClass<UCapsuleComponent>();
	if (capsule_comp)
	{
		capsule_half_height_ = capsule_comp->GetUnscaledCapsuleHalfHeight() / 2.f;
		capsule_radius_ = capsule_comp->GetUnscaledCapsuleRadius();
	}
}

void AUnit::SetDamageUI(FDamageData data, bool is_evaded)
{

	if (is_evaded)
	{
		ADamageUI* missed_ui = Cast<ADamageUI>(object_pool_component_->SpawnFromPool(GetActorTransformForDamageUI()));
		if (missed_ui)
		{
			missed_ui->SetMissed();
		}
	}
	else
	{
		if (data.atk_base_dmg > 0.f)
		{
			ADamageUI* atk_ui = Cast<ADamageUI>(object_pool_component_->SpawnFromPool(GetActorTransformForDamageUI()));
			if (atk_ui)
			{
				atk_ui->SetDamageAmount(data.atk_base_dmg, FLinearColor::White);
			}
		}
		else if (data.atk_base_dmg < 0.f)
		{
			UE_LOG(LogTemp, Error, TEXT("atk_base_dmg less than 0 has come."));
		}

		if (data.skill_power_base_dmg > 0.f)
		{
			ADamageUI* skill_ui = Cast<ADamageUI>(object_pool_component_->SpawnFromPool(GetActorTransformForDamageUI()));
			skill_ui->SetDamageAmount(data.skill_power_base_dmg, FLinearColor::Blue);
		}
		else if (data.skill_power_base_dmg < 0.f)
		{
			UE_LOG(LogTemp, Error, TEXT("skill_power_base_dmg less than 0 has come."));
		}
	}
}

void AUnit::GetDamage(FDamageData data)
{
	switch (data.damage_type)
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
		// @@ TODO: Remove comment mark on the below line when the function has implemented.
		// GetDamageByMagic(data);
		break;
	default:
		break;
	}
}

FDamageData AUnit::ApplyOnAttackEvent(FDamageData dmg_data)
{
	if (dmg_event_map_.Find(EUnitEvent::OnFire))
	{
		if (dmg_event_map_[EUnitEvent::OnFire].IsEmpty() == false)
		{
			for (auto& delegate : dmg_event_map_[EUnitEvent::OnFire])
			{
				if (delegate.IsBound())
				{
					dmg_data = delegate.Execute(dmg_data);
				}
			}
		}
	}
	return dmg_data;
}

void AUnit::Heal(float heal)
{
	character_stat_component_->Heal(heal);

	ADamageUI* ui = Cast<ADamageUI>(object_pool_component_->SpawnFromPool(GetActorTransformForDamageUI()));
	if (ui)
	{
		ui->SetHealAmount(heal);
	}
}

void AUnit::ApplyBuff(FBuffData buff)
{
	character_stat_component_->ApplyBuff(buff);
}

bool AUnit::RemoveBuff(FName BuffName)
{
	return character_stat_component_->RemoveBuff(BuffName);
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

	//Stun Animation 재생
	GetMesh()->SetMaterial(0, test_stun_material_);
	PlayAnimMontage(stun_montage_);
}

void AUnit::FinishStun()
{
	UE_LOG(LogTemp, Display, TEXT("AUnit::FinishStunned"));
	GetMesh()->SetMaterial(0, original_material);
	Cast<AMeleeAIController>(Controller)->SetUnitState(EUnitState::Forwarding);
}

void AUnit::Die()
{
	for (auto& delegate_array : dmg_event_map_)
	{
		for (auto& delegate_elem : delegate_array.Value)
		{
			delegate_elem.Unbind();
		}
	}
	Destroy();
}

FTransform AUnit::GetActorTransformForDamageUI() const noexcept
{
	// Randomize spawn locations
	FTransform transform = GetActorTransform();
	FVector rand_offsets = FVector(0.f, capsule_radius_+ FMath::RandRange(-10.f, 50.f), capsule_half_height_ + FMath::RandRange(-10.f, 50.f));
	
	APlayerController* player_controller = GetWorld()->GetFirstPlayerController();
	if (player_controller && player_controller->PlayerCameraManager)
	{
		rand_offsets = player_controller->PlayerCameraManager->GetCameraRotation().RotateVector(rand_offsets);
	}

	transform.SetLocation(transform.GetLocation() + rand_offsets);
	return transform;
}

void AUnit::GetDamageByDot(FDamageData data)
{
	character_stat_component_->GetDamage(data.atk_base_dmg);
	character_stat_component_->GetDamage(data.skill_power_base_dmg);
	character_stat_component_->RecordDamage(data);
	SetDamageUI(data, false);
}

void AUnit::GetDamageByPEM(FDamageData data)
{


	if (dmg_event_map_.Find(EUnitEvent::OnHitBeforeCalc))
	{
		if (dmg_event_map_[EUnitEvent::OnHitBeforeCalc].IsEmpty() == false)
		{
			for (auto& delegate : dmg_event_map_[EUnitEvent::OnHitBeforeCalc])
			{
				if (delegate.IsBound())data = delegate.Execute(data);
			}
		}
	}

	bool is_evaded = character_stat_component_->CalcDamage(data);
	if (is_evaded == false)
	{
		if (dmg_event_map_.Find(EUnitEvent::OnHitAfterCalc))
		{
			if (dmg_event_map_[EUnitEvent::OnHitAfterCalc].IsEmpty() == false)
			{
				for (auto& delegate : dmg_event_map_[EUnitEvent::OnHitAfterCalc])
				{
					if (delegate.IsBound()) data = delegate.Execute(data);
				}
			}
		}
		character_stat_component_->GetDamage(data.atk_base_dmg);
		character_stat_component_->GetDamage(data.skill_power_base_dmg);
	}
	SetDamageUI(data, is_evaded);
}