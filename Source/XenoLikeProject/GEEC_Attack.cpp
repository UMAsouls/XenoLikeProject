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

	RelevantAttributesToCapture.Add(PowerDef);
	RelevantAttributesToCapture.Add(CriticalRateDef);
	RelevantAttributesToCapture.Add(IncomingDamageDef);
	
	RelevantAttributesToCapture.Add(DefenceDef);
	RelevantAttributesToCapture.Add(GuardRateDef);
	RelevantAttributesToCapture.Add(IncomingDamageDef);
	
	AutoAttackKindTag = FGameplayTag::RequestGameplayTag("Attack.Kind.AutoAttack");
	ArtAttackKindTag = FGameplayTag::RequestGameplayTag("Attack.Kind.Art");
	
	ValidTransientAggregatorIdentifiers.AddTag(AutoAttackKindTag);
	ValidTransientAggregatorIdentifiers.AddTag(ArtAttackKindTag);
	
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
	
	TArray<FGameplayTag> OutputTags;
	
	// オートアタックかどうかをTransientVariableで評価
	float IsAutoAttack;
	ExecutionParams.AttemptCalculateTransientAggregatorMagnitude(AutoAttackKindTag,EvaluationParameters,IsAutoAttack);
	float IsArtAttack;
	ExecutionParams.AttemptCalculateTransientAggregatorMagnitude(ArtAttackKindTag,EvaluationParameters,IsArtAttack);
	
	if (IsArtAttack >= 1.f)
	{
		OutputTags.Add(ArtAttackKindTag);
	}
	else
	{
		OutputTags.Add(AutoAttackKindTag);
	}

	FRandomStream rand;
	rand.GenerateNewSeed();
	

	float CriticalBonus = 1.f;
	if (CriticalRate >= rand.GetFraction()) {
		CriticalBonus = 1.3f;
		OutputTags.Add(FGameplayTag::RequestGameplayTag(FName("Attack.Result.Critical")));
	}
	
	//�K�[�h��guardRate�̊m���Ŕ���������
	float guard = 1.f;
	if (GuardRate >= rand.GetFraction()) 
	{
		guard = 0.4f;
		OutputTags.Add(FGameplayTag::RequestGameplayTag(FName("Attack.Result.Guard")));
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
			if (AActor* TargetActor = ExecutionParams.GetTargetAbilitySystemComponent()->GetOwner())
			{
				SourceSet->OnAttackHit.Broadcast(Damage, FGameplayTagContainer::CreateFromArray(OutputTags), TargetActor);
			}
		}
	}
}