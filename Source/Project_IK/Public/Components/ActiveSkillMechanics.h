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
#include "AITypes.h"
#include "ActiveSkillMechanics.generated.h"

class UActiveSkillBase;
class UDataTableManager;
class AHeroBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_IK_API UActiveSkillMechanics : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UActiveSkillMechanics();

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void InitializeComponent() override;

	UFUNCTION(BlueprintCallable)
	bool InvokeSkills(const FTargetResult& TargetResult);

	bool HasActiveSkill() const;
	float GetCooltime() const;
	float GetCastingTime() const;
	
	FTargetParameters GetTargetParameters() const;
	FActiveSkillData GetEquippedActiveSkillData();
	class USkillBase* GetActiveSkill() const;
	void EquipActiveSkill(EActiveSkillType type);
	void UnEquipActiveSkill();

	void OnCastingFinish();
	FAIRequestID GetCastingRequestID() const;

private:
	FActiveSkillData equipped_active_skill_data_;
	UPROPERTY()
	TWeakObjectPtr<UDataTableManager> data_table_cache_;
	UPROPERTY()
	TObjectPtr <UActiveSkillBase> active_skill_;
	UPROPERTY()
	TWeakObjectPtr <AHeroBase> hero_cache_;
	UPROPERTY()
	FTimerHandle casting_time_handle_;
	UPROPERTY()
	FAIRequestID active_skill_request_id_ = 1;
};