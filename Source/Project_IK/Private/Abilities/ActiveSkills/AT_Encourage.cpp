/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 04.19.2025
Summary : Source file for an active skill named Encourage.
					Buffs of attack speed & skill cool-time in a range of allies.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Abilities/ActiveSkills/AT_Encourage.h"

#include "Abilities/Buffs/BuffHandler.h"
#include "Structs/TargetResult.h"
#include "Structs/BuffStatusData.h"
#include "Characters/HeroBase.h"

//IKTODO: 실드에 계수를 추가하는것도 좋을듯 하다.
#include "NiagaraFunctionLibrary.h"
#include "Components/CapsuleComponent.h"
#include "NiagaraComponent.h"

UAT_Encourage::UAT_Encourage()
{
	target_param_ = FTargetParameters(ETargetingMode::Location, ETargetType::Allies, 0.f, 1000.f, false);
}

void UAT_Encourage::InitActiveSkill(AActor* skill_owner, const FActiveSkillData& skill_data)
{
	Super::InitActiveSkill(skill_owner, skill_data);
	buff_ = NewObject<UBuffHandler>(this, buff_class_);
	cool_time_ = skill_data.cool_time_;
}

void UAT_Encourage::OnEnterCasting()
{
	Super::OnEnterCasting();
	Cast<AUnit>(skill_owner_)->PlayAnimMontage(casting_anim_montage_);
}

bool UAT_Encourage::ActivateSkill(const FTargetResult& TargetResult)
{
	SpawnSkillParticle(TargetResult);


	for (AActor* ally : TargetResult.target_actors_)
	{
		if (AUnit* casted_hero = Cast<AUnit>(ally))
		{
			buff_->ApplyBuff(casted_hero);

			UNiagaraFunctionLibrary::SpawnSystemAttached(encouraged_target_fx_, casted_hero->GetMesh(), FName(""), FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::Type::SnapToTarget, true);
		}
	}

	return Super::ActivateSkill(TargetResult);
}

void UAT_Encourage::SpawnSkillParticle(const FTargetResult& TargetResult)
{
	FVector ground_offset = FVector::ZeroVector;

	UCapsuleComponent* capsule = Cast<UCapsuleComponent>(skill_owner_->GetRootComponent());
	if (capsule)
	{
		ground_offset.Z = capsule->GetScaledCapsuleHalfHeight();
	}
	UNiagaraComponent* component = UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, encourage_fx_, TargetResult.target_location_ - ground_offset);
	if (component)
	{
		component->SetFloatParameter(FName("Radius"), target_param_.radius_);
	}
}
