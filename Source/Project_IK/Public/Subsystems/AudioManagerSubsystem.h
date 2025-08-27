/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 08.12.2025
Summary : Header file for audio manager subsystem.
					It manages all audio in this project except audio bound in button.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Managers/EnumCluster.h"
#include "Engine/EngineTypes.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "AudioManagerSubsystem.generated.h"

struct FCueEntry;
class UAudioDataAsset;
class USoundMix;
enum class EAudioType : uint8;

/**
 *
 */
UCLASS()
class PROJECT_IK_API UAudioManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	static UAudioManagerSubsystem* Get(const UObject* world_context);

	void SetMasterVolume(float V);
	void SetBGMVolume(float V);
	void SetSFXVolume(float V);

	UFUNCTION(BlueprintCallable)
	UAudioComponent* Play2D(EAudioType audio_type, float volume = 1.f, float pitch = 1.f);
	UFUNCTION(BlueprintCallable)
	UAudioComponent* PlayAtLocation(EAudioType audio_type, const FVector& location, float volume = 1.f, float pitch = 1.f);
	UFUNCTION(BlueprintCallable)
	UAudioComponent* PlayAttached(EAudioType audio_type, USceneComponent* attach_to, FName socket = NAME_None, FVector offset = FVector::ZeroVector, 
		EAttachLocation::Type attach_type = EAttachLocation::Type::KeepWorldPosition, bool bStopWithOwner = true, float volume = 1.f, float pitch = 1.f);



protected:
	void LoadReferences();
	template<typename T>
	T* LoadSync(const TSoftObjectPtr<T>& soft) const;
	void ApplyVolumes(float master, float bgm, float sfx);
	const FCueEntry* GetCue(EAudioType audio_type);
	USoundBase* GetSoundClass(EAudioType audio_type, float& volume, float& pitch);


	UPROPERTY(BlueprintReadOnly)
	TSoftObjectPtr<UAudioDataAsset> soft_audio_cues_ = nullptr;
	UPROPERTY(BlueprintReadOnly)
	TSoftObjectPtr<USoundMix> soft_master_mix_ = nullptr;
	UPROPERTY(BlueprintReadOnly)
	TSoftObjectPtr<USoundClass> soft_master_channel_ = nullptr;
	UPROPERTY(BlueprintReadOnly)
	TSoftObjectPtr<USoundClass> soft_bgm_channel_ = nullptr;
	UPROPERTY(BlueprintReadOnly)
	TSoftObjectPtr<USoundClass> soft_sfx_channel_ = nullptr;
	UPROPERTY(BlueprintReadOnly)
	TSoftObjectPtr<USoundConcurrency> soft_default_sound_concurrency_ = nullptr;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UAudioDataAsset> audio_cues_ = nullptr;
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<USoundMix> master_mix_ = nullptr;
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<USoundClass> master_channel_ = nullptr;
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<USoundClass> bgm_channel_ = nullptr;
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<USoundClass> sfx_channel_ = nullptr;
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<USoundConcurrency> default_sound_concurrency_ = nullptr;
};

template<typename T>
inline T* UAudioManagerSubsystem::LoadSync(const TSoftObjectPtr<T>& soft) const
{
	if (!soft.ToSoftObjectPath().IsValid())
	{
		return nullptr;
	}

	return soft.IsValid() ? soft.Get() : soft.LoadSynchronous();
}
