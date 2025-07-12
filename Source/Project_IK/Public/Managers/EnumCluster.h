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
	OnLogic UMETA(DisplayName = "On Logic"),
	OnReloading UMETA(DisplayName = "On Reloading"),
	OnActiveSkill UMETA(DisplayName = "On Active Skill"),
	OnStunned UMETA(DisplayName = "On Stunned"),
	OnRepositioning UMETA(DisplayName = "On Repositioning"),
};

UENUM(BlueprintType)
enum class ECCType : uint8
{
	Silence UMETA(DisplayName = "Silence"),
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
enum class ECombatEndState : uint8
{
	ShowingCombatResultUI UMETA(DisplayName = "ShowingCombatResultUI"),
	ShowingEquipmentRewardUI UMETA(DisplayName = "ShowingEquipmentRewardUI"),
	ShowingInventoryUI UMETA(DisplayName = "ShowingInventoryUI"),
	ShowingMapUI UMETA(DisplayName = "ShowingMapUI"),
	ShowingToMainmenu UMETA(DisplayName = "ShowingToMainmenu"),
};

UENUM(BlueprintType)
enum class EItemType : uint8
{
	HPPotion UMETA(DisplayName = "HPPotion"),
	Missile UMETA(DisplayName = "Missile"),
	Stimuli UMETA(DisplayName = "Stimuli"),
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
enum class ECharacterType  : uint8
{
	INVALID UMETA(DisplayName = "INVALID"),
	Hero1 UMETA(DisplayName = "Hero1"),
	Hero2 UMETA(DisplayName = "Hero2"),
	Hero3 UMETA(DisplayName = "Hero3"),
	Hero4 UMETA(DisplayName = "Hero4"),
	EnemySoldier UMETA(DisplayName = "EnemySoldier"),
	EnemySniper UMETA(DisplayName = "EnemySniper"),
	EnemyKnight UMETA(DisplayName = "EnemyKnight"),
	EnemyLaserDrone	UMETA(DisplayName = "EnemyLaserDrone"),
	EnemyHealingPillar UMETA(DisplayName = "EnemyHealingPillar"),
	EnemyHeavyGunner UMETA(DisplayName = "EnemyHeavyGunner"),
	EnemyOfficer UMETA(DisplayName = "EnemyOfficer"),
	EnemyAssassin UMETA(DisplayName = "EnemyAssassin"),
};

UENUM(BlueprintType)
enum class EHeroType  : uint8
{
	INVALID UMETA(DisplayName = "INVALID"),
	Hero1 UMETA(DisplayName = "Hero1"),
	Hero2 UMETA(DisplayName = "Hero2"),
	Hero3 UMETA(DisplayName = "Hero3"),
	Hero4 UMETA(DisplayName = "Hero4"),
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

inline ECharacterType HeroTypeToCharacterType(EHeroType hero_type)
{
	switch (hero_type)
	{
	case EHeroType::Hero1:
		return ECharacterType::Hero1;
	case EHeroType::Hero2:
		return ECharacterType::Hero2;
	case EHeroType::Hero3:
		return ECharacterType::Hero3;
	case EHeroType::Hero4:
		return ECharacterType::Hero4;
	default:
		return ECharacterType::INVALID;
	}
}

inline EHeroType CharacterTypeToHeroType(ECharacterType character_type)
{
	switch (character_type)
	{
	case ECharacterType::Hero1:
		return EHeroType::Hero1;
	case ECharacterType::Hero2:
		return EHeroType::Hero2;
	case ECharacterType::Hero3:
		return EHeroType::Hero3;
	case ECharacterType::Hero4:
		return EHeroType::Hero4;
	default:
		return EHeroType::INVALID;
	}
}

UENUM(BlueprintType)
enum class ERarity : uint8
{
	Common UMETA(DisplayName = "Common"),
	Rare UMETA(DisplayName = "Rare"),
	Legendary UMETA(DisplayName = "Legendary")
};

UENUM(BlueprintType)
enum class EDamageType : uint8
{
	INVALID UMETA(DisplayName = "INVALID"), 
	Projectile UMETA(DisplayName = "Projectile"),
	Explosive UMETA(DisplayName = "Explosive"),
	Melee UMETA(DisplayName = "Melee"),
	Dot UMETA(DisplayName = "Dot"),
	Magic UMETA(DisplayName = "Magic"),
};

UENUM(BlueprintType)
enum class EUnitEvent : uint8
{
	OnDie UMETA(DisplayName = "OnDie"),
	OnStun UMETA(DisplayName = "OnStun"),
	OnReload UMETA(DisplayName = "OnReload"),
	OnFire UMETA(DisplayName = "OnFire"),
	OnActiveSkill UMETA(DisplayName = "OnActiveSkill"),
	OnMove UMETA(DisplayName = "OnMove"),
	OnEliminate UMETA(DisplayName = "OnEliminate"),
	OnCriticalFire UMETA(DisplayName = "OnCriticalFire"),
	HideOnCover UMETA(DisplayName = "HideOnCover"),
	LeaveCover UMETA(DisplayName = "LeaveCover"),
	OnEnterBattle UMETA(DisplayName = "OnEnterBattle"),
};

UENUM(BlueprintType)
enum class EDamageEvent : uint8
{
	OnHitBeforeCalc UMETA(DisplayName = "OnHitBeforeCalc"),
	OnHitAfterCalc UMETA(DisplayName = "OnHitAfterCalc"),
	OnFireWeapon UMETA(DisplayName = "OnFireWeapon"),
	OnInvokeActiveSkill UMETA(DisplayName = "OnInvokeActiveSkill"),
};

UENUM(BlueprintType)
enum class EGearType : uint8
{
	INVALID UMETA(DisplayName = "INVALID"),
	Weapon UMETA(DisplayName = "Weapon"),
	ActiveSkill UMETA(DisplayName = "ActiveSkill"),
	PassiveSkill UMETA(DisplayName = "PassiveSkill"),
	SupportSkill UMETA(DisplayName = "SupportSkill"),
	Rune UMETA(DisplayName = "Rune"),
};

UENUM(BlueprintType)
enum class EInventorySlotType : uint8
{
	INVALID UMETA(DisplayName = "INVALID"),
	Weapon UMETA(DisplayName = "WeaponBoardSlot"),
	ActiveSkill UMETA(DisplayName = "ActiveSkillBoardSlot"),
	PassiveSkill UMETA(DisplayName = "PassiveSkillBoardSlot"),
	SupportSkill UMETA(DisplayName = "SupportSkillBoardSlot"),
	Rune_0 UMETA(DisplayName = "Rune_0"),
	Rune_1 UMETA(DisplayName = "Rune_0"),
	Rune_2 UMETA(DisplayName = "Rune_0"),
	Rune_3 UMETA(DisplayName = "Rune_0"),
	Rune_4 UMETA(DisplayName = "Rune_0"),
	Rune_5 UMETA(DisplayName = "Rune_0"),
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

inline FText ECharStatToString(ECharacterStatType stat)
{
	switch (stat)
	{
	case ECharacterStatType::AttackPower:
		return NSLOCTEXT("Stat", "StatTypeAttackPower", "Attack Power");
	case ECharacterStatType::AttackSpeed:
		return NSLOCTEXT("Stat", "StatTypeAttackSpeed", "Attack Speed");
	case ECharacterStatType::SkillPower:
		return NSLOCTEXT("Stat", "StatTypeSkillPower", "SKill Power");
	default:
		return NSLOCTEXT("Stat", "Default", "DEFAULT");
	}
}

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	INVALID UMETA(DisplayName = "INVALID"),
	DefaultPistol UMETA(DisplayName = "DefaultPistol"),
	
