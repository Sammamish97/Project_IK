/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 4.17.2025
Summary : Source file for Bullet On Hit Effect Component.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Components/BulletOnHitEffectComponent.h"


// Sets default values for this component's properties
UBulletOnHitEffectComponent::UBulletOnHitEffectComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBulletOnHitEffectComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBulletOnHitEffectComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UBulletOnHitEffectComponent::OnHit(AActor* target)
{
}
