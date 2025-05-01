/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 4.29.2025
Summary : Header file for On Arrived Cover  Task.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Task_OnArrivedCover.generated.h"

UCLASS()
class PROJECT_IK_API UTask_OnArrivedCover : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UTask_OnArrivedCover();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard", meta = (AllowPrivateAccess = "true"))
	FBlackboardKeySelector is_arrived_cover_key_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard", meta = (AllowPrivateAccess = "true"))
	FBlackboardKeySelector owned_cover_key_;
};
