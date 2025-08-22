/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 08.12.2025
Summary : Header file for audio data assets.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Managers/EnumCluster.h"
#include "AudioDataAsset.generated.h"

class USoundBase;
class USoundClass;
enum class EAudioType : uint8;

USTRUCT(BlueprintType)
struct FCueEntry
{
	GENERATED_BODY()

public:
	// Async load to hold only necessary assets
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<USoundBase> soft_sound_;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<USoundClass> soft_sound_channel_;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float volume_ = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float pitch_ = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EAudioType audio_type_ = EAudioType::NONE;
};

/**
 * 
 */
UCLASS(BlueprintType)
class PROJECT_IK_API UAudioDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	// Let's try this one to be TArray that makes a couple of trade offs
	//		1. O(1) time complexity of Find
	//		2. probably there will be duplicated items.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FCueEntry> cues_;

	inline const FCueEntry* Find(EAudioType type) const
	{
		return cues_.FindByPredicate([type](const FCueEntry& cue) {return cue.audio_type_ == type; });
	}
};
