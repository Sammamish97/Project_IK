/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 6.1.2025
Summary : Header file for the Instant Repair Support SKill.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "Abilities/SupportSkills/SP_Reposition.h"
#include "Characters/HeroBase.h"
#include "Components/TargetingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "WorldSettings/IKPlayerController.h"

#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

USP_Reposition::USP_Reposition()
{
	target_param_ = FTargetParameters(ETargetingMode::Actor, ETargetType::Allies, 10000.f);
	reposition_location_params_ = FTargetParameters(ETargetingMode::Location, ETargetType::None, 1000.f, 100.f);
}

bool USP_Reposition::ActivateSkill(const FTargetResult& target_result)
{
	if (selected_hero_)
	{
		selected_hero_->Reposition(target_result.target_location_);

		if (reposition_vfx_)
		{
			UNiagaraComponent* component = UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, reposition_vfx_, target_result.target_location_);
			component->SetVariableFloat(FName("Radius"), reposition_location_params_.radius_);
		}
		return true;
	}
	
	if (target_result.target_actors_.Num() > 0 
		&& target_result.target_actors_[0]
		&& target_result.target_actors_[0]->IsA(AHeroBase::StaticClass()))
	{
		selected_hero_ = Cast<AHeroBase>(target_result.target_actors_[0]);
		Cast<AIKPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->GetTargetingComponent()->StartTargeting(reposition_location_params_);
	}
	return false;
}

void USP_Reposition::ResetSkill()
{
	Super::ResetSkill();
	selected_hero_ = nullptr;
}
