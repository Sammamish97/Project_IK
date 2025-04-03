/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 11.27.2024
Summary : Source file for Item class.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Structs/ItemData.h"
#include "Item.generated.h"

struct FTargetResult;
class ASmokeRegion;

/**
 * 
 */
UCLASS(Blueprintable)
class PROJECT_IK_API UItem : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION()
	void InitializeItemUsingData(FItemData item_data);

	UFUNCTION()
	void UseItem(UWorld* world, const FTargetResult& TargetResult);

	UFUNCTION()
	FItemData GetData() const;

	FItemData* GetDataPtr();

	UFUNCTION()
	FTargetParameters GetTargetParameters() const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Items")
	TSubclassOf<ASmokeRegion> smoke_region_class_;

private:
	UPROPERTY(VisibleAnywhere, Category = "Item")
	FItemData item_data_;

	void RestoreHP(TArray<AActor*> actors);
	void LaunchMissile(TArray<AActor*> actors);
	void AttackSpeedStimuli(TArray<AActor*> actors);
	void SmokeGrenade(UWorld* World, FVector TargetLocation, float Radius);
	void Flashbang(TArray<AActor*> actors);
};