	Pistol_B UMETA(DisplayName = "Pistol_B"),
	AssaultRifle_B UMETA(DisplayName = "AssaultRifle_B"),
	ShotGun_B UMETA(DisplayName = "ShotGun_B"),
	SniperRifle_B UMETA(DisplayName = "SniperRifle_B"),
	
	Pistol_A UMETA(DisplayName = "Pistol_A"),
	AssaultRifle_A UMETA(DisplayName = "AssaultRifle_A"),
	ShotGun_A UMETA(DisplayName = "ShotGun_A"),
	SniperRifle_A UMETA(DisplayName = "SniperRifle_A"),

	HeavyGunnerWeapon UMETA(DisplayName = "HeavyGunnerWeapon"),
	OfficerWeapon UMETA(DisplayName = "OfficerWeapon"),
	AssassinWeapon UMETA(DisplayName = "AssassinWeapon")
};

UENUM(BlueprintType)
enum class EBulletType : uint8
{
	INVALID UMETA(DisplayName = "INVALID"),
	FMJ UMETA(DisplayName = "FMJ"),
	Buckshot UMETA(DisplayName = "Buckshot"),
};

UENUM(BlueprintType)
enum class EPassiveSkillType : uint8
{
	INVALID UMETA(DisplayName = "INVALID"),
	FixedDmgReduce UMETA(DisplayName = "FixedDmgReduce"),
	RandDmgIncrease UMETA(DisplayName = "RandDmgIncrease"),
	Agility UMETA(DisplayName = "Agility"),
	Regenerate UMETA(DisplayName = "Regenerate"),
	Berserker UMETA(DisplayName = "Berserker"),
	Executioner UMETA(DisplayName = "Executioner"),
	CloseQuartersMastery UMETA(DisplayName = "CloseQuartersMastery"),
	LowProfile UMETA(DisplayName = "LowProfile"),
	StableFirstRound UMETA(DisplayName = "StableFirstRound"),
};

UENUM(BlueprintType)
enum class EActiveSkillType : uint8
{
	INVALID UMETA(DisplayName = "INVALID"),
	
