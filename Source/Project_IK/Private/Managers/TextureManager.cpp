/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 12.05.2024
Summary : Source file for texture manager.
					It loads all textures using in the game at the beginning of the game.
					Provide when codes needed.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Managers/TextureManager.h"

#include "AssetRegistry/AssetRegistryModule.h"

#include "Components/CharacterStatComponent.h"

void UTextureManager::InitializeTextures()
{
	GetAllTexturesInFolder("/Game/Images");
}

UTexture2D* UTextureManager::GetTexture(const FString& Key) const
{
	if (textures_.Contains(Key))
	{
		TSoftObjectPtr<UTexture2D> soft_texture = textures_[Key];
		// In the case you want it to be asynchronously, call LoadAssetAsync with 
		// a passed callback function that takes pointer to UTexture2D.
		return soft_texture.LoadSynchronous();
	}
	return nullptr;
}

UTexture2D* UTextureManager::GetBuffTexture(ECharacterStatType StatType) const
{
	switch (StatType)
	{
	case ECharacterStatType::AttackPower:
		return GetTexture("attack_power");
		break;
	case ECharacterStatType::AttackSpeed:
		return GetTexture("fire_rate_burst");
		break;
	case ECharacterStatType::CriticalHitRate:
		return GetTexture("critical_hit_rate");
		break;
	case ECharacterStatType::Accuracy:
		return GetTexture("accuracy");
		break;
	case ECharacterStatType::MagazineBonus:
		break;
	case ECharacterStatType::LifeSteal:
		break;
	case ECharacterStatType::HitPoints:
		return GetTexture("hit_points");
		break;
	case ECharacterStatType::EvasionRate:
		return GetTexture("evasion");
		break;
	case ECharacterStatType::Armor:
		return GetTexture("armor");
		break;
	case ECharacterStatType::Survivability:
		break;
	case ECharacterStatType::SightRange:
		return GetTexture("signt_range");
		break;
	case ECharacterStatType::MoveSpeed:
		return GetTexture("move_speed");
		break;
	case ECharacterStatType::SkillPower:
		break;
	case ECharacterStatType::SkillCoolDown:
		break;
	case ECharacterStatType::Shield:
		break;
	default:
		break;
	}
	return nullptr;
}

UTexture2D* UTextureManager::GetCCTexture(ECCType CCType) const
{
	switch (CCType)
	{
	case ECCType::DroneJamming:
		return GetTexture("drone_jamming");
		break;
	case ECCType::Silence:
		return GetTexture("silence");
		break;
	case ECCType::MuteItems:
		return GetTexture("mute_items");
		break;
	case ECCType::Stun:
		return GetTexture("stun");
		break;
	case ECCType::Bleeding:
		// @@ TODO: Add bleeding texture
		return GetTexture("stun");
		break;
	default:
		break;
	}
	return nullptr;
}

void UTextureManager::GetAllTexturesInFolder(const FString& FolderPath)
{
	FAssetRegistryModule& asset_registry_module = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");

	FARFilter filter;
	filter.PackagePaths.Add(*FolderPath);
	// Include subfolders
	filter.bRecursivePaths = true;
	// Ensures retrieving only texture assets.
	filter.ClassPaths.Add(UTexture2D::StaticClass()->GetClassPathName());

	TArray<FAssetData> asset_data_list;
	asset_registry_module.Get().GetAssets(filter, asset_data_list);

	for (const FAssetData& data : asset_data_list)
	{
		TSoftObjectPtr<UTexture2D> soft_texture(data.ToSoftObjectPath());
		textures_.Add(data.AssetName.ToString(), soft_texture);
	}
}
