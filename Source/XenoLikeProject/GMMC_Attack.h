// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "GMMC_Attack.generated.h"

/**
 * 
 */
UCLASS()
class XENOLIKEPROJECT_API UGMMC_Attack : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

	UGMMC_Attack();

	FGameplayEffectAttributeCaptureDefinition PowerDef;
	FGameplayEffectAttributeCaptureDefinition CriticalRateDef;

	float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
	
};
