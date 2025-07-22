/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 3.30.2025
Summary : Header file for Reset Gunner Value Task.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Task_ResetGunnerValues.generated.h"

UCLASS()
class PROJECT_IK_API UTask_ResetGunnerValues : public UBTTaskNode
{
	GENERATED_BODY()
	UTask_ResetGunnerValues();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard", meta = (AllowPrivateAccess = "true"))
	FBlackboardKeySelector is_arrived_cover_key_;
};
