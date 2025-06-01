/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 4.22.2025
Summary : Source file for Dagger Set Bonus.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "Abilities/SetBonuses/SetBonus_Dagger.h"

#include "Characters/EnemyBase.h"
#include "Characters/HeroBase.h"
#include "Components/ObjectPoolComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Structs/BuffData.h"
#include "Subsystems/DelegateBridgeSubsystem.h"

#include "Weapons/Runes/DaggerProjectiles.h"

USetBonus_Dagger::USetBonus_Dagger()
{
	bullet_pool_ = CreateDefaultSubobject<UObjectPoolComponent>("BulletPool");
}

//2세트: 공격속도 10% + 치명타율 + 5%
void USetBonus_Dagger::ActivateEdgeBonus()
{
	Super::ActivateEdgeBonus();
	hero_cache_->ApplyBuff(FBuffData(TEXT("Dagger_Edge"), ECharacterStatType::AttackSpeed, 10.f, true, true));
	hero_cache_->ApplyBuff(FBuffData(TEXT("Dagger_Edge"), ECharacterStatType::CriticalHitRate, 5.f, true, true));
}

//3세트: 장전 시 2초간 치명타율 10% 추가.
void USetBonus_Dagger::ActivateTriangleBonus()
{
	Super::ActivateTriangleBonus();
	GetWorld()->GetSubsystem<UDelegateBridgeSubsystem>()->BindOnUnitEvent(hero_cache_, EUnitEvent::OnReload, this, &USetBonus_Dagger::TriangleReloadCritRateBuff);
}

//6세트: 치명타 공격을 발사할 때 마다 데미지가 치명타 확률에 비례하는 2발의 추가 탄환 발사.
void USetBonus_Dagger::ActivateHexagonBonus()
{
	Super::ActivateHexagonBonus();
	bullet_pool_->InitializePool();
	bullet_pool_->SetObjectClass(dagger_actor_);
	GetWorld()->GetSubsystem<UDelegateBridgeSubsystem>()->BindOnUnitEvent(hero_cache_, EUnitEvent::OnCriticalFire, this, &USetBonus_Dagger::HexagonBonus);
}

void USetBonus_Dagger::TriangleReloadCritRateBuff()
{
	hero_cache_->ApplyBuff({"Dagger_CritBuff", ECharacterStatType::CriticalHitRate, 20.f, true, 5.f});
}

void USetBonus_Dagger::HexagonBonus()
{
	TArray<AActor*> ignore_actors;
	TArray<AActor*> out_actors;
	TArray<TEnumAsByte<EObjectTypeQuery>> traceObjectTypes;
	
	UKismetSystemLibrary::SphereOverlapActors(GetWorld(), hero_cache_->GetActorLocation(),
				hero_cache_->GetCharacterStat()->GetSightRange(),
				traceObjectTypes, AEnemyBase::StaticClass(), ignore_actors, out_actors);
	

	const FDamageData dmg_data = { dagger_damage_, 0, EDamageType::Projectile, hero_cache_};


	if (out_actors.Num() >= 2)
	{
		SpawnDaggers(out_actors[0]->GetActorLocation(), dmg_data);
		SpawnDaggers(out_actors[1]->GetActorLocation(), dmg_data);

	}else if (out_actors.Num() == 1)
	{
		SpawnDaggers(out_actors[0]->GetActorLocation(), dmg_data);
	}
}

void USetBonus_Dagger::SpawnDaggers(const FVector& target_position, const FDamageData& damage_data)
{
	const FVector position = GetDaggerSpawnPosition();
	FRotator rotator = UKismetMathLibrary::FindLookAtRotation(position, target_position);
	ADaggerProjectiles* dagger = Cast<ADaggerProjectiles>(bullet_pool_->SpawnFromPool(rotator, position));
	if (dagger)
	{
		dagger->SetDamageData(damage_data);
		dagger->BeginDaggerMovements();
	}
	
}

FVector USetBonus_Dagger::GetDaggerSpawnPosition()
{
	return hero_cache_->GetActorLocation() + position_offset + (FMath::VRand() * random_offset_radius + FVector(0.f, 0.f, random_offset_radius / 2.f));
}
