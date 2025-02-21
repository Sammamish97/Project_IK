/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 2.22.2025
Summary : Header file for Oopart Mechanics class.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Structs/OopartData.h"
#include "OopartMechanics.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECT_IK_API UOopartMechanics : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UOopartMechanics();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	FOopartData GetEquippedOopartData();
	void EquipOopart(EOopartType type);
	void UnEquipOopart();
	
private:
	FOopartData equipped_oopart_data_;
	AOopartBase* oopart_actor_;
	
	class UDataTableManager* equip_manager_cache_;
	class AHeroBase* hero_cache_;
};
