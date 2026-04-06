// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "EnemiesSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class XENOLIKEPROJECT_API UEnemiesSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category="EnemiesSubsystem")
	void AddEnemy(AActor* Enemy);

	UFUNCTION(BlueprintCallable, Category="EnemiesSubsystem")
	virtual void RemoveEnemy(AActor* Enemy);

protected:
	TArray<TObjectPtr<AActor>> Enemies;
	
};
