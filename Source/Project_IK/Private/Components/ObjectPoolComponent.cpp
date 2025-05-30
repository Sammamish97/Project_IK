/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 12.05.2024
Summary : Source file for Object Pool Component.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "Components/ObjectPoolComponent.h"
#include "Weapons/PooledActor.h"

// Sets default values for this component's properties
UObjectPoolComponent::UObjectPoolComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UObjectPoolComponent::BeginPlay()
{
	Super::BeginPlay();

	InitializePool();
}

void UObjectPoolComponent::InitializePool()
{
	if(pooled_actor_class_ == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Should Select target object class"));
		return;
	}
	object_pool_.Empty();
	for(int i = 0; i < pool_size_; ++i)
	{
		object_pool_.Add(GetWorld()->SpawnActor<APooledActor>(pooled_actor_class_));
	}
}

APooledActor* UObjectPoolComponent::FindFirstAvailableActor()
{
	for(int i = 0; i < pool_size_; ++i)
	{
		if(object_pool_[i]->GetInUse() == false)
		{
			return object_pool_[i];
		}
	}
	UE_LOG(LogTemp, Error, TEXT("Failed to find available object in the pool"));
	return nullptr;
}

APooledActor* UObjectPoolComponent::SpawnFromPool(const FRotator& rotator, const FVector& translator)
{
	auto available_actor = FindFirstAvailableActor();
	if(available_actor != nullptr)
	{
		available_actor->SetActorRotation(rotator);
		available_actor->SetActorLocation(translator);
		available_actor->SetInUse(true);
		return available_actor;
	}
	return nullptr;
}

TSubclassOf<APooledActor> UObjectPoolComponent::GetObjectClass() const
{
	return pooled_actor_class_;
}

void UObjectPoolComponent::SetObjectClass(const TSubclassOf<APooledActor>& target_class)
{
	pooled_actor_class_ = target_class;
	InitializePool();
}

TArray<APooledActor*>& UObjectPoolComponent::GetObjectPool()
{
	return object_pool_;
}