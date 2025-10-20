/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.24.2025
Summary : Source file for one Maintain buff.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Abilities/Buffs/BF_Maintain.h"

#include "Characters/Unit.h"

#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

void UBF_Maintain::ApplyBuff(AUnit* target)
{
	target_cache_ = target;
	target->AcquireShield(shield_amount_, 5.f);
	FTimerDelegate heal_del = FTimerDelegate::CreateUObject(this, &UBF_Maintain::RemoveBuff, target_cache_.Get());
	FTimerDelegate heal_tick_del = FTimerDelegate::CreateUObject(this, &UBF_Maintain::Heal);

	GetWorld()->GetTimerManager().SetTimer(heal_timer_handle_, heal_del, heal_duration_, false);
	GetWorld()->GetTimerManager().SetTimer(heal_tick_handle_, heal_tick_del, 0.5f, true);
	
	if (maintain_vfx_)
	{
		maintain_vfx_component_ = UNiagaraFunctionLibrary::SpawnSystemAttached(maintain_vfx_, target->GetRootComponent(), FName(""), FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::Type::SnapToTarget, false);
	}
}

void UBF_Maintain::RemoveBuff(AUnit* target)
{
	GetWorld()->GetTimerManager().ClearTimer(heal_timer_handle_);
	GetWorld()->GetTimerManager().ClearTimer(heal_tick_handle_);
	target->RemoveBuffUI(buff_type_);

	if (maintain_vfx_)
	{
		maintain_vfx_component_->Deactivate();
	}
}

void UBF_Maintain::Heal()
{
	if (auto target = target_cache_.Get())
	{
		target->Heal(heal_per_half_sec_);
	}
}