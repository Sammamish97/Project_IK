/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 12.05.2024
Summary : Header file for texture manager.
					It loads all textures using in the game at the beginning of the game.
					Provide when codes needed.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TextureManager.generated.h"

enum class ECharacterStatType : uint8;
enum class ECCType : uint8;

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UTextureManager : public UObject
{
	GENERATED_BODY()
public:
	void InitializeTextures();

	UTexture2D* GetTexture(const FString& Key) const;
	UTexture2D* GetBuffTexture(ECharacterStatType StatType) const;
	UTexture2D* GetCCTexture(ECCType CCType) const;
private:
	void GetAllTexturesInFolder(const FString& FolderPath);

	TMap<FString, TSoftObjectPtr<UTexture2D>> textures_;
};
