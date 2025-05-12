/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 4.18.2025
Summary : Source file for Shock Javelin active skill.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Abilities/ActiveSkills/AT_ShockJavelin.h"

#include "Kismet/KismetMathLibrary.h"
#include "Structs/TargetResult.h"
#include "Weapons/Skills/ShockJavelin.h"

UAT_ShockJavelin::UAT_ShockJavelin()
{
	target_param_ = FTargetParameters(ETargetingMode::Actor, ETargetType::Opponents, 1000.f);

	cool_time_ = 5.f;
}

bool UAT_ShockJavelin::ActivateSkill_Implementation(const FTargetResult& TargetResult)
{
	FVector javelin_location = skill_owner_->GetActorLocation() + javelin_location_offset_;
	FRotator rotation = UKismetMathLibrary::FindLookAtRotation(javelin_location, TargetResult.target_actors_[0]->GetActorLocation());
	FTransform spawn_transform(rotation, javelin_location);
	
	AShockJavelin* spawned_javellin = GetWorld()->SpawnActor<AShockJavelin>(javelin_class_, spawn_transform);
	return true;
}
