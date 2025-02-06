/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 2.3.2025
Summary : Header file for Perk trees.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Structs/PerkNode.h"
#include "PerkTree.generated.h"

struct FPerkNode;

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UPerkTree : public UObject
{
	GENERATED_BODY()

public:
	static UPerkTree* Get();

	const TArray<FPerkNode>& GetTree() const;

	void Initialize();
	// Need to call it to clean instance at the end of the world EndPlay()
	void Destroy();


	UPROPERTY(VisibleAnywhere, Category = "PerkData")
	TArray<FPerkNode> perks_;

private:
	// Private constructor to prevent multiple instancings.
	UPerkTree();
};
