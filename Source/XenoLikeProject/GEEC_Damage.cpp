// Fill out your copyright notice in the Description page of Project Settings.


#include "GEEC_Damage.h"
#include "XenoCharacterAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "Math/RandomStream.h"

UGEEC_Damage::UGEEC_Damage() 
{
	DEFINE_ATTRIBUTE_CAPTUREDEF(UXenoCharacterAttributeSet, Defence, Target, true);
	DEFINE_ATTRIBUTE_CAPTUREDEF(UXenoCharacterAttributeSet, GuardRate, Target, true);
	DEFINE_ATTRIBUTE_CAPTUREDEF(UXenoCharacterAttributeSet, IncomingDamage, Target, true);
	DEFINE_ATTRIBUTE_CAPTUREDEF(UXenoCharacterAttributeSet, Miss, Source, true);
	DEFINE_ATTRIBUTE_CAPTUREDEF(UXenoCharacterAttributeSet, Hit, Source, true);

	RelevantAttributesToCapture.Add(DefenceDef);
	RelevantAttributesToCapture.Add(GuardRateDef);
	RelevantAttributesToCapture.Add(IncomingDamageDef);
	RelevantAttributesToCapture.Add(MissDef);
	RelevantAttributesToCapture.Add(HitDef);
}

void UGEEC_Damage::Execute_Implementation(
	const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput
) const 
{
	const FGameplayEffectSpec& spec = ExecutionParams.GetOwningSpec();

	float Defence = 10.f;
	float GuardRate = 0.3f;
	float IncomingDamage = 0.f;

	const FGameplayTagContainer* SourceTags = spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DefenceDef, EvaluationParameters, Defence);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GuardRateDef, EvaluationParameters, GuardRate);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(IncomingDamageDef, EvaluationParameters, IncomingDamage);

	//�K�[�h��guardRate�̊m���Ŕ���������
	float guard = 0.4f;
	FRandomStream rand;
	rand.GenerateNewSeed();
	if (GuardRate < rand.GetFraction()) 
	{
		guard = 1.f;
	}

	//�������
	//��ł����Ə���������
	if (false) 
	{
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(MissProperty, EGameplayModOp::Override, 1.f));
		return;
	}

	//�X�L���Ƃ��Ń_���[�W�����銄��
	//�������
	float SkillReduce = 1.0f;

	//�_���[�W�v�Z
	float TrueDamage = IncomingDamage * (1 - ((IncomingDamage / 10 - Defence) * 0.01)) * guard * SkillReduce;

	//�_���[�W���^��
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(IncomingDamageProperty, EGameplayModOp::Override, TrueDamage));
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(HitProperty, EGameplayModOp::Override, TrueDamage));
}
