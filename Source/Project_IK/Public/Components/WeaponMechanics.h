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
#include "Structs/CharacterData.h"
#include "Structs/WeaponStatusData.h"
#include "AITypes.h"
#include "WeaponMechanics.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_IK_API UWeaponMechanics : public UActorComponent
{
	GENERATED_BODY()
public:	
	UFUNCTION()
	void EquipWeapon(const FWeaponData& data);
	
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	void BeginFire(AActor* target);
	void FinishFire();

	void InstantReload();
	void Reload();
	void StopReload();
	
	bool IsMagazineEmpty() const;

	UFUNCTION(BlueprintCallable)
	FWeaponStatusData GetWeaponData();

	void SetHoldAction(bool hold_action);
	
	UFUNCTION(BlueprintCallable)
	AGunBase* GetWeaponActor();

	void DieWeaponActor();

	void ChangeGunShotSoundTemporariliy(EAudioType temporary_gunshot_audio, float duration = 0.f);

private:
	UPROPERTY(Transient)
	TObjectPtr<AGunBase> weapon_actor_ = nullptr;
	
	UPROPERTY(Transient)
	TObjectPtr<AUnit> owner_ref_ = nullptr;
};