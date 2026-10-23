// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbilitySystemComponent.h"
#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "Public/StatusStruct.h"
#include "XenoCharacterAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FHPUpdateDelegate,float,MaxHP,float,HP);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDamageDelegate, float,Damage, AActor*,SourceActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttackMissDelegate,  FGameplayTagContainer, ResultTag);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAttackHitDelegate, float,Damage, FGameplayTagContainer, ResultTag);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FNoParamDelegate);
/**
 * 
 */
UCLASS()
class XENOLIKEPROJECT_API UXenoCharacterAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UXenoCharacterAttributeSet();
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)override;
	
	UFUNCTION(BlueprintCallable, Category="DataSet")
	virtual void SetStatus(FStatusStruct Status);

	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData Hp;
	ATTRIBUTE_ACCESSORS(UXenoCharacterAttributeSet, Hp)

	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData MaxHp;
	ATTRIBUTE_ACCESSORS(UXenoCharacterAttributeSet, MaxHp)

	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData Power;
	ATTRIBUTE_ACCESSORS(UXenoCharacterAttributeSet, Power)

	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData Defence;
	ATTRIBUTE_ACCESSORS(UXenoCharacterAttributeSet, Defence)

	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData HealPower;
	ATTRIBUTE_ACCESSORS(UXenoCharacterAttributeSet, HealPower)

	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData Speed;
	ATTRIBUTE_ACCESSORS(UXenoCharacterAttributeSet, Speed)

	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData CriticalRate;
	ATTRIBUTE_ACCESSORS(UXenoCharacterAttributeSet, CriticalRate)

	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData GuardRate;
	ATTRIBUTE_ACCESSORS(UXenoCharacterAttributeSet, GuardRate)

	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData TalentArtGage;
	ATTRIBUTE_ACCESSORS(UXenoCharacterAttributeSet, TalentArtGage)
	
	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData TalentArtGageMax;
	ATTRIBUTE_ACCESSORS(UXenoCharacterAttributeSet, TalentArtGageMax)
	
	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData AutoAttackSpeed;
	ATTRIBUTE_ACCESSORS(UXenoCharacterAttributeSet, AutoAttackSpeed)
	
	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData AutoAttackCooldownTime;
	ATTRIBUTE_ACCESSORS(UXenoCharacterAttributeSet, AutoAttackCooldownTime)
	
	//MetaAttribute
	UPROPERTY()
	FGameplayAttributeData IncomingDamage;
	ATTRIBUTE_ACCESSORS(UXenoCharacterAttributeSet, IncomingDamage)
	
	UPROPERTY()
	FGameplayAttributeData ArtHealBonus;
	ATTRIBUTE_ACCESSORS(UXenoCharacterAttributeSet, ArtHealBonus)
	
	UPROPERTY()
	FGameplayAttributeData IncomingHeal;
	ATTRIBUTE_ACCESSORS(UXenoCharacterAttributeSet, IncomingHeal)

	UPROPERTY(BlueprintAssignable)
	FHPUpdateDelegate OnHPUpdate;

	UPROPERTY(BlueprintAssignable)
	FDamageDelegate OnDamage;

	UPROPERTY(BlueprintAssignable)
	FNoParamDelegate OnDeath;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FAttackMissDelegate OnAttackMissed;

	UPROPERTY(BlueprintAssignable)
	FNoParamDelegate OnTalentArtRecastComplete;

	UPROPERTY(BlueprintAssignable)
	FAttackHitDelegate OnAttackHit;
};
