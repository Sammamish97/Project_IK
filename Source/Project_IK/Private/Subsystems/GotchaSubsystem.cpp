/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 07.15.2025
Summary : Source file for a subsystem that manages data about Gotcha.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Subsystems/GotchaSubsystem.h"

void UGotchaSubsystem::SetNumMaxPull(int32 num_max_pull)
{
	num_max_pull_ = num_max_pull;
}

int32 UGotchaSubsystem::GetNumMaxPull() const
{
	return num_max_pull_;
}

void UGotchaSubsystem::SetSeedWeightRarity(ERarity seed_weight_rarity)
{
	seed_weight_rarity_ = seed_weight_rarity;
}

ERarity UGotchaSubsystem::GetSeedWeightRarity() const
{
	return seed_weight_rarity_;
}
