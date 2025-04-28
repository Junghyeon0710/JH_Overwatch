// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/LyraActivatableWidget.h"
#include "JHCreditScreen.generated.h"

/**
 * 
 */
UCLASS()
class LYRAGAME_API UJHCreditScreen : public ULyraActivatableWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeOnInitialized() override;

	void HandleBackAction();
	UFUNCTION(BlueprintImplementableEvent)
	void HandleSlowAction();
	UFUNCTION(BlueprintImplementableEvent)
	void HandleFastAction();
	
protected:

	UPROPERTY(EditDefaultsOnly)
	FDataTableRowHandle BackInputActionData;

	UPROPERTY(EditDefaultsOnly)
	FDataTableRowHandle SlowInputActionData;

	UPROPERTY(EditDefaultsOnly)
	FDataTableRowHandle FastInputActionData;

	FUIActionBindingHandle BackHandle;
	FUIActionBindingHandle SlowHandle;
	FUIActionBindingHandle FastHandle;
};
