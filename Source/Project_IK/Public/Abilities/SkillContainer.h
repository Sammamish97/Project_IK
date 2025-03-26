/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 09.26.2024
Summary : Header file for skill containers.
					An actor component class to contain skills.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Structs/ActiveSkillData.h"
#include "Structs/TargetParameters.h"
#include "Structs/TargetResult.h"
#include "SkillContainer.generated.h"


class USkillBase;
class UDataTableManager;
class AHeroBase;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_IK_API USkillContainer : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USkillContainer();

	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;

	UFUNCTION(BlueprintCallable)
	bool InvokeSkills(const FTargetResult& TargetResult);

	bool HasActiveSkill() const;
	float GetCooltime() const;
	bool IsOnCoolDown() const;
	float GetLeftCoolDown() const;

	TOptional<FTargetParameters> GetTargetParameters() const;
	FActiveSkillData GetEquippedActiveSkillData();
	
	void EquipActiveSkill(EActiveSkillType type);
	void UnEquipActiveSkill();

private:
	FActiveSkillData equipped_active_skill_data_;
	UPROPERTY()
	TWeakObjectPtr<UDataTableManager> data_table_cache_;
	UPROPERTY()
	TObjectPtr <USkillBase> active_skill_;
	UPROPERTY()
	TWeakObjectPtr <AHeroBase> hero_cache_;
	UPROPERTY()
	FTimerHandle cool_down_handle_;
};
