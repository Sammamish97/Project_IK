/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 04.21.2025
Summary : Source file for an actor class for FateSpiral.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Abilities/ActiveSkills/FateSpiral.h"

#include "Kismet/GameplayStatics.h"
#include "WorldSettings/IKGameModeBase.h"

#include "Characters/HeroBase.h"
#include "Characters/EnemyBase.h"
#include "Components/CharacterStatComponent.h"

// Sets default values
AFateSpiral::AFateSpiral()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AFateSpiral::SetSkillOwner(AActor* skill_owner)
{
	skill_owner_cache_ = skill_owner;
}

void AFateSpiral::SetDepartureActor(AActor* departure)
{
	if (departure)
	{
		departure_ = departure;
	}
}

void AFateSpiral::SetArrivalActor(AActor* arrival)
{
	if (arrival)
	{
		arrival_ = arrival;
	}
}

void AFateSpiral::SetRange(float range)
{
	range_squared_ = range * range;
}

// Called when the game starts or when spawned
void AFateSpiral::BeginPlay()
{
	Super::BeginPlay();

	jump_count_ = 0;
	traversed_actors_.Empty();

	GetWorld()->GetTimerManager().SetTimer(
		fate_sprial_handler_,
		this, &AFateSpiral::ConductLogic,
		0.5f,
		true,
		0.5f
	);
}

void AFateSpiral::ConductLogic()
{
	++jump_count_;

	// @@ TODO: Need additional logic if departure became NULLPTR
	if (arrival_)
	{
		if (arrival_->IsA<AHeroBase>())
		{
			HealAlly();
		}
		else if (arrival_->IsA<AEnemyBase>())
		{
			DamageEnemy();
		}

		if (jump_count_ >= 4)
		{
			EndLogic();
		}
		else
		{
			traversed_actors_.Add(arrival_);

			departure_ = arrival_;
			arrival_ = FindNextTarget();

			if (!arrival_)
			{
				EndLogic();
			}
		}
	}
	else
	{
		EndLogic();
	}
}

void AFateSpiral::HealAlly()
{
	AUnit* unit = Cast<AUnit>(arrival_);

	float skill_power = GetOwnerSkillPower();
	unit->Heal(heal_amount_ + skill_power * heal_scaling_factor_);
}

void AFateSpiral::DamageEnemy()
{
	IDamageable* damageable = Cast<IDamageable>(arrival_);

	float skill_power = GetOwnerSkillPower();
	damageable->GetDamage(FDamageData(0.f, damage_amount_ + skill_power * damage_scaling_factor_, EDamageType::Magic, skill_owner_cache_, arrival_));
}

AActor* AFateSpiral::FindNextTarget()
{
	AActor* result = nullptr;
	float min_radius = range_squared_;

	AIKGameModeBase* game_mode = Cast<AIKGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (game_mode)
	{
		TArray<AActor*> actor_containers = game_mode->GetEnemyContainers();
		if (arrival_->IsA<AEnemyBase>())
		{
			actor_containers = game_mode->GetHeroContainer();
		}
		for (AActor* actor : actor_containers)
		{
			if (actor)
			{
				FVector to_actor = actor->GetActorLocation() - arrival_->GetActorLocation();

				float squared_distance_to_actor = to_actor.SizeSquared();
				if (squared_distance_to_actor <= min_radius && !traversed_actors_.Contains(actor))
				{
					result = actor;
					min_radius = squared_distance_to_actor;
				}
			}
		}
	}

	return result;
}

float AFateSpiral::GetOwnerSkillPower()
{
	AActor* actor = skill_owner_cache_.Get();

	// If actor is still alive, update skill power for a case got buffed.
	if (actor)
	{
		AUnit* unit = Cast<AUnit>(actor);
		if (unit)
		{
			owner_skill_power_ = unit->GetCharacterStat()->GetSkillPower();
		}
	}
	return owner_skill_power_;
}

void AFateSpiral::EndLogic()
{
	GetWorld()->GetTimerManager().ClearTimer(fate_sprial_handler_);
	Destroy();
}

// Called every frame
void AFateSpiral::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (arrival_ && departure_)
	{
		FColor color = FColor::Black;
		if (arrival_->IsA<AHeroBase>())
		{
			color = FColor::Green;
		}
		else if (arrival_->IsA<AEnemyBase>())
		{
			color = FColor::Red;
		}

		DrawDebugLine(GetWorld(), departure_->GetActorLocation(), arrival_->GetActorLocation(),
			color, false, -1, 0U, 8.f);
	}
}

