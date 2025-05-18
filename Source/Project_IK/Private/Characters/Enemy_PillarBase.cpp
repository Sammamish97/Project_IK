/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 5.18.2025
Summary : Source file for Pillar Base.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Characters/Enemy_PillarBase.h"

// Sets default values
AEnemy_PillarBase::AEnemy_PillarBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemy_PillarBase::BeginPlay()
{
	Super::BeginPlay();
	FTimerDelegate buff_delegate = FTimerDelegate::CreateUObject(this, &AEnemy_PillarBase::ActivateBuff);
	GetWorld()->GetTimerManager().SetTimer(buff_timer_, buff_delegate, buff_term_, true, buff_term_);
}

void AEnemy_PillarBase::ActivateBuff()
{
}
