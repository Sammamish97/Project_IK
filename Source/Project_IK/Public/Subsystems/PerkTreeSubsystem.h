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
#include "Subsystems/GameInstanceSubsystem.h"
#include "Structs/PerkNode.h"
#include "PerkTreeSubsystem.generated.h"

struct FPerkNode;

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UPerkTreeSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	const TArray<FPerkNode>& GetTree() const;


	virtual void Initialize(FSubsystemCollectionBase& collection) override;

	virtual void Deinitialize() override;


private:

	UPROPERTY(VisibleAnywhere, Category = "PerkData")
	TArray<FPerkNode> perks_;
};
