// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/LyraCameraMode.h"
#include "LyraCameraModeCharacterSelect.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class CHARACTERSELECTRUNTIME_API ULyraCameraModeCharacterSelect : public ULyraCameraMode
{
	GENERATED_BODY()
	
public:
	ULyraCameraModeCharacterSelect();

protected:
	virtual void UpdateView(float DeltaTime) override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character Select Camera")
	float CameraDistance;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character Select Camera")
	float TargetHeightOffset = 80.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character Select Camera")
	float LookDownAngleOffset = 10.f;
	
};
