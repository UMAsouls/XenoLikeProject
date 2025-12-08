// Fill out your copyright notice in the Description page of Project Settings.


#include "GEEC_Damage.h"
#include "XenoCharacterAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "Math\RandomStream.h"

UGEEC_Damage::UGEEC_Damage() 
{
	DEFINE_ATTRIBUTE_CAPTUREDEF(UXenoCharacterAttributeSet, Defence, Target, true);
	DEFINE_ATTRIBUTE_CAPTUREDEF(UXenoCharacterAttributeSet, GuardRate, Target, true);
	DEFINE_ATTRIBUTE_CAPTUREDEF(UXenoCharacterAttributeSet, Hp, Target, true);

	RelevantAttributesToCapture.Add(DefenceDef);
	RelevantAttributesToCapture.Add(GuardRateDef);
	RelevantAttributesToCapture.Add(HpDef);
}

void UGEEC_Damage::Execute_Implementation(
	const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput
) const 
{
	const FGameplayEffectSpec& spec = ExecutionParams.GetOwningSpec();

	float Damage = spec.GetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag("Effect.Damage"));
	float Defence = 10.f;
	float GuardRate = 0.3f;
	float Hp = 100.f;

	const FGameplayTagContainer* SourceTags = spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DefenceDef, EvaluationParameters, Defence);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GuardRateDef, EvaluationParameters, GuardRate);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(HpDef, EvaluationParameters, Hp);

	//ガードをguardRateの確率で発生させる
	float guard = 0.4f;
	FRandomStream rand;
	rand.GenerateNewSeed();
	if (GuardRate < rand.GetFraction()) {
		guard = 1.f;
	}

	//スキルとかでダメージが減る割合
	//実装後回し
	float SkillReduce = 1.0f;

	//ダメージ計算
	float TrueDamage = Damage * (1 - ((Damage / 10 - Defence) * 0.01)) * guard * SkillReduce;

	//ダメージを運搬
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(HpProperty, EGameplayModOp::Additive, -TrueDamage));
}