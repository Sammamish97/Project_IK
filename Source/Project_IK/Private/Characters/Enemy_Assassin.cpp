/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 5.18.2025
Summary : Source file for Enemy Assassin.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Characters/Enemy_Assassin.h"

#include "Components/CapsuleComponent.h"
#include "Subsystems/DelegateBridgeSubsystem.h"


// Sets default values
AEnemy_Assassin::AEnemy_Assassin()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("CloakedEnemyPreset"));
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
}

// Called when the game starts or when spawned
void AEnemy_Assassin::BeginPlay()
{
	Super::BeginPlay();
	auto delegate_manager = GetWorld()->GetSubsystem<UDelegateBridgeSubsystem>();
	delegate_manager->BindOnHPChanged(GetCharacterStat(), this, &AEnemy_Assassin::OnAction);
}

void AEnemy_Assassin::OnAction(float hp_ratio)
{
	if (is_cloaked_)
	{
		UE_LOG(LogTemp, Error, TEXT("Clock Done!!!"));
		//만약 공격을 받아 은폐가 끝난다면 스턴.
		if (hp_ratio < 1.f)
		{
			GetStunned(3.f);
		}
		is_cloaked_ = false;
		GetCapsuleComponent()->SetCollisionProfileName(TEXT("EnemyPreset"));
		//Cloaking 해제 VFX 발동.
	}
}

void AEnemy_Assassin::Attack(AActor* target)
{
	Super::Attack(target);
	OnAction(0.f);
}