/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.18.2025
Summary : Source file for Buff Containing Cover.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Environments/BuffContainingCover.h"

#include "Characters/HeroBase.h"

void ABuffContainingCover::InitBuffData(const FItemData& item_data)
{
	buff_ui_data_.buff_type_ = EBuffType::DeployCover;
	buff_ui_data_.duration_ = 0.f;
	buff_ui_data_.is_permanent_ = true;
	buff_ui_data_.item_data_ = item_data;
}

ABuffContainingCover::ABuffContainingCover()
{
	buff_amount_ = 20.f;
	
	buff_status_.duration_ = 0.f;
	buff_status_.is_permanent_ = true;
	buff_status_.is_percentage_ = true;
	buff_status_.stat_type_ = ECharacterStatType::AttackSpeed;
	buff_status_.value_ = buff_amount_;
}

void ABuffContainingCover::BeginPlay()
{
	Super::BeginPlay();
}

void ABuffContainingCover::OnSettleDown(AActor* hidden_unit)
{
	Super::OnSettleDown(hidden_unit);
	AHeroBase* casted_hero = Cast<AHeroBase>(hidden_unit_);
	casted_hero->ApplyBuff(EBuffType::DeployCover, buff_status_);
	casted_hero->AddBuffUI(buff_ui_data_);
}

void ABuffContainingCover::OnLeave()
{
	AHeroBase* casted_hero = Cast<AHeroBase>(hidden_unit_);
	casted_hero->RemoveBuff(EBuffType::DeployCover);
	casted_hero->RemoveBuffUI(EBuffType::DeployCover);
	Super::OnLeave();
}
