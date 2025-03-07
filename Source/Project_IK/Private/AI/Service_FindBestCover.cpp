/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.05.2024
Summary : Source file for Find best cover node.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "AI/Service_FindBestCover.h"

#include "AIController.h"
#include "Characters/Unit.h"
#include "Components/CharacterStatComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Managers/CommonFunctions.h"
#include "Environments/Cover.h"
#include "Kismet/KismetSystemLibrary.h"

UService_FindBestCover::UService_FindBestCover()
{
	NodeName = "FindBestCover";
	Interval = 0.001f;
	RandomDeviation = 0.f;

	owned_cover_key_.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UService_FindBestCover, owned_cover_key_), UObject::StaticClass());
	attack_target_key_.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UService_FindBestCover, attack_target_key_), UObject::StaticClass());
}

void UService_FindBestCover::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();

	AActor* cover = Cast<AActor>(blackboard->GetValueAsObject(owned_cover_key_.SelectedKeyName));
	AActor* attack_target = Cast<AActor>(blackboard->GetValueAsObject(attack_target_key_.SelectedKeyName));
	
	//현재 소유한 cover가 없어야만 새로운 cover를 찾아야 함.
	if(cover == nullptr)
	{
		//cover의 계산에는 적의 위치가 필요함.
		if(attack_target)
		{
			AUnit* casted_gunner = Cast<AUnit>(OwnerComp.GetAIOwner()->GetPawn());
			FVector attack_target_pos = attack_target->GetActorLocation();
			
			TArray<AActor*> ignore_actors;
			TArray<AActor*> out_actors;
			TArray<TEnumAsByte<EObjectTypeQuery>> traceObjectTypes;
			traceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));

			UKismetSystemLibrary::SphereOverlapActors(GetWorld(), casted_gunner->GetActorLocation(),
				casted_gunner->GetCharacterStat()->GetSightRange(),
				traceObjectTypes, ACover::StaticClass(), ignore_actors, out_actors);

			// @@ TODO: Replace deprecated fire range.
			// @@ TODO: Then REMOVE this comment and the variable
			const float DEPRECATED_FIRE_RANGE = 600.f;
			if(ACover* best_cover = CommonFunctions::FindBestCover(out_actors, attack_target_pos, DEPRECATED_FIRE_RANGE))
			{
				best_cover->SetCoveringOwner(true);
				blackboard->SetValueAsObject(owned_cover_key_.SelectedKeyName, best_cover);
				blackboard->SetValueAsEnum(unit_state_key_.SelectedKeyName, static_cast<uint8>(EUnitState::HeadingToCover));
			}
		}
	}
}