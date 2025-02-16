/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 12.10.2024
Summary : Source file for Check Gunner Arrived Cover node.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "AI/Service_CheckGunnerArrivedCover.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Managers/EnumCluster.h"

UService_CheckGunnerArrivedCover::UService_CheckGunnerArrivedCover()
{
	NodeName = "CheckGunnerArrivedCover";
	Interval = 0.001f;
	RandomDeviation = 0.f;
	
	attack_target_key_.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UService_CheckGunnerArrivedCover, attack_target_key_), UObject::StaticClass());
	owned_cover_key_.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UService_CheckGunnerArrivedCover, owned_cover_key_), UObject::StaticClass());
}

void UService_CheckGunnerArrivedCover::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
	float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();
	APawn* casted_gunner = OwnerComp.GetAIOwner()->GetPawn();
	if(AActor* cover_actor = Cast<AActor>(blackboard->GetValueAsObject(owned_cover_key_.SelectedKeyName)))
	{
		float cover_owner_dist = FVector::Dist2D(cover_actor->GetActorLocation(), casted_gunner->GetActorLocation());
		//TODO: 플레이어-엄폐물 사이 위치 threshold를 하드코딩이 아닌 적절한 값으로 대체해야 한다. 
		if(cover_owner_dist <= 50.0)
		{
			blackboard->SetValueAsEnum(unit_state_key_.SelectedKeyName, static_cast<uint8>(EUnitState::Attacking));
		}
		else
		{
			blackboard->SetValueAsEnum(unit_state_key_.SelectedKeyName, static_cast<uint8>(EUnitState::HeadingToCover));
		}
	}
}
