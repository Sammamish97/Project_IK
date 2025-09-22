/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 9.22.2025
Summary : Source file for separating enemies and heroes.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "AI/Service_SeparatingMovement.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "AI/NavigationSystemBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/Unit.h"
#include "Kismet/GameplayStatics.h"
#include "WorldSettings/IKGameModeBase.h"

UService_SeparatingMovement::UService_SeparatingMovement()
{
	is_enemy_in_range_key_.AddBoolFilter(this, GET_MEMBER_NAME_CHECKED(UService_SeparatingMovement, is_enemy_in_range_key_));
	attack_target_key_.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UService_SeparatingMovement, attack_target_key_), UObject::StaticClass());
	target_move_point_key_.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UService_SeparatingMovement, target_move_point_key_));
}

void UService_SeparatingMovement::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
	UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();
	auto attack_target = Cast<AActor>(blackboard->GetValueAsObject(attack_target_key_.SelectedKeyName));
	auto casted_unit = Cast<AUnit>(OwnerComp.GetAIOwner()->GetPawn());
	FVector base_dir;
	TArray<AActor*> ally_container;
	if (attack_target)
	{
		base_dir = (attack_target->GetActorLocation() - casted_unit->GetActorLocation()).GetSafeNormal();
	}
	else
	{
		if(casted_unit->IsHero())
		{
			base_dir = FVector(1, 0, 0);
		}
		else
		{
			base_dir = FVector(-1, 0, 0);
		}	
	}
	AIKGameModeBase* casted_mode = Cast<AIKGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	if (casted_unit->IsHero())
	{
		ally_container = casted_mode->GetHeroContainer();
	}
	else
	{
		ally_container = casted_mode->GetEnemyContainers();
	}
	
	FVector Right = FVector::CrossProduct(FVector::UpVector, base_dir).GetSafeNormal();
	float latPressure = 0.f;
	for (AActor* ally : ally_container)
	{
		if (ally == nullptr || ally == casted_unit)
		{
			continue;
		}
		FVector d = casted_unit->GetActorLocation() - ally->GetActorLocation();
		float dist = d.Size();
		if (dist < KINDA_SMALL_NUMBER) continue;
		float sep = FMath::Max(0.f, preferred_spacing_ - dist) / preferred_spacing_; // 0..1
		FVector dir = d / dist;
		latPressure += FVector::DotProduct(dir, Right) * sep; // 좌/우 부호 포함
	}

	float offset = FMath::Clamp(latPressure * lateral_gain_, -max_lateral_offset_, max_lateral_offset_);

	// 원래 목표점(전진: Waypoint, 교전: EnemyPos 또는 Lead된 포인트)
	FVector baseGoal = casted_unit->GetActorLocation() + base_dir * 500;
	FVector goal = baseGoal + Right * offset;

	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	if (!NavSys) return;

	FNavLocation NavLoc;
	// Z는 넉넉히(장애물/지형 기복 대비)
	const FVector Extent(150.f, 150.f, 500.f);            
	const ANavigationData* NavData = NavSys->GetDefaultNavDataInstance(FNavigationSystem::DontCreate);

	if (NavSys->ProjectPointToNavigation(goal, NavLoc, Extent, NavData))
	{
		blackboard->SetValueAsVector(target_move_point_key_.SelectedKeyName, NavLoc);
	}
	else
	{
		blackboard->SetValueAsVector(target_move_point_key_.SelectedKeyName, baseGoal);
	}
}
