// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "StateListener.h"
#include "GamePhaseStateEnum.h"
#include "GameStateEventSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class XENOLIKEPROJECT_API UGameStateEventSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

private:
	TMap<EGamePhaseStateEnum, TArray<TObjectPtr<AActor>>> Listeners;

public:
	UFUNCTION(BlueprintCallable)
	void Publish(EGamePhaseStateEnum StatePhaseEnum);

	UFUNCTION(BlueprintCallable)
	void Subscribe(EGamePhaseStateEnum StatePhaseEnum, AActor* actor);
	
};
