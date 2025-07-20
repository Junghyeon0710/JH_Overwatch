// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

#include "InputHoldDurationMessage.generated.h"


USTRUCT(BlueprintType)
struct FInputHoldDurationMessage
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category=Gameplay)
	TObjectPtr<AActor> Instigator;
	
	UPROPERTY(BlueprintReadWrite, Category=Gameplay)
	float Duration = 0;
};
