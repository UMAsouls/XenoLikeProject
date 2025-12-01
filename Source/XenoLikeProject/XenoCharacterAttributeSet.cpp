// Fill out your copyright notice in the Description page of Project Settings.

#include "XenoCharacterAttributeSet.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"
#include "Kismet/GameplayStatics.h"

UXenoCharacterAttributeSet::UXenoCharacterAttributeSet() 
{
	Hp = 100.f;
	MaxHp = 100.f;
	Power = 100.f;
	Defence = 100.f;
	HealPower = 100.f;
	Speed = 100.f;
	CriticalRate = 0.f;
	GuardRate = 0.f;

}

void UXenoCharacterAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	TObjectPtr<AActor> TargetActor = Data.Target.GetAvatarActor();
	TObjectPtr<AActor> SourceActor = Data.EffectSpec.GetContext().GetOriginalInstigator();

	if(Data.EvaluatedData.Attribute == GetHpAttribute())
	{
		SetHp(FMath::Clamp(GetHp(), 0, GetMaxHp()));
	}
}