	Thunder_B UMETA(DisplayName = "Thunder_B"),
	Thunder_A UMETA(DisplayName = "Thunder_A"),
	
	ThunderStorm_B UMETA(DisplayName = "ThunderStorm_B"),
	ThunderStorm_A UMETA(DisplayName = "ThunderStorm_A"),
	
	FateSpiral_B UMETA(DisplayName = "FateSpiral_B"),
	FateSpiral_A UMETA(DisplayName = "FateSpiral_A"),
	
	Encourage_B UMETA(DisplayName = "Encourage_B"),
	Encourage_A UMETA(DisplayName = "Encourage_A"),

	DeploySentryGun_B UMETA(DisplayName = "DeploySentryGun_B"),
	DeploySentryGun_A UMETA(DisplayName = "DeploySentryGun_A"),
	
	DeployCover_B UMETA(DisplayName = "DeployCover_B"),
	DeployCover_A UMETA(DisplayName = "DeployCover_A"),
	
	TripleFire_B UMETA(DisplayName = "TripleFire_B"),
	TripleFire_A UMETA(DisplayName = "TripleFire_A"),
	
	ChargeShot_B UMETA(DisplayName = "ChargeShot_B"),
	ChargeShot_A UMETA(DisplayName = "ChargeShot_A"),
	
	MagnetizedBullet_B UMETA(DisplayName = "MagnetizedBullet_B"),
	MagnetizedBullet_A UMETA(DisplayName = "MagnetizedBullet_A"),

