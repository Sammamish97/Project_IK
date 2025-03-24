/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 11.27.2024
Summary : Source file for Item class.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Abilities/Item.h"
#include "Managers/EnumCluster.h"
#include "Characters/Unit.h"
#include "Components/CharacterStatComponent.h"
#include "Structs/TargetResult.h"
#include "Interfaces/Damageable.h"
#include "Abilities/SmokeRegion.h"

void UItem::InitializeItemUsingData(FItemData item_data)
{
	item_data_ = item_data;
}

void UItem::UseItem(UWorld* world, const FTargetResult& TargetResult)
{
	switch (item_data_.item_logic_)
	{
	case EItemLogicType::None:
		break;
	case EItemLogicType::RestoreHP:
		RestoreHP(TargetResult.target_actors_);
		break;
	case EItemLogicType::LaunchMissile:
		LaunchMissile(TargetResult.target_actors_);
		break;
	case EItemLogicType::AttackSpeedStimuli:
		AttackSpeedStimuli(TargetResult.target_actors_);
		break;
	case EItemLogicType::SmokeGrenade:
		SmokeGrenade(world, TargetResult.target_location_, TargetResult.target_parameters_.radius_);
		break;
	case EItemLogicType::Flashbang:
		Flashbang(TargetResult.target_actors_);
		break;
	default:
		break;
	}
}

FItemData UItem::GetData() const
{
	return item_data_;
}

FItemData* UItem::GetDataPtr()
{
	return &item_data_;
}

FTargetParameters UItem::GetTargetParameters() const
{
	return item_data_.target_params_;
}

void UItem::RestoreHP(TArray<AActor*> actors)
{
	for (AActor* actor : actors)
	{
		TWeakObjectPtr<UCharacterStatComponent> stat = actor->GetComponentByClass<UCharacterStatComponent>();
		if (stat.IsValid())
		{
			static constexpr float heal_amount = 50.f;
			// Instant heal immediately.
			stat->Heal(heal_amount);
			int32 heal_count = 0;
			const int32 max_heal_count = 4;
			FTimerDelegate delegate;
			FTimerHandle heal_handler;
			UWorld* world = actor->GetWorld();
			if (world)
			{
				FTimerManager& timer_manager = world->GetTimerManager();
				delegate.BindLambda([stat, &heal_count, max_heal_count, &timer_manager, &heal_handler]() {
					if (!stat.IsValid())
					{
						timer_manager.ClearTimer(heal_handler);
						return;
					}
					stat->Heal(heal_amount);

					++heal_count;

					if (heal_count >= max_heal_count)
					{
						timer_manager.ClearTimer(heal_handler);
					}
					});

				timer_manager.SetTimer(heal_handler, delegate, 2.5f, true);

			}
		}
	}
}

void UItem::LaunchMissile(TArray<AActor*> actors)
{
	for (int32 i = 0; i < actors.Num(); i++)
	{
		if (actors[i])
		{
			IDamageable* damageable_actor = Cast<IDamageable>(actors[i]);
			if (damageable_actor)
			{
				FDamageData data = {50.f, 0.f,  EDamageType::Explosive, nullptr	};
				damageable_actor->GetDamage(data);
			}
		}
	}
}

void UItem::AttackSpeedStimuli(TArray<AActor*> actors)
{
	for (int32 i = 0; i < actors.Num(); i++)
	{
		AUnit* unit = Cast<AUnit>(actors[i]);
		if (unit)
		{
			unit->ApplyBuff(FBuff(TEXT("Item_Stimuli"), ECharacterStatType::AttackSpeed, 1.2f, true, 10.f));
		}
	}

}

void UItem::SmokeGrenade(UWorld* World, FVector TargetLocation, float Radius)
{
	if (World)
	{
		FActorSpawnParameters spawn_params;
		spawn_params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		ASmokeRegion* spawned_smoke = World->SpawnActor<ASmokeRegion>(smoke_region_class_, TargetLocation, FRotator::ZeroRotator, spawn_params);
		if (spawned_smoke)
		{
			spawned_smoke->SetLifeSpan(10.f);
			spawned_smoke->SetSphereRadius(Radius);
			
		}
	}
}

void UItem::Flashbang(TArray<AActor*> actors)
{
	for (int32 i = 0; i < actors.Num(); i++)
	{
		AUnit* unit = Cast<AUnit>(actors[i]);
		if (unit)
		{
			unit->ApplyCrowdControl(ECCType::Stun, 5.f);
		}
	}

}
