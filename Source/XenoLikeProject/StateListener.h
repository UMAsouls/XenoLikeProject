// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GamePhaseStateEnum.h"
#include "StateListener.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UStateListener : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class XENOLIKEPROJECT_API IStateListener
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void StateChanged(EGamePhaseStateEnum StateEnum);
};
