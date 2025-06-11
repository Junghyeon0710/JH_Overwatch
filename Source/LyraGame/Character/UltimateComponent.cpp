// Copyright 2025, Your Studio. All Rights Reserved.

#include "UltimateComponent.h"
#include "AbilitySystem/Attributes/UltimateSet.h"
#include "Character/UltimateComponent.h"
#include "AbilitySystem/LyraAbilitySystemComponent.h"
#include "Net/UnrealNetwork.h"

UUltimateComponent::UUltimateComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
	
	AbilitySystemComponent = nullptr;
	UltimateSet = nullptr;
}

void UUltimateComponent::InitializeWithAbilitySystem(ULyraAbilitySystemComponent* InASC)
{
	if (AbilitySystemComponent || !InASC)
	{
		return;
	}

	AbilitySystemComponent = InASC;
	UltimateSet = InASC->GetSet<UUltimateSet>();

	if (!UltimateSet)
	{
		UE_LOG(LogTemp, Error, TEXT("UUltimateComponent: UltimateSet is null for %s."), *GetNameSafe(GetOwner()));
		return;
	}

	UltimateSet->OnUltimateGaugeChanged.AddUObject(this, &ThisClass::HandleUltimateGaugeChanged);
	UltimateSet->OnMaxUltimateGaugeChanged.AddUObject(this, &ThisClass::HandleMaxUltimateGaugeChanged);

	// Broadcast current values
	OnUltimateGaugeChanged.Broadcast(this, UltimateSet->GetUltGauge(), UltimateSet->GetUltGauge(), nullptr);
	OnMaxUltimateGaugeChanged.Broadcast(this, UltimateSet->GetMaxUltGauge(), UltimateSet->GetMaxUltGauge(), nullptr);
}

void UUltimateComponent::UninitializeFromAbilitySystem()
{
	if (UltimateSet)
	{
		UltimateSet->OnUltimateGaugeChanged.RemoveAll(this);
		UltimateSet->OnMaxUltimateGaugeChanged.RemoveAll(this);
	}

	UltimateSet = nullptr;
	AbilitySystemComponent = nullptr;
}

float UUltimateComponent::GetUltimateGauge() const
{
	return UltimateSet ? UltimateSet->GetUltGauge() : 0.0f;
}

float UUltimateComponent::GetMaxUltimateGauge() const
{
	return UltimateSet ? UltimateSet->GetMaxUltGauge() : 0.0f;
}

float UUltimateComponent::GetUltimateGaugeNormalized() const
{
	if (!UltimateSet) return 0.0f;
	const float MaxGauge = UltimateSet->GetMaxUltGauge();
	return MaxGauge > 0.0f ? UltimateSet->GetUltGauge() / MaxGauge : 0.0f;
}

void UUltimateComponent::ConsumeUltimateGauge()
{
	if (!UltimateSet)
	{
		return;
	}
	const_cast<UUltimateSet*>(UltimateSet.Get())->SetUltGauge(0);
	//UltimateSet->SetUltGauge(0);
}

void UUltimateComponent::HandleUltimateGaugeChanged(AActor* Instigator, AActor* Causer, const FGameplayEffectSpec* Spec, float Delta, float OldValue, float NewValue)
{
	OnUltimateGaugeChanged.Broadcast(this, OldValue, NewValue, Instigator);

	// Optional: Trigger ultimate ability if gauge is full
	if (NewValue >= GetMaxUltimateGauge())
	{
		// TODO: Broadcast event or activate ultimate ability
	}
}

void UUltimateComponent::HandleMaxUltimateGaugeChanged(AActor* Instigator, AActor* Causer, const FGameplayEffectSpec* Spec, float Delta, float OldValue, float NewValue)
{
	OnMaxUltimateGaugeChanged.Broadcast(this, OldValue, NewValue, Instigator);
}