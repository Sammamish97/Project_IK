/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 12.05.2024
Summary : Header file for Object Pool Component.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ObjectPoolComponent.generated.h"

class APooledActor;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_IK_API UObjectPoolComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UObjectPoolComponent();
protected:
	APooledActor* FindFirstAvailableActor();

public:
	virtual void BeginPlay() override;
	void InitializePool();
	APooledActor* SpawnFromPool(FTransform spawn_transform);
	TSubclassOf<APooledActor> GetObjectClass() const;
	TArray<APooledActor*>& GetObjectPool();

private:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
	TSubclassOf<APooledActor> pooled_actor_class_;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
	int pool_size_;

	UPROPERTY(Transient)
	TArray<APooledActor*> object_pool_;
};
