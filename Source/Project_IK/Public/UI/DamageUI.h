/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 12.19.2024
Summary : Header file for an actor that holds damage UI.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "../Weapons/PooledActor.h"
#include "DamageUI.generated.h"

class UDamageWidget;
class UWidgetComponent;

UCLASS(Blueprintable)
class PROJECT_IK_API ADamageUI : public APooledActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADamageUI();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SetHealAmount(float HealAmount);

	UFUNCTION(BlueprintCallable)
	void SetDamageAmount(float DamageAmount, FLinearColor Color);

	UFUNCTION(BlueprintCallable)
	void SetMissed();

	virtual void SetInUse(bool in_use) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage UI")
	TSubclassOf<UDamageWidget> damage_widget_class_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage UI", meta = (AllowPrivateAccess = true))
	FVector initial_velocity_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage UI", meta = (AllowPrivateAccess = true))
	FVector gravity_;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage UI", meta = (AllowPrivateAccess = true))
	UWidgetComponent* widget_component_;

	FVector velocity_;
};
