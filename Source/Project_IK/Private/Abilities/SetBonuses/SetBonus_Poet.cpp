/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 4.24.2025
Summary : Source file for Poet Set Bonus.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Abilities/SetBonuses/SetBonus_Poet.h"

#include "Characters/HeroBase.h"
#include "Kismet/KismetMathLibrary.h"
#include "Weapons/Skills/SentryGun.h"
#include "Structs/BuffStatusData.h"
#include "Subsystems/DelegateBridgeSubsystem.h"

//2세트: 스킬 위력 + 10% + 스킬 쿨다운 + 10%
void USetBonus_Poet::ActivateEdgeBonus()
{
	Super::ActivateEdgeBonus();
	//IKTODO: 테스트 이후 정상화 시켜야 함.
	// hero_cache_->ApplyBuff(FBuffStatusData(TEXT("Poet_Edge"), ECharacterStatType::SkillPower, 10.f, true, true));
	// hero_cache_->ApplyBuff(FBuffStatusData(TEXT("Poet_Edge"), ECharacterStatType::SkillCoolDown, 10.f, true, true));
}

//3세트: 액티브 스킬 사용 시, 25%의 확률로 미니포탑 소환.
void USetBonus_Poet::ActivateTriangleBonus()
{
	Super::ActivateTriangleBonus();
	GetWorld()->GetSubsystem<UDelegateBridgeSubsystem>()->BindOnUnitEvent(hero_cache_, EUnitEvent::OnActiveSkill, this, &USetBonus_Poet::PoetTriangle);
}

//6세트: 액티브 스킬 사용 시, 75%의 확률로 미니 소환물 소환.
void USetBonus_Poet::ActivateHexagonBonus()
{
	Super::ActivateHexagonBonus();
	GetWorld()->GetSubsystem<UDelegateBridgeSubsystem>()->BindOnUnitEvent(hero_cache_, EUnitEvent::OnActiveSkill, this, &USetBonus_Poet::PoetHexagon);
}

void USetBonus_Poet::PoetTriangle()
{
	if (FMath::RandRange(0.f, 100.f) < 25.f)
	{
		TWeakObjectPtr<AActor> target_ptr = hero_cache_->GetAttackTarget();
		if (AActor* target_actor = target_ptr.Get())
		{
			auto location = (target_actor->GetActorLocation() + hero_cache_->GetActorLocation()) * 0.5f;
			location.X += FMath::RandRange(-100.f, 100.f);
			location.Y += FMath::RandRange(-100.f, 100.f);
			FRotator rotation = UKismetMathLibrary::FindLookAtRotation(location, target_actor->GetActorLocation());
			GetWorld()->SpawnActor<AActor>(sentry_gun_class_, location, rotation);
		}
		else
		{
			auto location = hero_cache_->GetActorLocation() + FVector(300, 0, 0);
			FRotator rotation = FRotator(1, 0, 0);
			GetWorld()->SpawnActor<AActor>(sentry_gun_class_, location, rotation);
		}
	}
}

void USetBonus_Poet::PoetHexagon()
{
	if (FMath::RandRange(0.f, 100.f) < 75.f)
	{
		TWeakObjectPtr<AActor> target_ptr = hero_cache_->GetAttackTarget();
		if (AActor* target_actor = target_ptr.Get())
		{
			auto location = (target_actor->GetActorLocation() + hero_cache_->GetActorLocation()) * 0.5f;
			location.X += FMath::RandRange(-100.f, 100.f);
			location.Y += FMath::RandRange(-100.f, 100.f);
			FRotator rotation = UKismetMathLibrary::FindLookAtRotation(location, target_actor->GetActorLocation());
			GetWorld()->SpawnActor<AActor>(sentry_gun_class_, location, rotation);
		}
		else
		{
			auto location = hero_cache_->GetActorLocation() + FVector(300, 0, 0);
			FRotator rotation = FRotator(1, 0, 0);
			GetWorld()->SpawnActor<AActor>(sentry_gun_class_, location, rotation);
		}
	}
}