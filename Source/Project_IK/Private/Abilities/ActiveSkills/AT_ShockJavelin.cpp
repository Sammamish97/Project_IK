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
	FRotator rotation = UKismetMathLibrary::FindLookAtRotation(skill_owner_->GetActorLocation(), TargetResult.target_actors_[0]->GetActorLocation());
	//FVector scale = javelin_class_->GetDefaultObject<AActor>()->GetRootComponent()->GetRelativeScale3D();
	FTransform spawn_transform(rotation, skill_owner_->GetActorLocation());
	
	AShockJavelin* spawned_javellin = GetWorld()->SpawnActor<AShockJavelin>(javelin_class_, spawn_transform);
	//spawned_javellin->SetDamageData({});
	return true;
}
