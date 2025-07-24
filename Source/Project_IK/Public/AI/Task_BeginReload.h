/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 12.17.2024
Summary : Header file for Begin Reload Task.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Task_BeginReload.generated.h"

class UWeaponMechanics;

UCLASS()
class PROJECT_IK_API UTask_BeginReload : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UTask_BeginReload();
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UFUNCTION()
	void OnFinishReload(UBehaviorTreeComponent* bt_component, bool is_interrupted);
};
