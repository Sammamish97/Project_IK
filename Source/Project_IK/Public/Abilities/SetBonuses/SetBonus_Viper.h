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

class UBulletDebuffEffectComponent;
class UBulletViperEffectComponent;

UCLASS(Blueprintable)
class PROJECT_IK_API USetBonus_Viper : public USetBonusBase
{
	GENERATED_BODY()


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UBulletDebuffEffectComponent> triangle_on_hit_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UBulletViperEffectComponent> hexagon_on_hit_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UNiagaraSystem> viper_activated_particle_;

	virtual void ActivateEdgeBonus() override;
	virtual void ActivateTriangleBonus() override;
	virtual void ActivateHexagonBonus() override;

private:
	FBuffStatusData edge_buff_data_;

};
