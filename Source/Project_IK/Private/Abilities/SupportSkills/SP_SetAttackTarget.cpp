/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.24.2025
Summary : Source file for set attack target support skill.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Abilities/SupportSkills/SP_SetAttackTarget.h"

#include "Characters/HeroBase.h"
#include "Components/TargetingComponent.h"
#include "Components/WeaponMechanics.h"
#include "Kismet/GameplayStatics.h"
#include "WorldSettings/IKPlayerController.h"

USP_SetAttackTarget::USP_SetAttackTarget()
{
	target_param_ = FTargetParameters(ETargetingMode::Actor, ETargetType::Allies, 10000.f);
	attack_target_params_ = FTargetParameters(ETargetingMode::Actor, ETargetType::Opponents, 1000.f, 1000.f);
}

bool USP_SetAttackTarget::ActivateSkill(const FTargetResult& target_result)
{
	if (selected_hero_)
	{
		selected_hero_->SetAttackTarget(target_result.target_actors_[0]);
		return true;
	}
	
	if (target_result.target_actors_.Num() > 0 && 
		target_result.target_actors_[0] &&
		target_result.target_actors_[0]->IsA(AHeroBase::StaticClass()))
	{
		selected_hero_ = Cast<AHeroBase>(target_result.target_actors_[0]);
		float fire_range = selected_hero_->GetWeaponMechanics()->GetWeaponData().fire_range;
		attack_target_params_.range_ = fire_range;
		attack_target_params_.radius_ = fire_range;
		Cast<AIKPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->GetTargetingComponent()->StartTargeting(attack_target_params_);
	}
	return false;
}

void USP_SetAttackTarget::ResetSkill()
{
	Super::ResetSkill();
	selected_hero_ = nullptr;
}