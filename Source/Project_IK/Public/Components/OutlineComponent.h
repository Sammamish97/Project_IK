/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 6.10.2025
Summary : Header file for Outline Component.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Managers/EnumCluster.h"
#include "OutlineComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECT_IK_API UOutlineComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	virtual void SwitchOutline(UPrimitiveComponent* target, EOutlineState state);
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
private:
	int32 EnumToDepthStencilChannel(EOutlineState state);
};
