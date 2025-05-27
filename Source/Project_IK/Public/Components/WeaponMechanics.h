/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.03.2024
Summary : Header file for WeaponMechanics.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Managers/EnumCluster.h"
#include "Structs/CharacterData.h"
#include "Structs/WeaponData.h"
#include "AITypes.h"
#include "WeaponMechanics.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_IK_API UWeaponMechanics : public UActorComponent
{
	GENERATED_BODY()
public:	
	UFUNCTION()
	void EquipWeapon(EWeaponType type);
	
	virtual void BeginPlay() override;
	
	void BeginFire(AActor* target);
	void Reload(float duration_multiplier = 1.0f);
	void FinishFire();
	
	bool IsMagazineEmpty() const;

	UFUNCTION(BlueprintCallable)
	FWeaponData GetWeaponData();
	
	UFUNCTION(BlueprintCallable)
	AGunBase* GetWeaponActor();

	FAIRequestID GetReloadRequestId() const;
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "WeaponMechanics", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AGunBase> weapon_class_ = nullptr;
	
	UPROPERTY(Transient)
	TObjectPtr<AGunBase> weapon_actor_ = nullptr;
	
	UPROPERTY(Transient)
	TObjectPtr<AUnit> owner_ref_ = nullptr;
};