/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 11.10.2024
Summary : Source file for managing characters data.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Managers/CharacterDataManager.h"
#include "Characters/Unit.h"
#include "Structs/CharacterData.h"

UCharacterDataManager::UCharacterDataManager()
	: Super::UObject()
{
	FString character_data_path = TEXT("/Script/Engine.DataTable'/Game/Resources/IK_Character_Data.IK_Character_Data'");
	static ConstructorHelpers::FObjectFinder<UDataTable> dt_character_data(*character_data_path);
	if (dt_character_data.Succeeded() == false)
	{
		UE_LOG(LogTemp, Error, TEXT("GameInstance has failed to load a game file data (IK_Character_Data)"));
	}
	character_table = dt_character_data.Object;
}

FCharacterData* UCharacterDataManager::GetCharacterData(EHeroType hero_type) const
{
	if (character_table)
	{
		return character_table->FindRow<FCharacterData>(*EnumToString(hero_type), TEXT(""));
	}
	return nullptr;
}

FString UCharacterDataManager::EnumToString(EHeroType char_type) const
{
	FString char_string;
	switch (char_type)
	{
	case EHeroType::Hero1:
		char_string = TEXT("1");
		break;
	case EHeroType::Hero2:
		char_string = TEXT("2");
		break;
	case EHeroType::Hero3:
		char_string = TEXT("3");
		break;
	case EHeroType::Hero4:
		char_string = TEXT("4");
		break;
	default:
		char_string = TEXT("1");
		break;
	}
	return char_string;
}