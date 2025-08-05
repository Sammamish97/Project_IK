/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 8.5.2025
Summary : Header file for Text Manager.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Internationalization/StringTable.h"
#include "Structs/CharacterData.h"
#include "TextManager.generated.h"

UCLASS(Blueprintable)
class PROJECT_IK_API UTextManager : public UObject
{
	GENERATED_BODY()
public:
	FText GetNameText(const FString& key) const;
	FText GetDetailText(const FString& key) const;
	FText GetStatusText(ECharacterStatType stat_type) const;
	
private:
	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UStringTable> name_table_;

	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UStringTable> detail_table_;

	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UStringTable> status_table_;
};
