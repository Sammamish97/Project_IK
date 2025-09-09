/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 08.12.2025
Summary : Source file for audio manager subsystem.
					It manages all audio in this project except audio bound in button.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Subsystems/AudioManagerSubsystem.h"

#include "WorldSettings/DeveloperSettings/AudioConfigSettings.h"
#include "Sound/SoundClass.h"
#include "Sound/SoundMix.h"
#include "Kismet/GameplayStatics.h"
#include "DataAssets/AudioDataAsset.h"

void UAudioManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	const UAudioConfigSettings* settings = GetDefault<UAudioConfigSettings>();
	if (settings)
	{
		soft_audio_cues_ = settings->audio_data_asset_;
		soft_master_mix_ = settings->master_mix_;
		soft_master_channel_ = settings->master_channel_;
		soft_bgm_channel_ = settings->bgm_channel_;
		soft_sfx_channel_ = settings->sfx_channel_;

		ApplyVolumes(master_volume_, bgm_volume_, sfx_volume_);
	}
}

void UAudioManagerSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

UAudioManagerSubsystem* UAudioManagerSubsystem::Get(const UObject* world_context)
{
	UWorld* world = world_context->GetWorld();
	if (world)
	{
		return world->GetGameInstance()->GetSubsystem<UAudioManagerSubsystem>();
	}
	return nullptr;
}

void UAudioManagerSubsystem::ApplyVolumes(float master, float bgm, float sfx)
{
	LoadReferences();

	if (master_channel_)
	{
		master_channel_->Properties.Volume = FMath::Clamp(master, 0.f, 1.f);
	}
	if (bgm_channel_)
	{
		bgm_channel_->Properties.Volume = FMath::Clamp(bgm, 0.f, 1.f);
	}
	if (sfx_channel_)
	{
		sfx_channel_->Properties.Volume = FMath::Clamp(sfx, 0.f, 1.f);
	}

	if (master_mix_)
	{
		UGameplayStatics::PushSoundMixModifier(GetWorld(), master_mix_);
	}
}

const FCueEntry* UAudioManagerSubsystem::GetCue(EAudioType audio_type)
{
	return audio_cues_ ? audio_cues_->Find(audio_type) : nullptr;
}

USoundBase* UAudioManagerSubsystem::GetSoundClass(EAudioType audio_type, float& volume, float& pitch)
{
	LoadReferences();

	const FCueEntry* entry = GetCue(audio_type);
	if (!entry || !entry->soft_sound_.ToSoftObjectPath().IsValid())
	{
		return nullptr;
	}

	USoundBase* sound = LoadSync(entry->soft_sound_);
	if (!sound)
	{
		return nullptr;
	}

	volume = entry->volume_ * volume;
	pitch = entry->pitch_ * pitch;

	if (USoundClass* sound_channel = LoadSync(entry->soft_sound_channel_))
	{
		sound->SoundClassObject = sound_channel;
	}
	else if (!sound->SoundClassObject)
	{
		// Set a default to sounds that have not default channels
		sound->SoundClassObject = master_channel_;
	}

	if (entry->soft_sound_concurrency_.IsNull() == false && sound->bOverrideConcurrency == false && sound->ConcurrencySet.IsEmpty())
	{
		if (USoundConcurrency* sound_concurrency = LoadSync(entry->soft_sound_concurrency_))
		{
			sound->ConcurrencySet.Add(sound_concurrency);
		}
	}

	return sound;
}

float UAudioManagerSubsystem::GetMasterVolume() const
{
	return master_volume_;
}

float UAudioManagerSubsystem::GetBGMVolume() const
{
	return bgm_volume_;
}

float UAudioManagerSubsystem::GetSFXVolume() const
{
	return sfx_volume_;
}

void UAudioManagerSubsystem::SetMasterVolume(float V)
{
	master_volume_ = V;
	ApplyVolumes(master_volume_, bgm_volume_, sfx_volume_);
}

void UAudioManagerSubsystem::SetBGMVolume(float V)
{
	bgm_volume_ = V;
	ApplyVolumes(master_volume_, bgm_volume_, sfx_volume_);
}

void UAudioManagerSubsystem::SetSFXVolume(float V)
{
	sfx_volume_ = V;
	ApplyVolumes(master_volume_, bgm_volume_, sfx_volume_);
}

UAudioComponent* UAudioManagerSubsystem::Play2D(EAudioType audio_type, float volume, float pitch)
{
	USoundBase* sound = GetSoundClass(audio_type, volume, pitch);
	return UGameplayStatics::SpawnSound2D(GetWorld(), sound, volume, pitch);
}

UAudioComponent* UAudioManagerSubsystem::PlayAtLocation(EAudioType audio_type, const FVector& location, float volume, float pitch)
{
	USoundBase* sound = GetSoundClass(audio_type, volume, pitch);
	return UGameplayStatics::SpawnSoundAtLocation(GetWorld(), sound, location, FRotator::ZeroRotator, volume, pitch);
}

UAudioComponent* UAudioManagerSubsystem::PlayAttached(EAudioType audio_type, USceneComponent* attach_to, FName socket, FVector offset, EAttachLocation::Type attach_type, bool bStopWithOwner, float volume, float pitch)
{
	USoundBase* sound = GetSoundClass(audio_type, volume, pitch);
	return UGameplayStatics::SpawnSoundAttached(sound, attach_to, socket, offset, attach_type, bStopWithOwner, volume, pitch);
}

void UAudioManagerSubsystem::LoadReferences()
{
	if (!audio_cues_)
	{
		audio_cues_ = LoadSync(soft_audio_cues_);
	}
	if (!master_mix_)
	{
		master_mix_ = LoadSync(soft_master_mix_);
	}

	if (!master_channel_)
	{
		master_channel_ = LoadSync(soft_master_channel_);
	}
	if (!bgm_channel_)
	{
		bgm_channel_ = LoadSync(soft_bgm_channel_);
	}
	if (!sfx_channel_)
	{
		sfx_channel_ = LoadSync(soft_sfx_channel_);
	}
}
