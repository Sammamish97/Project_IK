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
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UI/HPUICore.h"
#include "WorldSettings/IKGameModeBase.h"

AEnemyBase::AEnemyBase()
{
	GetMesh()->SetCollisionProfileName(TEXT("EnemyPreset"));
	forward_dir_ = {-1,0, 0};
	is_hero_ = false;
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	UHPUICore* widget = Cast<UHPUICore>(hp_UI_->GetWidget());
	if (widget)
	{
		widget->SetHPBarColor(FColor::Red);
	}
}

void AEnemyBase::Die()
{
	AIKGameModeBase* casted_mode = Cast<AIKGameModeBase>(UGameplayStatics::GetGameMode(this));
	if(casted_mode) casted_mode->RemoveEnemy(this);
	Super::Die();
}
