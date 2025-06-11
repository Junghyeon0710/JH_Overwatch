// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GameplayEffect/GE_UltimateGain.h"

#include "AbilitySystem/Attributes/UltimateSet.h"


UGE_UltimateGain::UGE_UltimateGain()
{
	DurationPolicy = EGameplayEffectDurationType::Instant;

	// 궁극기 게이지 Attribute 설정
	FGameplayModifierInfo Modifier;
	Modifier.Attribute = UUltimateSet::GetUltGaugeAttribute();
	Modifier.ModifierOp = EGameplayModOp::Additive;
	

	// SetByCaller 태그로 수치 전달받음
	static FGameplayTag GainTag = FGameplayTag::RequestGameplayTag(FName("SetByCaller.Damage"));
	FSetByCallerFloat SetByCaller;
	SetByCaller.DataTag = GainTag;

	Modifier.ModifierMagnitude = SetByCaller;

	Modifiers.Add(Modifier);
}
