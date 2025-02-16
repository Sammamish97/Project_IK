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
#include "Kismet/GameplayStatics.h"
#include "WorldSettings/IKGameModeBase.h"

AEnemyBase::AEnemyBase()
{
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("EnemyPreset"));
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
	forward_dir_ = {-1,0, 0};
}

void AEnemyBase::GetDamage(FDamageData data)
{
	Super::GetDamage(data);
	bool is_evaded = character_stat_component_->CalcDamage(data);
	character_stat_component_->GetDamage(data.damage);
	SetDamageUI(data, is_evaded);
}

void AEnemyBase::Die()
{
	AIKGameModeBase* casted_mode = Cast<AIKGameModeBase>(UGameplayStatics::GetGameMode(this));
	if(casted_mode) casted_mode->RemoveEnemy(this);
	Super::Die();
}
