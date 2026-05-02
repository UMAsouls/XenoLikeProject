// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "GEEC_Damage.generated.h"

/**
 * 
 */
UCLASS()
class XENOLIKEPROJECT_API UGEEC_Damage : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

	UGEEC_Damage();

	DECLARE_ATTRIBUTE_CAPTUREDEF(Defence)
	DECLARE_ATTRIBUTE_CAPTUREDEF(GuardRate)
	DECLARE_ATTRIBUTE_CAPTUREDEF(IncomingDamage)
	DECLARE_ATTRIBUTE_CAPTUREDEF(Miss)
	DECLARE_ATTRIBUTE_CAPTUREDEF(Hit)

	virtual void Execute_Implementation(
		const FGameplayEffectCustomExecutionParameters& ExecutionParams, 
		OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput
	) const override;
	
};
