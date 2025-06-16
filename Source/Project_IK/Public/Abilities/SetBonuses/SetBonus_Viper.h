/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 4.22.2025
Summary : Header file for the Viper Set Bonus.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "SetBonusBase.h"
#include "SetBonus_Viper.generated.h"

UCLASS()
class PROJECT_IK_API USetBonus_Viper : public USetBonusBase
{
	GENERATED_BODY()


protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UNiagaraSystem> skill_particle_system_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UMaterialInstance> skill_bullet_material_;

	virtual void ActivateEdgeBonus() override;
	virtual void ActivateTriangleBonus() override;
	virtual void ActivateHexagonBonus() override;
};