	Ricochet_B UMETA(DisplayName = "Ricochet_B"),
	Ricochet_A UMETA(DisplayName = "Ricochet_A"),
};

UENUM(BlueprintType)
enum class EFireType : uint8
{
	INVALID UMETA(DisplayName = "INVALID"),
	Auto UMETA(DisplayName = "Auto"),
	Burst UMETA(DisplayName = "Burst"),
	PreHeating UMETA(DisplayName = "PreHeating"),
	BoltAction UMETA(DisplayName = "BoltAction")
};

UENUM(BlueprintType)
enum class ERuneSetType : uint8
{
	INVALID UMETA(DisplayName = "INVALID"),
	Chariot UMETA(DisplayName = "Chariot"),
	GreatBow UMETA(DisplayName = "GreatBow"),
	Dagger UMETA(DisplayName = "Dagger"),
	Quake UMETA(DisplayName = "Quake"),
	Tempest UMETA(DisplayName = "Tempest"),
	Viper UMETA(DisplayName = "Viper"),
	Poet UMETA(DisplayName = "Poet"),
};

UENUM(BlueprintType)
enum class ERuneBonusType : uint8
{
	INVALID UMETA(DisplayName = "INVALID"),
	Edge UMETA(DisplayName = "Edge"),
	Triangle UMETA(DisplayName = "Triangle"),
	Hexagon UMETA(DisplayName = "Hexagon"),
};


UENUM(BlueprintType)
enum class EGlobalBuffType : uint8
{
	WoundingBullets UMETA(DisplayName = "WoundingBullets"),
	Deathbound_Hero1 UMETA(DisplayName = "Deathbound Hero1"),
	Deathbound_Hero2 UMETA(DisplayName = "Deathbound Hero2"),
	Deathbound_Hero3 UMETA(DisplayName = "Deathbound Hero3"),
	Deathbound_Hero4 UMETA(DisplayName = "Deathbound Hero4"),
	None UMETA(DisplayName = "None"),
};

inline EGlobalBuffType HeroTypeToDeathbound(EHeroType hero_type)
{
	switch (hero_type)
	{
	case EHeroType::Hero1:
		return EGlobalBuffType::Deathbound_Hero1;
		break;
	case EHeroType::Hero2:
		return EGlobalBuffType::Deathbound_Hero2;
		break;
	case EHeroType::Hero3:
		return EGlobalBuffType::Deathbound_Hero3;
		break;
	case EHeroType::Hero4:
		return EGlobalBuffType::Deathbound_Hero4;
		break;
	default:
		return EGlobalBuffType::None;
		break;
	}
}

inline EHeroType DeathboundToHeroType(EGlobalBuffType buff_type)
{
	switch (buff_type)
	{
	case EGlobalBuffType::Deathbound_Hero1:
		return EHeroType::Hero1;
		break;
	case EGlobalBuffType::Deathbound_Hero2:
		return EHeroType::Hero2;
		break;
	case EGlobalBuffType::Deathbound_Hero3:
		return EHeroType::Hero3;
		break;
	case EGlobalBuffType::Deathbound_Hero4:
		return EHeroType::Hero4;
		break;
	default:
		return EHeroType::INVALID;
		break;
	}
}


UENUM(BlueprintType)
enum class ETargetingState : uint8
{
	Idle UMETA(DisplayName = "Idle"),
	ActiveSKill UMETA(DisplayName = "ActiveSKill"),
	SupportSkill UMETA(DisplayName = "SupportSkill"),
};

UENUM(BlueprintType)
enum class ERunResultState : uint8
{
	ShowingRunRewardUI UMETA(DisplayName = "ShowingRunRewardUI"),
	ShowingToMainMenuUI UMETA(DisplayName = "ShowingToMainMenuUI"),
};

UENUM(BlueprintType)
enum class EEventType : uint8
{
	INVALID UMETA(DisplayName = "INVALID"),
	EventType_1 UMETA(DisplayName = "EventType_1"),
	EventType_2 UMETA(DisplayName = "EventType_2"),
	EventType_3 UMETA(DisplayName = "EventType_3"),
	EventType_4 UMETA(DisplayName = "EventType_4"),
};

UENUM(BlueprintType)
enum class EWeaponAnimationType : uint8
{
	INVALID UMETA(DisplayName = "INVALID"),
	Pistol UMETA(DisplayName = "Pistol"),
	Rifle UMETA(DisplayName = "Rifle"),
	Minigun UMETA(DisplayName = "Minigun"),
};

UENUM(BlueprintType)
enum class EAIFindTargetType : uint8
{
	INVALID UMETA(DisplayName = "INVALID"),
	Nearest UMETA(DisplayName = "Nearest"),
	Farthest UMETA(DisplayName = "Farthest"),
	Random UMETA(DisplayName = "Random"),
	Weakest UMETA(DisplayName = "Weakest")
};

UENUM(BlueprintType)
enum class EUnitBoneType : uint8
{
	INVALID UMETA(DisplayName = "INVALID"),
	Humanoid_Gunner UMETA(DisplayName = "HeroHumanoid"),
};

UENUM(BlueprintType)
enum class EWeaponAction : uint8
{
	INVALID UMETA(DisplayName = "INVALID"),
	Fire UMETA(DisplayName = "Fire"),
	Reload UMETA(DisplayName = "Reload"),
};

UENUM(BlueprintType)
enum class ESupportSkillType : uint8
{
	INVALID UMETA(DisplayName = "INVALID"),
	Reposition UMETA(DisplayName = "Reposition"),
	SupportFire UMETA(DisplayName = "SupportFire"),
	InstantRepair UMETA(DisplayName = "InstantRepair"),
};

UENUM(BlueprintType)
enum class EOutlineState : uint8
{
	INVALID UMETA(DisplayName = "INVALID"),
	Disable UMETA(DisplayName = "Disable"),
	Red UMETA(DisplayName = "Red"),
	Yellow UMETA(DisplayName = "Yellow"),
	Green UMETA(DisplayName = "Green"),
};

UENUM(BlueprintType)
enum class EBuffType : uint8
{
	INVALID UMETA(DisplayName = "INVALID"),
	//Active
	MagnetizedBullet_A UMETA(DisplayName = "MagnetizedBullet_A"),

	//Passive
	InstantRepair UMETA(DisplayName = "InstantRepair"),
	Encourage UMETA(DisplayName = "Encourage"),
	DeployCover UMETA(DisplayName = "DeployCover"),
	Agility UMETA(DisplayName = "Agility"),
	Berserker UMETA(DisplayName = "Berserker"),
	LowProfile UMETA(DisplayName = "LowProfile"),

	//Rune
	Chariot_Edge UMETA(DisplayName = "Chariot_Edge"),
	Chariot_Triangle UMETA(DisplayName = "Chariot_Edge"),
	Chariot_Hexagon UMETA(DisplayName = "Chariot_Hexagon"),
	
	Dagger_Edge UMETA(DisplayName = "Dagger_Edge"),
	Dagger_Triangle UMETA(DisplayName = "Dagger_Triangle"),
	Dagger_Hexagon UMETA(DisplayName = "Dagger_Hexagon"),
	
	Quake_Edge UMETA(DisplayName = "Quake_Edge"),
	Quake_Triangle UMETA(DisplayName = "Quake_Triangle"),
	Quake_Hexagon UMETA(DisplayName = "Quake_Hexagon"),
	
	Viper_Edge UMETA(DisplayName = "Viper_Edge"),
	Viper_Triangle UMETA(DisplayName = "Viper_Triangle"),
	Viper_Hexagon UMETA(DisplayName = "Viper_Hexagon"),

	//Global
	Deathbound UMETA(DisplayName = "Deathbound"),

};