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

UCLASS(Abstract)
class PROJECT_IK_API AEnemy_Officer : public AEnemy_RifleMan
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void PointTarget(float hp_ratio, AActor* owner_actor);

private:
	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	float rally_range_ = 600.f;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> pointing_animation_;
	
	UPROPERTY(EditDefaultsOnly)
	float targeting_hp_threshold_ = 0.7;

	bool is_targeting_available_ = true;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TSubclassOf<UBuffHandler> focusing_buff_class_;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TSubclassOf<UBuffHandler> marked_buff_class_;
	
	UPROPERTY(Transient)
	TObjectPtr<UBuffHandler> focusing_buff_;
	
	UPROPERTY(Transient)
	TObjectPtr<UBuffHandler> marked_buff_;
};
