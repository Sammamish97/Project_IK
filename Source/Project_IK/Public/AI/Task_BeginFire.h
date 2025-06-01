/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 12.17.2024
Summary : Header file for BeginFire Task.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Task_BeginFire.generated.h"

UCLASS()
class PROJECT_IK_API UTask_BeginFire : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UTask_BeginFire();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BB", meta = (AllowPrivateAccess = "true"))
	FBlackboardKeySelector attack_target_key_;
};
