/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 2.1.2025
Summary : Header file for the ArmorMechanics.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Structs/ArmorData.h"
#include "Structs/DamageData.h"
#include "ArmorMechanics.generated.h"

//TODO
//1. UDataTable* armor_table_;를 다른곳으로 옮기기. 모든 영웅이 armor_table_를 가질 필요는 없다.
//2. TestSkill를 포함할 함수 배열 만들기.
//3. Dmg와 HP를 계산하는 부분에서 skill이 사용되게 만들기.
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECT_IK_API UArmorMechanics : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UArmorMechanics();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	//Demo: TestSkill_1은 받는 피해를 고정적으로 3씩 차감한다.
	void TestSkill_1_Prepare();
	FDamageData TestSkill_1(FDamageData dmg_input);
	void TestSkill_1_Terminate();

public:
	void EquipArmor();
	void UnEquipArmor();
	void ParseArmorData(EArmorType type);
	FArmorData GetArmorData();
	FString EnumToString(EArmorType armor_type);

private:
	EArmorType equipped_armor_type_;
	FArmorData equipped_armor_data_;
	UDataTable* armor_table_;
};
