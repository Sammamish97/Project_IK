/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 2.09.2025
Summary : Source file for Oopart base class.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Managers/EnumCluster.h"
#include "OopartBase.generated.h"

UCLASS()
class PROJECT_IK_API AOopartBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AOopartBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SetOwner(TWeakObjectPtr<AActor> owner);
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Oopart", meta = (AllowPrivateAccess = "true", BindWidget))
	UStaticMeshComponent* oopart_mesh_;

	UPROPERTY(VisibleAnywhere, Category = "Oopart")
	TWeakObjectPtr<AActor> oopart_owner_;

	EOopartType oopart_type_;
};