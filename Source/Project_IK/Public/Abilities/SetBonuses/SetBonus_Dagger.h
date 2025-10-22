/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 4.22.2025
Summary : Header file for Dagger Set Bonus.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Structs/DamageData.h"
#include "SetBonusBase.h"
#include "SetBonus_Dagger.generated.h"

class APooledActor;
class UBuffHandler;

UCLASS(Blueprintable)
class PROJECT_IK_API USetBonus_Dagger : public USetBonusBase
{
	GENERATED_BODY()

public:
	USetBonus_Dagger();
	
	virtual void ActivateEdgeBonus() override;
	virtual void ActivateTriangleBonus() override;
	virtual void ActivateHexagonBonus() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Daggers")
	TSubclassOf<APooledActor> dagger_actor_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Daggers")
	float dagger_damage_ = 20.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnPosition")
	FVector position_offset = FVector(0, 200, 200);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnPosition")
	float random_offset_radius = 50.f;

protected:
	UFUNCTION()
	void TriangleReloadCritRateBuff();
	UFUNCTION()
	void HexagonBonus();

	void SpawnDaggers(const FVector& target_position, const FDamageData& damage_data);
	FVector GetDaggerSpawnPosition();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SkillData")
	TSubclassOf<UBuffHandler> edge_buff_class_;

	UPROPERTY();
	TObjectPtr<UBuffHandler> edge_buff_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SkillData")
	TSubclassOf<UBuffHandler> triangle_buff_class_;

	UPROPERTY();
	TObjectPtr<UBuffHandler> triangle_buff_;
	
	
	UPROPERTY()
	TObjectPtr<class UObjectPoolComponent> bullet_pool_;

	UPROPERTY()
	FTimerHandle bullet_timer_handle_;
};
