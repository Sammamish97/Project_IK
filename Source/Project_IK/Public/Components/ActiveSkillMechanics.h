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
	void ActivateSkill(const FTargetResult& TargetResult);
	void StopActiveSkill();

	bool HasActiveSkill() const;
	float GetCooltime() const;
	float GetCastingTime() const;

	UFUNCTION()
	void OnFinishCasting(FTargetResult TargetResult);

	UFUNCTION()
	void OnFinishAIHolding();
	
	FTargetParameters GetTargetParameters() const;
	const FActiveSkillData& GetEquippedActiveSkillData();
	class USkillBase* GetActiveSkill() const;
	void EquipActiveSkill(const FActiveSkillData& data);
	void UnEquipActiveSkill();

private:
	UPROPERTY()
	FActiveSkillData equipped_active_skill_data_;
	
	UPROPERTY()
	TObjectPtr <UActiveSkillBase> active_skill_;
	
	UPROPERTY()
	TWeakObjectPtr <AHeroBase> hero_cache_;

	//액티브 스킬의 흐름은 다음과 같다.
	//AI Hold: 액티브 스킬이 끝날 때 까지 다른 행동을 못하도록 끝나는 시간까지 ai state를 묶는다.
	//Casting: 스킬이 발동되자마자 액티브 스킬이 실행되지는 않는다. 보통 짧은 시간의 "선딜"이 존재한다. Casting timer를 통해 선딜을 계산한다.
	//Finish Casting: Casting이 끝나면 실제로 스킬을 발동 시킨다.
	//FiniSh AI Hold: AI Hold가 끝나면 모든 스킬 프로세스가 끝났으므로, AI State를 OnLogic으로 돌린다.
	
	FTimerHandle casting_time_handle_;
	FTimerHandle ai_hold_time_handle_;
};