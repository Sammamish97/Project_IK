/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.05.2024
Summary : Header file for Find Nearest Enemy service node.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "Managers/EnumCluster.h"
#include "Service_FindEnemy.generated.h"

UCLASS()
class PROJECT_IK_API UService_FindEnemy : public UBTService
{
	GENERATED_BODY()

public:
	UService_FindEnemy();
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard", meta = (AllowPrivateAccess = "true"))
	FBlackboardKeySelector target_class_key_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard", meta = (AllowPrivateAccess = "true"))
	FBlackboardKeySelector attack_target_key_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard", meta = (AllowPrivateAccess = "true"))
	FBlackboardKeySelector target_type_key_;
};
