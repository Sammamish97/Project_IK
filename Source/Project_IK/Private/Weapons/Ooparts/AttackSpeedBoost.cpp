/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 2.09.2025
Summary : Source file for attack speed boost oopart.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Weapons/Ooparts/AttackSpeedBoost.h"


// Sets default values
AAttackSpeedBoost::AAttackSpeedBoost()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAttackSpeedBoost::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAttackSpeedBoost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

