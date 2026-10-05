// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "BattleSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBattleEnd);

/**
 * 
 */
UCLASS()
class XENOLIKEPROJECT_API UBattleSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	UFUNCTION(BlueprintCallable, Category = "BattleSubsystem")
	void BattleStart();

	UFUNCTION(BlueprintCallable, Category = "BattleSubsystem")
	void BattleWin();
	
	UFUNCTION(BlueprintCallable, Category = "BattleSubsystem")
	void BattleLose();
	
	UFUNCTION(BlueprintCallable, Category = "BattleSubsystem")
	void BattleEnd();
	
	UPROPERTY(BlueprintAssignable, Category = "BattleSubsystem")
	FOnBattleEnd OnBattleEnd;

private:
	
	bool IsBattle = false;
};
