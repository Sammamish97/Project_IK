/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 5.28.2025
Summary : Header file for Enemy Officer.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Enemy_RifleMan.h"
#include "Enemy_Officer.generated.h"

UCLASS()
class PROJECT_IK_API AEnemy_Officer : public AEnemy_RifleMan
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy_Officer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void PointTarget(float hp_ratio, AActor* owner_actor);

private:
	bool is_targeting_available_ = true;
	float rally_range_ = 600.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> pointing_animation_;
};
