/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 8.30.2025
Summary : Header file for Event Data Asset.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Managers/EnumCluster.h"
#include "Structs/EventData.h"
#include "EventDataAsset.generated.h"

UCLASS()
class PROJECT_IK_API UEventDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	FEventData GetActiveSkillData(EEventType type);
	FEventData GetActiveSkillDataRandomly(UWorld* world, bool only_positive);
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TMap<EEventType, FEventData> event_data_map;
};
