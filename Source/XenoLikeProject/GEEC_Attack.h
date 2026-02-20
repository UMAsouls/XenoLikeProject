// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "GEEC_Attack.generated.h"

/**
 * 
 */
UCLASS()
class XENOLIKEPROJECT_API UGEEC_Attack : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

	UGEEC_Attack();

	DECLARE_ATTRIBUTE_CAPTUREDEF(Power)
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalRate)
	DECLARE_ATTRIBUTE_CAPTUREDEF(IncomingDamage)

	virtual void Execute_Implementation(
		const FGameplayEffectCustomExecutionParameters& ExecutionParams,
		OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput
	) const override;
	
};
