/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 04.18.2025
Summary : Header file for an active skill named ThunderStorm.
					It periodically summons thunders that damages in an area.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Abilities/SkillBase.h"
#include "AT_ThunderStorm.generated.h"

class AThunderStorm;

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UAT_ThunderStorm : public USkillBase
{
	GENERATED_BODY()
public:
	UAT_ThunderStorm();
	virtual bool ActivateSkill_Implementation(const FTargetResult& TargetResult) override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visuals")
	TSubclassOf<AThunderStorm> visual_actor_class_;

protected:
	UFUNCTION()
	void DamageEnemies();


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float damage_ = 0.f;

	UWorld* world_cache_ = nullptr;

	UPROPERTY()
	TObjectPtr<AThunderStorm> visual_actor_;
};
