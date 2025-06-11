// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Attributes/UltimateSet.h"

#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"


UUltimateSet::UUltimateSet()
	: UltGauge(0),
	  MaxUltGauge(100)
{
	
}

void UUltimateSet::OnRep_UltGauge(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UUltimateSet, UltGauge, OldValue);
	

}

void UUltimateSet::OnRep_MaxUltGauge(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UUltimateSet, MaxUltGauge, OldValue);
	
}

void UUltimateSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UUltimateSet, UltGauge, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UUltimateSet, MaxUltGauge, COND_None, REPNOTIFY_Always);
}

void UUltimateSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetUltGaugeAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxUltGauge());
		UltimateGaugeBeforeChange = GetUltGauge();
	}
	else if (Attribute == GetMaxUltGaugeAttribute())
	{
		NewValue = FMath::Max(NewValue, 1.0f); // 최소 1 이상
	}

	
}

void UUltimateSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	AActor* Instigator = Data.EffectSpec.GetEffectContext().GetOriginalInstigator();
	AActor* Causer = Data.EffectSpec.GetEffectContext().GetEffectCauser();

	if (Data.EvaluatedData.Attribute == GetUltGaugeAttribute())
	{
		float ClampedGauge =  FMath::Clamp(Data.EvaluatedData.Magnitude, 0.0f, GetMaxUltGauge());
	//	SetUltGauge(ClampedGauge + GetUltGauge());
		
		OnUltimateGaugeChanged.Broadcast(Instigator, Causer, &Data.EffectSpec, Data.EvaluatedData.Magnitude, UltimateGaugeBeforeChange, GetUltGauge());
	}
}