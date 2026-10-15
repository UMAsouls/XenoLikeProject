// Fill out your copyright notice in the Description page of Project Settings.


#include "GEEC_Heal.h"

#include "XenoCharacterAttributeSet.h"

UGEEC_Heal::UGEEC_Heal()
{
	DEFINE_ATTRIBUTE_CAPTUREDEF(UXenoCharacterAttributeSet, HealPower, Source, true);
	DEFINE_ATTRIBUTE_CAPTUREDEF(UXenoCharacterAttributeSet, IncomingHeal, Target, true);
	
	RelevantAttributesToCapture.Add(HealPowerDef);
	RelevantAttributesToCapture.Add(IncomingHealDef);
}

void UGEEC_Heal::Execute_Implementation(
	const FGameplayEffectCustomExecutionParameters& ExecutionParams, 
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput
	) const
{
	const FGameplayEffectSpec& spec = ExecutionParams.GetOwningSpec();

	float HealPower = 10.f;
	float IncomingHeal = 0.f;

	const FGameplayTagContainer* SourceTags = spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;
	
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(HealPowerDef, EvaluationParameters, HealPower);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(IncomingHealDef, EvaluationParameters, IncomingHeal);
	
	FRandomStream rand;
	rand.GenerateNewSeed();
	
	float heal = HealPower * (1 + rand.GetFraction() * 0.1f);
	
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(IncomingHealProperty, EGameplayModOp::Additive, heal));
}

