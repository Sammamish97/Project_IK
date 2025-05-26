/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 5.18.2025
Summary : Header file for Enemy Assassin.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Enemy_RifleMan.h"
#include "Enemy_Assassin.generated.h"

UCLASS(Abstract)
class PROJECT_IK_API AEnemy_Assassin : public AEnemy_RifleMan
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy_Assassin();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Attack(AActor* target) override;
	UFUNCTION()
	void OnAction(float hp_ratio);
	
private:
	bool is_cloaked_ = true;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UMaterialInstance> head_material_;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UMaterialInstance> limb_material_;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UMaterialInstance> torso_material_;
};
