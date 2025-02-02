/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.20.2024
Summary : Source file for unit.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Characters/Unit.h"

#include "AIController.h"
#include "AI/MeleeAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/ArmorMechanics.h"
#include "Components/CharacterStatComponent.h"
#include "Components/CrowdControlComponent.h"
#include "Components/WidgetComponent.h"

#include "UI/HitPointsUI.h"
#include "Components/ObjectPoolComponent.h"
#include "UI/DamageUI.h"

// Sets default values
AUnit::AUnit()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	character_stat_component_ = CreateDefaultSubobject<UCharacterStatComponent>(TEXT("CharacterStatComponent"));
	hp_UI_ = CreateDefaultSubobject<UWidgetComponent>(TEXT("HP UI"));
	
	hp_UI_->SetWidgetSpace(EWidgetSpace::Screen);
	hp_UI_->SetDrawSize({100, 50});
	hp_UI_->SetupAttachment(RootComponent);

	character_stat_component_->Die.AddDynamic(this, &AUnit::Die);


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

	if (hp_UI_class_)
	{
		hp_UI_->SetWidgetClass(hp_UI_class_);
	}
	Cast<UHitPointsUI>(hp_UI_->GetWidget())->BindNecessaryComponents(character_stat_component_, cc_component_);
}

void AUnit::SetDamageUI(float dmg)
{
	ADamageUI* ui = Cast<ADamageUI>(object_pool_component_->SpawnFromPool(GetActorTransformForDamageUI()));
    	if (ui)
    	{
    		if (dmg > 0.f)
    		{
    			ui->SetDamageAmount(dmg);
    		}
    		else
    		{
    			ui->SetMissed();
    		}
    	}
}

void AUnit::GetDamage(FDamageData data)
{
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

void AUnit::ApplyBuff(FBuff buff)
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

void AUnit::GetStunned(float stun_duration)
{
	UE_LOG(LogTemp, Display, TEXT("AUnit::GetStunned"));
	if(GetWorld()->GetTimerManager().IsTimerActive(stun_timer_) == false)
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
	Destroy();
}

FTransform AUnit::GetActorTransformForDamageUI() const noexcept
{
	// Randomize spawn locations
	FTransform transform = GetActorTransform();
	transform.SetLocation(transform.GetLocation() + FVector(10.f, 0.f, 0.f) + FVector(FMath::RandRange(0.f, 10.f), 0.f, FMath::RandRange(0.f, 10.f)));
	return transform;
}
