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
#include "EnumCluster.generated.h"

UENUM(BlueprintType)
enum class EUnitState  : uint8
{
	Forwarding UMETA(DisplayName = "Forwarding"),
	HeadingToEnemy UMETA(DisplayName = "Heading To Enemy"),
	HeadingToCover UMETA(DisplayName = "Heading To Cover"),
	Attacking UMETA(DisplayName = "Attacking"),
	Reloading UMETA(DisplayName = "Reloading"),
	Stunned UMETA(DisplayName = "Stunned"),
	Repositioning UMETA(DisplayName = "Repositioning"),
};

UENUM(BlueprintType)
enum class ECCType : uint8
{
	DroneJamming UMETA(DisplayName = "DroneJamming"),
	Silence UMETA(DisplayName = "Silence"),
	MuteItems UMETA(DisplayName = "MuteItems"),
	Stun UMETA(DisplayName = "Stun"),
	Bleeding UMETA(DisplayName = "Bleeding"),
};

UENUM(BlueprintType)
enum class NodeType : uint8
{
	None UMETA(DisplayName = "None"),
	Enemy UMETA(DisplayName = "Enemy"),
	Merchant UMETA(DisplayName = "Merchant"),
	Event UMETA(DisplayName = "Event"),
	Boss UMETA(DisplayName = "Boss"),
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

inline EHeroType IntToHeroType(int32 hero_idx)
{
	switch (hero_idx)
	{
	case 0:
		return EHeroType::Hero1;
	case 1:
		return EHeroType::Hero2;
	case 2:
		return EHeroType::Hero3;
	case 3:
		return EHeroType::Hero4;
	default:
		return EHeroType::INVALID;
	}
}

inline int32 HeroTypeToInt(EHeroType hero_type)
{
	switch (hero_type)
	{
		case EHeroType::Hero1:
			return 0;
		case EHeroType::Hero2:
			return 1;
		case EHeroType::Hero3:
			return 2;
		case EHeroType::Hero4:
			return 3;
		case EHeroType::INVALID:
		default:
			return -1;
	}
}

UENUM(BlueprintType)
enum class ERarity : uint8
{
	None UMETA(DisplayName = "None"),
	S UMETA(DisplayName = "S"),
	A UMETA(DisplayName = "A"),
	B UMETA(DisplayName = "B")
};

UENUM(BlueprintType)
enum class EDamageType : uint8
{
	Projectile UMETA(DisplayName = "Projectile"),
	Explosive UMETA(DisplayName = "Explosive"),
	Melee UMETA(DisplayName = "Melee"),
	Dot UMETA(DisplayName = "Dot"),
	Magic UMETA(DisplayName = "Magic"),
	INVALID UMETA(DisplayName = "INVALID")
};

UENUM(BlueprintType)
enum class EUnitEvent : uint8
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
	Weapon UMETA(DisplayName = "Weapon"),
	ActiveSkill UMETA(DisplayName = "ActiveSkill"),
	PassiveSkill UMETA(DisplayName = "PassiveSkill"),
	Oopart UMETA(DisplayName = "Oopart"),
	INVALID UMETA(DisplayName = "INVALID")
};

UENUM(BlueprintType)
enum class EInventorySlotType : uint8
{
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
	SightRange UMETA(DisplayName = "SightRange"),
	MoveSpeed UMETA(DisplayName = "MoveSpeed"),
	SkillPower UMETA(DisplayName = "SkillPower"),
	SkillCoolDown UMETA(DisplayName = "SkillCoolDown"),
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

UENUM(BlueprintType)
enum class EOopartType : uint8
{
	HealingWaves UMETA(DisplayName = "HealingWaves"),
	AttackSpeedBoost UMETA(DisplayName = "AttackSpeedBoost"),
	Empty UMETA(DisplayName = "Empty")
};

UENUM(BlueprintType)
enum class EActiveSkillType : uint8
{
	Thunder UMETA(DisplayName = "Thunder"),
	RapidFire UMETA(DisplayName = "RapidFire"),
	Empty UMETA(DisplayName = "Empty")
};

UENUM(BlueprintType)
enum class EFireType : uint8
{
	INVALID UMETA(DisplayName = "INVALID"),
	Auto UMETA(DisplayName = "Auto"),
	Burst UMETA(DisplayName = "Burst"),
	BoltAction UMETA(DisplayName = "BoltAction")
};

UENUM(BlueprintType)
enum class ERuneSetType : uint8
{
	INVALID UMETA(DisplayName = "INVALID"),
	ThunderLord UMETA(DisplayName = "ThunderLord"),
	Chariot UMETA(DisplayName = "Chariot")
};

UENUM(BlueprintType)
enum class EGlobalBuffType : uint8
{
	WoundingBullets UMETA(DisplayName = "WoundingBullets"),
	None UMETA(DisplayName = "None"),
};

UENUM(BlueprintType)
enum class ETargetingState : uint8
{
	Idle UMETA(DisplayName = "Idle"),
	ActiveSKill UMETA(DisplayName = "ActiveSKill"),
	Item UMETA(DisplayName = "Item"),
	EnterRepositioning UMETA(DisplayName = "Repositioning"),
	PickRepositionTargetLocation UMETA(DisplayName = "PickRepositionTargetLocation")
};