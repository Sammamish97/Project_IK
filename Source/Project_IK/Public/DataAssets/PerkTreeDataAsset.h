/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 07.13.2025
Summary : Header file for data assets for perk tree.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Structs/PerkNode.h"
#include "PerkTreeDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UPerkTreeDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	const TArray<FPerkNode>& GetTree() const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FPerkNode> tree_;
};
