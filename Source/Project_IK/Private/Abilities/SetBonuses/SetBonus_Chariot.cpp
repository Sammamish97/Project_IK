/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 3.9.2025
Summary : Source file for the Chariot Set Bonus.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Abilities/SetBonuses/SetBonus_Chariot.h"

#include "Characters/HeroBase.h"
#include "Structs/BuffStatusData.h"
#include "Subsystems/DelegateBridgeSubsystem.h"

#include "NiagaraFunctionLibrary.h"

#include "Subsystems/AudioManagerSubsystem.h"

//2세트: 공격력 10% + 체력 10%
void USetBonus_Chariot::ActivateEdgeBonus()
{
	Super::ActivateEdgeBonus();
	//IKTODO: 테스트 이후 정상화 시켜야 함.
	// hero_cache_->ApplyBuff(FBuffStatusData(TEXT("Chariot_Edge"), ECharacterStatType::AttackPower, 10.f, true, true));
	// hero_cache_->ApplyBuff(FBuffStatusData(TEXT("Chariot_Edge"), ECharacterStatType::HitPoints, 10.f, true, true));
}

//3세트: 장전 시 최대 체력의 15%에 해당하는 실드 획득.
void USetBonus_Chariot::ActivateTriangleBonus()
{
	Super::ActivateTriangleBonus();
	GetWorld()->GetSubsystem<UDelegateBridgeSubsystem>()->BindOnUnitEvent(hero_cache_, EUnitEvent::OnReload, this, &USetBonus_Chariot::GetShield);
}

//6세트: 적 처치/이동/CC기에 걸렸을 때 최대 체력의 15%에 해당하는 실드 획득 + 해당 실드의 지속시간 동안 10%의 흡혈 획득.
void USetBonus_Chariot::ActivateHexagonBonus()
{
	Super::ActivateHexagonBonus();
	GetWorld()->GetSubsystem<UDelegateBridgeSubsystem>()->BindOnUnitEvent(hero_cache_, EUnitEvent::OnStun, this, &USetBonus_Chariot::GetShieldAndLifeSteal);
	GetWorld()->GetSubsystem<UDelegateBridgeSubsystem>()->BindOnUnitEvent(hero_cache_, EUnitEvent::OnReposition, this, &USetBonus_Chariot::GetShieldAndLifeSteal);
	GetWorld()->GetSubsystem<UDelegateBridgeSubsystem>()->BindOnUnitEvent(hero_cache_, EUnitEvent::OnEliminate, this, &USetBonus_Chariot::GetShieldAndLifeSteal);
}

void USetBonus_Chariot::GetShield()
{
	hero_cache_->AcquireShield(hero_cache_->GetCharacterStat()->GetHitPoint() * 0.15f, shield_duration_);

	UNiagaraFunctionLibrary::SpawnSystemAttached(shield_effect_, hero_cache_->GetRootComponent(), FName(""), FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::Type::SnapToTarget, true);
	UAudioManagerSubsystem::Get(this)->PlayAtLocation(EAudioType::ChariotShield, hero_cache_->GetActorLocation());
}

void USetBonus_Chariot::GetShieldAndLifeSteal()
{
	GetShield();

	//IKTODO: 테스트 이후 정상화 시켜야 함.
	//hero_cache_->ApplyBuff(FBuffStatusData("Chariot_Hexagon", ECharacterStatType::LifeSteal, life_steal_percentage, true, shield_duration_));
}