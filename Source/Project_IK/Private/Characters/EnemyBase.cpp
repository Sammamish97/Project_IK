/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.20.2024
Summary : Source file for enemy base.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Characters/EnemyBase.h"

#include "Components/CapsuleComponent.h"
#include "Components/CharacterStatComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystems/DelegateBridgeSubsystem.h"
#include "UI/HitPointsUI.h"
#include "WorldSettings/IKGameModeBase.h"

AEnemyBase::AEnemyBase()
{
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("EnemyPreset"));
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
	forward_dir_ = {-1,0, 0};
	is_hero_ = false;
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	UDelegateBridgeSubsystem* subsystem = GetWorld()->GetSubsystem<UDelegateBridgeSubsystem>();
	UHitPointsUI* ui = Cast<UHitPointsUI>(hp_UI_->GetWidget());
	if (ui)
	{
		subsystem->BindOnCrowdControlChanged(cc_component_, ui, &UHitPointsUI::UpdateAppliedCCs);
		subsystem->BindOnHPChanged(character_stat_component_, ui, &UHitPointsUI::UpdateHPWidget);
		subsystem->BindOnShieldChanged(character_stat_component_, ui, &UHitPointsUI::UpdateShieldWidget);
		subsystem->BindOnBuffChanged(character_stat_component_, ui, &UHitPointsUI::UpdateAppliedBuffs);
	}
	hp_UI_->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	hp_UI_->SetDrawSize({ 100, 50 });
}

void AEnemyBase::Die()
{
	AIKGameModeBase* casted_mode = Cast<AIKGameModeBase>(UGameplayStatics::GetGameMode(this));
	if(casted_mode) casted_mode->RemoveEnemy(this);
	Super::Die();
}
