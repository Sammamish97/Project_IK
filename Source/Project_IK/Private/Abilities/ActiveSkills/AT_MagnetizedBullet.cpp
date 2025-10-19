/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 04.17.2025
Summary : Source file for Magnetized Bullet Active Skill.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "Abilities/ActiveSkills/AT_MagnetizedBullet.h"

#include "Abilities/Buffs/BuffHandler.h"
#include "Characters/HeroBase.h"

#include "Subsystems/AudioManagerSubsystem.h"
#include "Components/AudioComponent.h"
#include "Abilities/Buffs/BF_MagnetizedBullet.h"

#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

UAT_MagnetizedBullet::UAT_MagnetizedBullet()
{
	target_param_ = FTargetParameters(ETargetingMode::Actor, ETargetType::Allies, 0.f, 0.f, true);
	cool_time_ = 5.f;
}

void UAT_MagnetizedBullet::InitActiveSkill(AActor* skill_owner, const FActiveSkillData& skill_data)
{
	Super::InitActiveSkill(skill_owner, skill_data);
	buff_ = NewObject<UBuffHandler>(this, buff_class_);
}

bool UAT_MagnetizedBullet::ActivateSkill(const FTargetResult& TargetResult)
{
	AHeroBase* hero = Cast<AHeroBase>(skill_owner_);
	if (hero)
	{
		buff_->ApplyBuff(hero);

		ApplyFXs(hero);
		return Super::ActivateSkill(TargetResult);
	}
	return false;
}

void UAT_MagnetizedBullet::ApplyFXs(AHeroBase* hero)
{
	UAudioComponent* audio_component = nullptr;
	if (skill_owner_)
	{
		audio_component = UAudioManagerSubsystem::Get(this)->PlayAtLocation(EAudioType::MagnetizedBulletsActivated, skill_owner_->GetActorLocation());
	}
	else
	{
		audio_component = UAudioManagerSubsystem::Get(this)->Play2D(EAudioType::MagnetizedBulletsActivated);
	}

	float duration = 5.f;
	UBF_MagnetizedBullet* buff_mb = Cast<UBF_MagnetizedBullet>(buff_);
	if (buff_mb)
	{
		duration = buff_mb->GetDuration();
	}

	if (audio_component)
	{
		audio_component->FadeOut(duration, 0.2f);
	}

	hero->ChangeGunShotSoundTemporariliy(EAudioType::MagnetizedGunShot, duration);


	if (magnetized_invoked_particle_.IsValid() == false)
	{
		magnetized_invoked_particle_.LoadSynchronous();
	}
	UNiagaraComponent* niagara_component = UNiagaraFunctionLibrary::SpawnSystemAttached(magnetized_invoked_particle_.Get(), skill_owner_->GetRootComponent(), FName(""), FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset, true);
	if (niagara_component)
	{
		niagara_component->SetVariableFloat(FName("duration"), duration);
	}
}
