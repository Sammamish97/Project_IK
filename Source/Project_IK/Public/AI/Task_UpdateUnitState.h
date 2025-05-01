/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 5.1.2025
Summary : Header file for Update Unit State Task.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Managers/EnumCluster.h"
#include "Task_UpdateUnitState.generated.h"
UCLASS()
class PROJECT_IK_API UTask_UpdateUnitState : public UBTTaskNode
{
	GENERATED_BODY()
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard", meta = (AllowPrivateAccess = "true"))
	FBlackboardKeySelector unit_state_key_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard", meta = (AllowPrivateAccess = "true"))
	EUnitState new_state_;
};
