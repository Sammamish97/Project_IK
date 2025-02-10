/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 2.08.2025
Summary : Header file for Pistol.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Gun.h"
#include "Pistol.generated.h"

UCLASS()
class PROJECT_IK_API APistol : public AGun
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APistol();
	virtual void FireWeapon(FVector target_pos, FDamageData damage) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet", meta = (AllowPrivateAccess = "true", AllowedClass = "Bullet"))
	UClass* bullet_class_;
};
