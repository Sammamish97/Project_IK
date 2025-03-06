/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 12.10.2024
Summary : Source file for Check Battle Condition Node.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "AI/Service_CheckBattleCondition.h"
#include "AIController.h"
#include "Characters/Unit.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CharacterStatComponent.h"
#include "AI/Service_FindBestCover.h"
#include "Components/WeaponMechanics.h"
#include "Environments/Cover.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Managers/EnumCluster.h"
#include "Managers/CommonFunctions.h"

UService_CheckBattleCondition::UService_CheckBattleCondition()
{
	NodeName = "Check Battle Condition";
	Interval = 0.001f;
	RandomDeviation = 0.f;
	
	attack_target_key_.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UService_CheckBattleCondition, attack_target_key_), UObject::StaticClass());
	owned_cover_key_.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UService_CheckBattleCondition, owned_cover_key_), UObject::StaticClass());
}

//만약 전투 중 전투가 종료되거나, 전투 state를 바꿔야 하는 상황이 되었다면 여기서 대응.
void UService_CheckBattleCondition::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();
	UObject* attack_target = blackboard->GetValueAsObject(attack_target_key_.SelectedKeyName);
	UObject* owned_cover = blackboard->GetValueAsObject(owned_cover_key_.SelectedKeyName);
	
	auto casted_unit = Cast<AUnit>(OwnerComp.GetAIOwner()->GetPawn());
	auto component = casted_unit->GetComponentByClass(UWeaponMechanics::StaticClass());
	UWeaponMechanics* casted_component = Cast<UWeaponMechanics>(component);
		
	//적이 죽으면 state변경.
	if(attack_target == nullptr)
	{
		blackboard->SetValueAsEnum(unit_state_key_.SelectedKeyName, static_cast<uint8>(EUnitState::Forwarding));
		casted_component->FinishFire();
		return;
	}

	//적이 시야 밖으로 사라지면 state변경.
	AActor* casted_target = Cast<AActor>(attack_target);
	if(FVector::Dist2D(casted_target->GetActorLocation(), casted_unit->GetActorLocation()) >
		casted_unit->GetCharacterStat()->GetSightRange())
	{
		blackboard->SetValueAsEnum(unit_state_key_.SelectedKeyName, static_cast<uint8>(EUnitState::Forwarding));
		casted_component->FinishFire();
		return;
	}
	
	//만약 전투 중 쓸만한 엄폐물이 나타났거나, 사용하던 엄폐물이 박살나고 새로운 엄폐물을 전투중 발견하면 대응하기 위한 코드.
	if(owned_cover)
	{
		//만약 소유중인 엄폐물이 있다면, 만약 도달하지 않았다면 먼저 도달하도록 state를 변경.
		AActor* casted_cover = Cast<AActor>(owned_cover);
		float cover_owner_dist = FVector::Dist2D(casted_cover->GetActorLocation(), casted_unit->GetActorLocation());
		//TODO: 플레이어-엄폐물 사이 위치 threshold를 하드코딩이 아닌 적절한 값으로 대체해야 한다. 
		if(cover_owner_dist > 50.0)
		{
			blackboard->SetValueAsEnum(unit_state_key_.SelectedKeyName, static_cast<uint8>(EUnitState::HeadingToCover));
			casted_component->FinishFire();
		}
	}
	else
	{
		//전투를 하며 계속 엄폐물을 찾는다.
		TArray<AActor*> ignore_actors;
		TArray<AActor*> out_actors;
		TArray<TEnumAsByte<EObjectTypeQuery>> traceObjectTypes;
		traceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));
			
		UKismetSystemLibrary::SphereOverlapActors(GetWorld(), casted_unit->GetActorLocation(),
			casted_unit->GetCharacterStat()->GetSightRange(),
			traceObjectTypes, ACover::StaticClass(), ignore_actors, out_actors);

		// @@ TODO: Replace deprecated fire range.
			// @@ TODO: Then REMOVE this comment and the variable
		const float DEPRECATED_FIRE_RANGE = 600.f;
		//만약 사용 가능한 엄폐물을 찾으면 해당 엄폐물로 향한다.
		if(ACover* best_cover = CommonFunctions::FindBestCover(out_actors, casted_target->GetActorLocation(),
			DEPRECATED_FIRE_RANGE))
		{
			best_cover->SetCoveringOwner(true);
			blackboard->SetValueAsObject(owned_cover_key_.SelectedKeyName, best_cover);
			blackboard->SetValueAsEnum(unit_state_key_.SelectedKeyName, static_cast<uint8>(EUnitState::HeadingToCover));
			casted_component->FinishFire();
		}
	}
	
}
