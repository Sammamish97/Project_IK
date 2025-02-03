/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 2.02.2025
Summary : Header file for ArmorManager.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Structs/ArmorData.h"
#include "Structs/DamageData.h"
#include "EnumCluster.h"
#include "ArmorManager.generated.h"
typedef TMap<EArmorType, TFunctionRef<FDamageData(FDamageData)>> ArmorSkillMap;

UCLASS()
class PROJECT_IK_API UArmorManager : public UObject
{
	GENERATED_BODY()
	
public:
	UArmorManager();
	void InitArmorManager();
	void InitArmorSkillMap();
	FArmorData GetArmorData(EArmorType type);
	const ArmorSkillMap& GetArmorSkillMap() const;
 	FString EnumToString(EArmorType armor_type);
	
private:
	UDataTable* armor_table_;
	ArmorSkillMap armor_skill_map_;
};
