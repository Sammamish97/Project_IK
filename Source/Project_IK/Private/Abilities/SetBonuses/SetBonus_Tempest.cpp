/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 4.22.2025
Summary : Source file for the Tempest Set Bonus.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "Abilities/SetBonuses/SetBonus_Tempest.h"

#include "Abilities/Buffs/BuffHandler.h"
#include "Characters/HeroBase.h"
#include "Components/WeaponMechanics.h"
#include "Structs/BuffStatusData.h"
#include "Subsystems/DelegateBridgeSubsystem.h"
#include "Weapons/Guns/GunBase.h"

#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Components/CapsuleComponent.h"

//2세트: 스킬 쿨다운 20% 감소
void USetBonus_Tempest::ActivateEdgeBonus()
{
	Super::ActivateEdgeBonus();
	edge_buff_ = NewObject<UBuffHandler>(this, edge_buff_class_);
	edge_buff_->ApplyBuff(hero_cache_);
}

//3세트: 액티브 스킬을 발동할 시, 자동 장전
void USetBonus_Tempest::ActivateTriangleBonus()
{
	Super::ActivateTriangleBonus();
	GetWorld()->GetSubsystem<UDelegateBridgeSubsystem>()->BindOnUnitEvent(hero_cache_, EUnitEvent::OnActiveSkill, this, &USetBonus_Tempest::TriangleAutoReload);
}

//6세트: 스킬을 사용할 때 마다 쿨 다운 보너스를 5씩 얻음. 최대 30을 얻을 수 있음.
void USetBonus_Tempest::ActivateHexagonBonus()
{
	Super::ActivateHexagonBonus();
	hexagon_buff_ = NewObject<UBuffHandler>(this, hexagon_buff_class_);
	hexagon_buff_->ApplyBuff(hero_cache_);
	GetWorld()->GetSubsystem<UDelegateBridgeSubsystem>()->BindOnUnitEvent(hero_cache_, EUnitEvent::OnActiveSkill, this, &USetBonus_Tempest::HexagonCoolDownBuff);

	if (rune_vfx_system_)
	{
		FVector offset = FVector(0.f, 0.f, -90.f);

		UCapsuleComponent* component = Cast<UCapsuleComponent>(hero_cache_->GetRootComponent());
		if (component)
		{
			offset.Z = -component->GetScaledCapsuleHalfHeight();
		}

		rune_vfx_ = UNiagaraFunctionLibrary::SpawnSystemAttached(rune_vfx_system_, hero_cache_->GetRootComponent(), FName(""), offset, FRotator::ZeroRotator, EAttachLocation::SnapToTarget, true);
		rune_vfx_->SetIntParameter(FName("Level"), 0);
	}
}

void USetBonus_Tempest::TriangleAutoReload()
{
	hero_cache_->GetWeaponMechanics()->GetWeaponActor()->Reload();
}

void USetBonus_Tempest::HexagonCoolDownBuff()
{
	if (cur_buff_stack < 6)
	{
		cur_buff_stack += 1;
		hero_cache_->RemoveBuff(EBuffType::Tempest_Hexagon);
		hero_cache_->ApplyStatusBuff(EBuffType::Tempest_Hexagon, FBuffStatusData{ECharacterStatType::SkillCoolDown, cur_buff_stack * 5.f, false, true});
		if (rune_vfx_)
		{
			rune_vfx_->SetIntParameter(FName("Level"), StaticCast<int32>(cur_buff_stack / 2));
		}
	}
}