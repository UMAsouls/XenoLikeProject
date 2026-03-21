// Fill out your copyright notice in the Description page of Project Settings.


#include "GEEC_Attack.h"
#include "XenoCharacterAttributeSet.h"
#include "AbilitySystemComponent.h"

UGEEC_Attack::UGEEC_Attack()
{
	DEFINE_ATTRIBUTE_CAPTUREDEF(UXenoCharacterAttributeSet, Power, Source, true);
	DEFINE_ATTRIBUTE_CAPTUREDEF(UXenoCharacterAttributeSet, CriticalRate, Source, true);
	DEFINE_ATTRIBUTE_CAPTUREDEF(UXenoCharacterAttributeSet, IncomingDamage, Target, true);

	RelevantAttributesToCapture.Add(PowerDef);
	RelevantAttributesToCapture.Add(CriticalRateDef);
	RelevantAttributesToCapture.Add(IncomingDamageDef);
}

void UGEEC_Attack::Execute_Implementation(
	const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput
) const
{
	const FGameplayEffectSpec& spec = ExecutionParams.GetOwningSpec();

	float Power = 10.f;
	float CriticalRate = 0.3f;
	float IncomingDamage = 0.f;

	const FGameplayTagContainer* SourceTags = spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(PowerDef, EvaluationParameters, Power);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(CriticalRateDef, EvaluationParameters, CriticalRate);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(IncomingDamageDef, EvaluationParameters, IncomingDamage);

	FRandomStream rand;
	rand.GenerateNewSeed();

	float CriticalBonus = 1.f;
	if (CriticalRate >= rand.GetFraction()) {
		CriticalBonus = 1.3f;
	}

	float Damage = Power * ((1 + rand.GetFraction()) * 0.1f)  * CriticalBonus;

	//É_ÉÅÅ[ÉWÇâ^î¿
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(IncomingDamageProperty, EGameplayModOp::Additive,Damage));
}