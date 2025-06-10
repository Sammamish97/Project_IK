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
#include "UI/HP_UI_Widget.h"
#include "UI/UnitWidget.h"
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
	UUnitWidget* unit_widget = Cast<UUnitWidget>(hp_UI_->GetWidget());
	if (unit_widget)
	{
		unit_widget->InitUnitWidget(character_stat_component_->GetMaxHitPoint(), character_stat_component_->GetHitPoint());
		subsystem->BindOnHPOrShieldChanged(character_stat_component_, unit_widget->GetHPWidget(), &UHP_UI_Widget::UpdateWidget);
		subsystem->BindOnCrowdControlChanged(cc_component_, unit_widget, &UUnitWidget::UpdateAppliedCCs);
		subsystem->BindOnBuffChanged(character_stat_component_, unit_widget, &UUnitWidget::UpdateAppliedBuffs);
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
