// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "GEEC_Heal.generated.h"

/**
 * 
 */
UCLASS()
class XENOLIKEPROJECT_API UGEEC_Heal : public UGameplayEffectExecutionCalculation
{
public:
	GENERATED_BODY()
	
	UGEEC_Heal();
	
	DECLARE_ATTRIBUTE_CAPTUREDEF(HealPower);
	DECLARE_ATTRIBUTE_CAPTUREDEF(IncomingHeal);
	
	virtual void Execute_Implementation(
		const FGameplayEffectCustomExecutionParameters& ExecutionParams,
		OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput
	) const override;
};
