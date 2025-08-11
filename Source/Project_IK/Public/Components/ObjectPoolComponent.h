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
protected:
	APooledActor* FindFirstAvailableActor();

public:
	UObjectPoolComponent();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	void InitializePool();
	void ClearPool();
	APooledActor* SpawnFromPool(const FRotator& rotator, const FVector& translator);
	TSubclassOf<APooledActor> GetObjectClass() const;
	void SetObjectClass(const TSubclassOf<APooledActor>& target_class);
	TArray<APooledActor*>& GetObjectPool();

private:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
	TSubclassOf<APooledActor> pooled_actor_class_;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
	int pool_size_;

	UPROPERTY(Transient)
	TArray<APooledActor*> object_pool_;

	UPROPERTY(Transient)
	TObjectPtr<USceneComponent> objects_root_;
};
