/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 4.22.2025
Summary : Source file for Dagger Set Bonus.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "Abilities/SetBonuses/SetBonus_Dagger.h"

#include "Characters/HeroBase.h"
#include "Kismet/KismetMathLibrary.h"
#include "Structs/BuffData.h"
#include "Subsystems/DelegateBridgeSubsystem.h"

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
	GetWorld()->GetSubsystem<UDelegateBridgeSubsystem>()->BindOnUnitDamageEvent(hero_cache_, EUnitEvent::OnReload, this, &USetBonus_Dagger::TriangleReloadCritRateBuff, FName(TEXT("USetBonus_Dagger::TriangleBonus")));
}

//6세트: 치명타 공격을 발사할 때 마다 데미지가 치명타 확률에 비례하는 2발의 추가 탄환 발사.
void USetBonus_Dagger::ActivateHexagonBonus()
{
	Super::ActivateHexagonBonus();
	GetWorld()->GetSubsystem<UDelegateBridgeSubsystem>()->BindOnUnitDamageEvent(hero_cache_, EUnitEvent::OnCriticalFire, this, &USetBonus_Dagger::HexagonBonus, FName(TEXT("USetBonus_Dagger::HexagonBonus")));
}

FDamageData USetBonus_Dagger::TriangleReloadCritRateBuff(FDamageData dmg_data)
{
	hero_cache_->ApplyBuff({"Dagger_CritBuff", ECharacterStatType::CriticalHitRate, 20.f, true, 5.f});
	return dmg_data;
}

FDamageData USetBonus_Dagger::HexagonBonus(FDamageData dmg_data)
{
	UE_LOG(LogTemp, Display, TEXT("Dagger_CritBuff"));
	TWeakObjectPtr<AActor> target_ptr = hero_cache_->GetAttackTarget();
	if (AActor* attack_target = target_ptr.Get())
	{
		FVector muzzle = hero_cache_->GetActorLocation() + FVector(0, 200, 200);
		FRotator rotation = UKismetMathLibrary::FindLookAtRotation(muzzle, attack_target->GetActorLocation());
		FTransform spawn_transform(rotation, muzzle);
		GetWorld()->SpawnActor<AActor>(bonus_bullet_, spawn_transform);
	}
	return dmg_data;
}