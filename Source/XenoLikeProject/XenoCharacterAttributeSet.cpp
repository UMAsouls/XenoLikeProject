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
	ArtDamageBonus = 1.f;
	DamageAdjuster = 1.f;

}

void UXenoCharacterAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	TObjectPtr<AActor> TargetActor = Data.Target.GetAvatarActor();
	TObjectPtr<AActor> SourceActor = Data.EffectSpec.GetContext().GetOriginalInstigator();

	if (Data.EvaluatedData.Attribute == GetMissAttribute()) 
	{
		SetMiss(0);
		OnAttackMissed.Broadcast();
	}

	if (Data.EvaluatedData.Attribute == GetHitAttribute())
	{
		OnAttackHit.Broadcast(GetHit());
		SetHit(0);
	}

	if (Data.EvaluatedData.Attribute == GetIncomingDamageAttribute()) 
	{
		float damage = GetIncomingDamage()*GetDamageAdjuster()*GetArtDamageBonus();
		SetHp(FMath::Clamp(GetHp()-damage, 0, GetMaxHp()));

		SetIncomingDamage(0);
		SetDamageAdjuster(1);
		SetArtDamageBonus(1);

		OnDamage.Broadcast(damage);
		OnHPUpdate.Broadcast(GetMaxHp(), GetHp());
		if (GetHp() <= 0.f) OnDeath.Broadcast();
	}

	if(Data.EvaluatedData.Attribute == GetHpAttribute())
	{
		SetHp(FMath::Clamp(GetHp(), 0, GetMaxHp()));

		OnHPUpdate.Broadcast(GetMaxHp(), GetHp());
	}
}