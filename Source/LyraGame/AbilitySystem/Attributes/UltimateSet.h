// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/Attributes/LyraAttributeSet.h"
#include "UltimateSet.generated.h"

/**
 * 
 */
UCLASS()
class LYRAGAME_API UUltimateSet : public ULyraAttributeSet
{
	GENERATED_BODY()
	
public:

	UUltimateSet();

	ATTRIBUTE_ACCESSORS(UUltimateSet, UltGauge);
	ATTRIBUTE_ACCESSORS(UUltimateSet, MaxUltGauge);

	mutable FLyraAttributeEvent OnUltimateGaugeChanged;
	mutable FLyraAttributeEvent OnMaxUltimateGaugeChanged;

	float UltimateGaugeBeforeChange;

protected:

	UFUNCTION()
	void OnRep_UltGauge(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_MaxUltGauge(const FGameplayAttributeData& OldValue);


	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
private:

	// The base amount of damage to apply in the damage execution.
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_UltGauge, Category = "Lyra|Ult", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData UltGauge;

	// The base amount of healing to apply in the heal execution.
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxUltGauge, Category = "Lyra|Ult", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxUltGauge;
	
	
	
};
