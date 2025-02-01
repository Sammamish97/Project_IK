/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.20.2024
Summary : Source file for the DPI fire range buff.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Abilities/DPI_FireRange.h"
#include "Characters/Unit.h"
#include "Components/CharacterStatComponent.h"

#include "Kismet/GameplayStatics.h"
#include "WorldSettings/IKGameInstance.h"
#include "Managers/TextureManager.h"

ADPI_FireRange::ADPI_FireRange()
{
	PrimaryActorTick.bCanEverTick = false;
	is_periodic_ = false;
	buff_amount_ = 200.f;
}

void ADPI_FireRange::BeginPlay()
{
	Super::BeginPlay();
}

void ADPI_FireRange::StartPassiveSkill()
{
	Super::StartPassiveSkill();
	unit_caster_ = Cast<AUnit>(caster_);
	if(unit_caster_)
	{
		// @@ TODO: How to deal with fire range buff?
		//unit_caster_->ApplyBuff(FBuff(TEXT("Drone_FireRange"), ECharacterStatType::FireRange, buff_amount_, false, true));
	}
}