// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/GameFrameworkComponent.h"
#include "UltimateComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FUltimateGaugeChanged, UUltimateComponent*, Component, float, OldValue, float, NewValue, AActor*, Instigator);

class UUltimateSet;
struct FGameplayEffectSpec;

UCLASS(Blueprintable, Meta = (BlueprintSpawnableComponent))
class LYRAGAME_API UUltimateComponent : public UGameFrameworkComponent
{
	GENERATED_BODY()

public:
	UUltimateComponent(const FObjectInitializer& ObjectInitializer);

	// Returns the health component if one exists on the specified actor.
	UFUNCTION(BlueprintPure, Category = "Lyra|Health")
	static UUltimateComponent* FindUltimateComponent(const AActor* Actor) { return (Actor ? Actor->FindComponentByClass<UUltimateComponent>() : nullptr); }

	UFUNCTION(BlueprintCallable)
	void InitializeWithAbilitySystem(ULyraAbilitySystemComponent* InASC);

	UFUNCTION(BlueprintCallable)
	void UninitializeFromAbilitySystem();

	UFUNCTION(BlueprintCallable)
	float GetUltimateGauge() const;

	UFUNCTION(BlueprintCallable)
	float GetMaxUltimateGauge() const;

	UFUNCTION(BlueprintCallable)
	float GetUltimateGaugeNormalized() const;

	UFUNCTION(BlueprintCallable)
	void ConsumeUltimateGauge();



public:
	UPROPERTY(BlueprintAssignable)
	FUltimateGaugeChanged OnUltimateGaugeChanged;

	UPROPERTY(BlueprintAssignable)
	FUltimateGaugeChanged OnMaxUltimateGaugeChanged;

protected:
	UPROPERTY()
	TObjectPtr<ULyraAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<const UUltimateSet> UltimateSet;

	virtual void HandleUltimateGaugeChanged(AActor* Instigator, AActor* Causer, const FGameplayEffectSpec* Spec, float Delta, float OldValue, float NewValue);
	virtual void HandleMaxUltimateGaugeChanged(AActor* Instigator, AActor* Causer, const FGameplayEffectSpec* Spec, float Delta, float OldValue, float NewValue);
};