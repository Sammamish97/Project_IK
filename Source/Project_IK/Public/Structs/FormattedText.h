/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 07.04.2025
Summary : Header file for a struct for formatted text.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "FormattedText.generated.h"

USTRUCT(BlueprintType)
struct FFormattedText
{
	GENERATED_BODY()

public:
	// Runtime method to evaluate
	FText Evaluate(const TArray<FText>& Args) const
	{
		FFormatOrderedArguments OrderedArgs;
		for (const FText& Arg : Args)
		{
			OrderedArgs.Add(Arg);
		}
		return FText::Format(FormatText, OrderedArgs);
	}

protected:


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText FormatText;
};