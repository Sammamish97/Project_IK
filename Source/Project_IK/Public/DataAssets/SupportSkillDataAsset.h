/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 5.22.2025
Summary : Header file for the Support SKill Data Asset.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SupportSkillDataAsset.generated.h"

class UDisplayDataAsset;
UCLASS()
class PROJECT_IK_API USupportSkillDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class USupportSkillBase> support_skill_class_;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UDisplayDataAsset> display_data_;
};
