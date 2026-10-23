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
	ArtHealBonus = 1.f;
	
	AutoAttackCooldownTime = 0.5f;
	AutoAttackSpeed = 1.0f;
	
	TalentArtGage = 0.0f;
	TalentArtGageMax = 1.0f;

}

void UXenoCharacterAttributeSet::SetStatus(FStatusStruct Status)
{
	MaxHp = Status.HP;
	Hp = Status.HP;
	Power = Status.Power;
	Defence = Status.Defence;
	HealPower = Status.HealPower;
	Speed = Status.Speed;
	CriticalRate = Status.CriticalRate;
	GuardRate = Status.GuardRate;

}

void UXenoCharacterAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	TObjectPtr<AActor> TargetActor = Data.Target.GetAvatarActor();
	TObjectPtr<AActor> SourceActor = Data.EffectSpec.GetContext().GetOriginalInstigator();

	if (Data.EvaluatedData.Attribute == GetIncomingDamageAttribute()) 
	{
		
		float damage = GetIncomingDamage();
		SetHp(FMath::Clamp(GetHp()-damage, 0, GetMaxHp()));

		SetIncomingDamage(0);

		OnDamage.Broadcast(damage, SourceActor);
		OnHPUpdate.Broadcast(GetMaxHp(), GetHp());
		if (GetHp() <= 0.f) OnDeath.Broadcast();
	}
	
	if (Data.EvaluatedData.Attribute == GetIncomingHealAttribute())
	{
		float heal = GetIncomingHeal();
		SetHp(FMath::Clamp(GetHp()+heal, 0, GetMaxHp()));
		
		SetIncomingHeal(0);
		SetArtHealBonus(1);
		
		OnHPUpdate.Broadcast(GetMaxHp(), GetHp());
	}

	if(Data.EvaluatedData.Attribute == GetHpAttribute())
	{
		SetHp(FMath::Clamp(GetHp(), 0, GetMaxHp()));

		OnHPUpdate.Broadcast(GetMaxHp(), GetHp());
	}
	
	if (Data.EvaluatedData.Attribute == GetTalentArtGageAttribute())
	{
		SetTalentArtGage(FMath::Clamp(GetTalentArtGage(), 0, GetTalentArtGageMax()));
	}
}