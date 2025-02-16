/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 12.04.2024
Summary : Header file for the EnumCluster.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EnumCluster.generated.h"

UENUM(BlueprintType)
enum class EDPType : uint8
{
	Empty UMETA(DisplayName = "Empty"),
	FireRateBurst UMETA(DisplayName = "Fire Rate"),
	FireRange UMETA(DisplayName = "Fire Range"),
	HealingWaves UMETA(DisplayName = "Healing Waves"),
	LaserBeam UMETA(DisplayName = "LaserBeam"),
	INVALID UMETA(DisplayName = "Invalid")
};

UENUM(BlueprintType)
enum class EUnitState  : uint8
{
	Forwarding UMETA(DisplayName = "Forwarding"),
	HeadingToEnemy UMETA(DisplayName = "Heading To Enemy"),
	HeadingToCover UMETA(DisplayName = "Heading To Cover"),
	Attacking UMETA(DisplayName = "Attacking"),
	Reloading UMETA(DisplayName = "Reloading"),
	Stunned UMETA(DisplayName = "Stunned"),
};

UENUM(BlueprintType)
enum class EDroneState  : uint8
{
	Idle UMETA(DisplayName = "Idle"),
	BannedDP UMETA(DisplayName = "BannedDP"),
	UsingPeriodicDP UMETA(DisplayName = "UsingPeriodicDP"),
	UsingGeneralDP UMETA(DisplayName = "UsingGeneralDP")
};

UENUM(BlueprintType)
enum class ECCType : uint8
{
	DroneJamming UMETA(DisplayName = "DroneJamming"),
	Silence UMETA(DisplayName = "Silence"),
	MuteItems UMETA(DisplayName = "MuteItems"),
	Stun UMETA(DisplayName = "Stun"),
};

UENUM(BlueprintType)
enum class NodeType : uint8
{
	None UMETA(DisplayName = "None"),
	Enemy UMETA(DisplayName = "Enemy"),
};

UENUM(BlueprintType)
enum class ELevelEndState : uint8
{
	ShowingCombatResultUI UMETA(DisplayName = "ShowingCombatResultUI"),
	ShowingItemPickerUI UMETA(DisplayName = "ShowingItemPickerUI"),
	ShowingMapUI UMETA(DisplayName = "ShowingMapUI"),
};

UENUM(BlueprintType)
enum class EItemLogicType : uint8
{
	None UMETA(DisplayName = "None"),
	RestoreHP UMETA(DisplayName = "RestoreHP"),
	LaunchMissile UMETA(DisplayName = "LaunchMissile"),
	AttackSpeedStimuli UMETA(DisplayName = "AttackSpeedStimuli"),
	SmokeGrenade UMETA(DisplayName = "SmokeGrenade"),
	Flashbang UMETA(DisplayName = "Flashbang"),
};

UENUM(BlueprintType)
enum class ETargetingMode : uint8
{
	None UMETA(DisplayName = "None"),
	Actor UMETA(DisplayName = "Actor"),
	Location UMETA(DisplayName = "Location"),
	Direction UMETA(DisplayName = "Direction"),
};

UENUM(BlueprintType)
enum class ETargetType : uint8
{
	None UMETA(DisplayName = "None"),
	Allies UMETA(DisplayName = "Allies"),
	Opponents UMETA(DisplayName = "Opponents"),
	All UMETA(DisplayName = "All"),
};

UENUM(BlueprintType)
enum class EDialogueEventType : uint8
{
	GetRandomItem UMETA(DisplayName = "GetRandomItem"),
	GetRandomDP UMETA(DisplayName = "GetRandomDP"),
	GetFireRateBurstDP UMETA(DisplayName = "GetFireRateBurstDP"),
	GetFireRangeDP UMETA(DisplayName = "GetFireRangeDP")
};

UENUM(BlueprintType)
enum class EHeroType  : uint8
{
	Hero1 UMETA(DisplayName = "Hero1"),
	Hero2 UMETA(DisplayName = "Hero2"),
	Hero3 UMETA(DisplayName = "Hero3"),
	Hero4 UMETA(DisplayName = "Hero4"),
	INVALID UMETA(DisplayName = "INVALID")
};

UENUM(BlueprintType)
enum class ERarity : uint8
{
	None UMETA(DisplayName = "None"),
	S UMETA(DisplayName = "S"),
	A UMETA(DisplayName = "A"),
	B UMETA(DisplayName = "B")
};

UENUM(BlueprintType)
enum class EArmorType : uint8
{
	TestHealth UMETA(DisplayName = "TestHealth"),
	TestArmor UMETA(DisplayName = "TestArmor"),
	TestDodge UMETA(DisplayName = "TestDodge"),
	TestSkillArmor UMETA(DisplayName = "TestSkillArmor"),
	Empty UMETA(DisplayName = "Empty")
};

