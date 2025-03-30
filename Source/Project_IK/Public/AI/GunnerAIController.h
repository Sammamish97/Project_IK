/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.03.2024
Summary : Header file for Gunner AI Controller.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AI/MeleeAIController.h"
#include "GunnerAIController.generated.h"

UCLASS()
class PROJECT_IK_API AGunnerAIController : public AMeleeAIController
{
	GENERATED_BODY()
public:
	AGunnerAIController();
	virtual void OnDie() override;
	virtual AActor* GetOwnedCover() override;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GunnerAIController", meta = (AllowPrivateAccess = "true"))
	FName owned_cover_key_name_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GunnerAIController", meta = (AllowPrivateAccess = "true"))
	FName fire_state_key_name_;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GunnerAIController", meta = (AllowPrivateAccess = "true"))
	FName reload_state_key_name_;
};
