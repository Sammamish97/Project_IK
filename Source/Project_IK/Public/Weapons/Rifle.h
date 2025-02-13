/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.03.2024
Summary : Header file for Rifle.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Gun.h"
#include "Rifle.generated.h"

UCLASS()
class PROJECT_IK_API ARifle : public AGun
{
	GENERATED_BODY()
public:
	ARifle();
	virtual void FireWeapon(FVector target_pos, FDamageData damage) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet", meta = (AllowPrivateAccess = "true", AllowedClass = "Bullet"))
	UClass* bullet_class_;
};
