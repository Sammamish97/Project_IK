/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.29.2025
Summary : Header file for Enemy Knight A.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Enemy_RifleMan.h"
#include "Enemy_Knight_A.generated.h"

UCLASS()
class PROJECT_IK_API AEnemy_Knight_A : public AEnemy_RifleMan
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	void OnHPThreshold(float ratio);
	
private:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TSubclassOf<UBuffHandler> buff_class_;

	UPROPERTY();
	TObjectPtr<UBuffHandler> buff_;

	bool on_buff_ = false;
};
