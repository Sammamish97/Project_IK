/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 2.03.2025
Summary : Source file for Armor skill cluster.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Abilities/ArmorSkillCluster.h"

FDamageData ArmorSkillCluster::TestSkill_1(FDamageData dmg_input)
{
	dmg_input.damage -= 3;
	return dmg_input;
}