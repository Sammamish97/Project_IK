/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.20.2024
Summary : Source file for enemy base.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Characters/EnemyBase.h"

#include "Components/CharacterStatComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystems/DelegateBridgeSubsystem.h"
#include "UI/BuffContainer.h"
#include "UI/EnemyHPUI.h"
#include "WorldSettings/IKGameModeBase.h"
#include "WorldSettings/IKHUD.h"

#include "Subsystems/AudioManagerSubsystem.h"

AEnemyBase::AEnemyBase()
{
	GetMesh()->SetCollisionProfileName(TEXT("EnemyPreset"));
	forward_dir_ = {-1,0, 0};
	is_hero_ = false;
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	UDelegateBridgeSubsystem* subsystem = GetWorld()->GetSubsystem<UDelegateBridgeSubsystem>();

	if (UEnemyHPUI* hp_widget = Cast<UEnemyHPUI>(hp_widget_component_->GetWidget()))
	{
		OnApplyBuff.AddDynamic(hp_widget->GetBuffContainer(), &UBuffContainer::EnqueueBuff);
		OnBuffExpired.AddDynamic(hp_widget->GetBuffContainer(), &UBuffContainer::UpdateQueue);

		hp_widget->GetHPUICore()->InitHPWidget(character_stat_component_->GetMaxHitPoint(), character_stat_component_->GetHitPoint());
		subsystem->BindOnHPOrShieldChanged(character_stat_component_, hp_widget->GetHPUICore().Get(), &UHPUICore::UpdateWidget);
	}

	if (AIKPlayerController* pc = Cast<AIKPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
	{
		pc->AddEnemyToCameraManager(this);
		Cast<AIKHUD>(pc->GetHUD())->BindEnemyHPUI(this);
	}
}

void AEnemyBase::Die()
{
	AIKGameModeBase* casted_mode = Cast<AIKGameModeBase>(UGameplayStatics::GetGameMode(this));
	if(casted_mode) casted_mode->RemoveEnemy(this);
	UAudioManagerSubsystem::Get(this)->PlayAtLocation(EAudioType::EnemyDied, GetActorLocation());
	Super::Die();
}
