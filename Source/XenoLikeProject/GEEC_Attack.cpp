// Fill out your copyright notice in the Description page of Project Settings.


#include "GEEC_Attack.h"
#include "XenoCharacterAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "Tests/AutomationEditorCommon.h"

UGEEC_Attack::UGEEC_Attack()
{
	DEFINE_ATTRIBUTE_CAPTUREDEF(UXenoCharacterAttributeSet, Power, Source, true);
	DEFINE_ATTRIBUTE_CAPTUREDEF(UXenoCharacterAttributeSet, CriticalRate, Source, true);
	DEFINE_ATTRIBUTE_CAPTUREDEF(UXenoCharacterAttributeSet, IncomingDamage, Target, true);
	
	DEFINE_ATTRIBUTE_CAPTUREDEF(UXenoCharacterAttributeSet, Defence, Target, true);
	DEFINE_ATTRIBUTE_CAPTUREDEF(UXenoCharacterAttributeSet, GuardRate, Target, true);
	DEFINE_ATTRIBUTE_CAPTUREDEF(UXenoCharacterAttributeSet, IncomingDamage, Target, true);
	DEFINE_ATTRIBUTE_CAPTUREDEF(UXenoCharacterAttributeSet, Miss, Source, true);
	DEFINE_ATTRIBUTE_CAPTUREDEF(UXenoCharacterAttributeSet, Hit, Source, true);

	RelevantAttributesToCapture.Add(PowerDef);
	RelevantAttributesToCapture.Add(CriticalRateDef);
	RelevantAttributesToCapture.Add(IncomingDamageDef);
	
	RelevantAttributesToCapture.Add(DefenceDef);
	RelevantAttributesToCapture.Add(GuardRateDef);
	RelevantAttributesToCapture.Add(IncomingDamageDef);
	RelevantAttributesToCapture.Add(MissDef);
	RelevantAttributesToCapture.Add(HitDef);
	
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
	
	float Defence = 10.f;
	float GuardRate = 0.3f;
	
	float ArtDamageBonus = 1.0f;

	const FGameplayTagContainer* SourceTags = spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;
	
	FGameplayTag ArtBonusTag = FGameplayTag::RequestGameplayTag(FName("Effect.Damage.ArtBonus"));
	ArtDamageBonus = spec.GetSetByCallerMagnitude(ArtBonusTag, false, 1.0f);

	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(PowerDef, EvaluationParameters, Power);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(CriticalRateDef, EvaluationParameters, CriticalRate);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(IncomingDamageDef, EvaluationParameters, IncomingDamage);
	
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DefenceDef, EvaluationParameters, Defence);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GuardRateDef, EvaluationParameters, GuardRate);

	FRandomStream rand;
	rand.GenerateNewSeed();

	float CriticalBonus = 1.f;
	if (CriticalRate >= rand.GetFraction()) {
		CriticalBonus = 1.3f;
	}
	
	//�K�[�h��guardRate�̊m���Ŕ���������
	float guard = 0.4f;
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
	
	float Damage = FMath::Max(Power-Defence, 1.0f) * FMath::Max(Power/30.f,1.0f)
		* (1 + rand.GetFraction()*0.5f)  
		* CriticalBonus * ArtDamageBonus 
		* guard * SkillReduce;

	//�_���[�W���^��
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(IncomingDamageProperty, EGameplayModOp::Override, Damage));
	
	// Hit通知用
	if (UAbilitySystemComponent* SourceASC =
		ExecutionParams.GetSourceAbilitySystemComponent())
	{
		if (const UXenoCharacterAttributeSet* SourceSet =
				SourceASC->GetSet<UXenoCharacterAttributeSet>())
		{
			SourceSet->OnAttackHit.Broadcast(Damage);
		}
	}
}