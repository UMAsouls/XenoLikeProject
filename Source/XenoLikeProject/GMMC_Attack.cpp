// Fill out your copyright notice in the Description page of Project Settings.


#include "GMMC_Attack.h"
#include "XenoCharacterAttributeSet.h"
#include "Math\RandomStream.h"

UGMMC_Attack::UGMMC_Attack() 
{
	PowerDef.AttributeToCapture = UXenoCharacterAttributeSet::GetPowerAttribute();
	PowerDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;

	CriticalRateDef.AttributeToCapture = UXenoCharacterAttributeSet::GetCriticalRateAttribute();
	CriticalRateDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;

	RelevantAttributesToCapture.Add(PowerDef);
	RelevantAttributesToCapture.Add(CriticalRateDef);
}

float UGMMC_Attack::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const  
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParams;
	EvaluateParams.SourceTags = SourceTags;
	EvaluateParams.TargetTags = TargetTags;

	float Power = 0.f;
	GetCapturedAttributeMagnitude(PowerDef, Spec, EvaluateParams, Power);

	float CriticalRate = 0.f;
	GetCapturedAttributeMagnitude(CriticalRateDef, Spec, EvaluateParams, CriticalRate);

	FRandomStream rand;
	rand.GenerateNewSeed();

	float CriticalBonus = 1.f;
	if (CriticalRate >= rand.GetFraction()) {
		CriticalBonus = 1.3f;
	}

	float Damage = Power * ((1 + rand.GetFraction()) * 0.5f) * 1.3f * CriticalBonus;

	return Damage;
}



