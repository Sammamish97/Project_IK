/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 9.22.2025
Summary : Header file for separating enemies and heroes.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "Service_SeparatingMovement.generated.h"

UCLASS()
class PROJECT_IK_API UService_SeparatingMovement : public UBTService
{
	GENERATED_BODY()

public:
	UService_SeparatingMovement();
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard", meta = (AllowPrivateAccess = "true"))
	FBlackboardKeySelector attack_target_key_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard", meta = (AllowPrivateAccess = "true"))
	FBlackboardKeySelector is_enemy_in_range_key_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard", meta = (AllowPrivateAccess = "true"))
	FBlackboardKeySelector target_move_point_key_;

	//확보해야 할 최소한의 공간.
	float preferred_spacing_ = 300;
	//좌/우로 얼마나 강하게 밀어낼 것인가?
	float lateral_gain_ = 300;
	//최대 좌/우 offset.
	float max_lateral_offset_ = 300;
};