UENUM(BlueprintType)
enum class ETrinketType : uint8
{
	TestAttack UMETA(DisplayName = "TestAttack"),
	TestAttackSpeed UMETA(DisplayName = "TestAttackSpeed"),
	TestCrit UMETA(DisplayName = "TestCrit"),
	TestSkillTrinket UMETA(DisplayName = "TestSkillTrinket"),
	Empty UMETA(DisplayName = "Empty")
};

UENUM(BlueprintType)
enum class EDamageType : uint8
{
	Projectile UMETA(DisplayName = "Projectile"),
	Explosive UMETA(DisplayName = "Explosive"),
	Melee UMETA(DisplayName = "Melee"),
	Dot UMETA(DisplayName = "Dot"),
	INVALID UMETA(DisplayName = "INVALID")
};

UENUM(BlueprintType)
enum class EHeroEvent : uint8
{
	OnHitBeforeCalc UMETA(DisplayName = "OnHitBeforeCalc"),
	OnHitAfterCalc UMETA(DisplayName = "OnHitAfterCalc"),
	OnHeal UMETA(DisplayName = "OnHeal"),
	OnHPChanged UMETA(DisplayName = "OnHPChanged"),
	OnDie UMETA(DisplayName = "OnDie"),
	OnStun UMETA(DisplayName = "OnStun"),
	OnReload UMETA(DisplayName = "OnReload"),
	OnFire UMETA(DisplayName = "OnFire"),
	OnActiveSkill UMETA(DisplayName = "OnActiveSkill"),
	NONE
};

UENUM(BlueprintType)
enum class EGearType : uint8
{
	Armor UMETA(DisplayName = "Armor"),
	Trinket UMETA(DisplayName = "Trinket"),
	Weapon UMETA(DisplayName = "Weapon"),
	ActiveSkill UMETA(DisplayName = "ActiveSkill"),
	PassiveSkill UMETA(DisplayName = "PassiveSkill"),
	Oopart UMETA(DisplayName = "Oopart"),
	INVALID UMETA(DisplayName = "INVALID")
};

UENUM(BlueprintType)
enum class EInventorySlotType : uint8
{
	Armor UMETA(DisplayName = "Armor"),
	Trinket UMETA(DisplayName = "Trinket"),
	Weapon UMETA(DisplayName = "Weapon"),
	ActiveSkill UMETA(DisplayName = "ActiveSkill"),
	PassiveSkill UMETA(DisplayName = "PassiveSkill"),
	Oopart UMETA(DisplayName = "Oopart"),
	Inventory UMETA(DisplayName = "Inventory"),
	INVALID UMETA(DisplayName = "INVALID")
};

UENUM(BlueprintType)
enum class ECharacterStatType : uint8
{
	AttackPower UMETA(DisplayName = "AttackPower"),
	AttackSpeed UMETA(DisplayName = "AttackSpeed"),
	CriticalHitRate UMETA(DisplayName = "CriticalHitRate"),
	Accuracy UMETA(DisplayName = "Accuracy"),
	MagazineBonus UMETA(DisplayName = "MagazineBonus"),
	LifeSteal UMETA(DisplayName = "LifeSteal"),
	HitPoints UMETA(DisplayName = "HitPoints"),
	EvasionRate UMETA(DisplayName = "EvasionRate"),
	Armor UMETA(DisplayName = "Armor"),
	Survivability UMETA(DisplayName = "Survivability"),
	MoveSpeed UMETA(DisplayName = "MoveSpeed"),
	ActiveSkillPower UMETA(DisplayName = "ActiveSkillPower"),
	ActiveSkillCooldown UMETA(DisplayName = "ActiveSkillCooldown"),
	PassiveSkillPower UMETA(DisplayName = "PassiveSkillPower"),
	PassiveSkillCooldown UMETA(DisplayName = "PassiveSkillCooldown"),
	Shield UMETA(DisplayName = "Shield"),
};

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	Pistol UMETA(DisplayName = "Pistol"),
	AssaultRifle UMETA(DisplayName = "AssaultRifle"),
	ShotGun UMETA(DisplayName = "ShotGun"),
	SniperRifle UMETA(DisplayName = "SniperRifle"),
	Empty UMETA(DisplayName = "Empty")
};

UENUM(BlueprintType)
enum class EPassiveSkillType : uint8
{
	FixedDmgReduce UMETA(DisplayName = "FixedDmgReduce"),
	RandDmgIncrease UMETA(DisplayName = "RandDmgIncrease"),
	Empty UMETA(DisplayName = "Empty")
};

//TODO: 총알에 치유감소/도트딜/도탄 같은 효과를 실을 때 사용한다.
UENUM(BlueprintType)
enum class EAttackEffect : uint8
{
	Test1 UMETA(DisplayName = "Test1"),
	Test2 UMETA(DisplayName = "Test2"),
	Test3 UMETA(DisplayName = "Test3"),
	Empty UMETA(DisplayName = "Empty")
};