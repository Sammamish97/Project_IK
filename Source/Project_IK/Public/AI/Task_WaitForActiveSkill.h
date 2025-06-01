/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 5.24.2025
Summary : Header file for Wait for active skill casting Task.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Task_WaitForActiveSkill.generated.h"

UCLASS()
class PROJECT_IK_API UTask_WaitForActiveSkill : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UTask_WaitForActiveSkill();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
