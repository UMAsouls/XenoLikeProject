// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbilitySystemComponent.h"
#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "XenoCharacterAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


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


};
