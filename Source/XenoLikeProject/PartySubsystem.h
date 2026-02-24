// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PartySubsystem.generated.h"


DECLARE_DYNAMIC_DELEGATE(FDrawWeaponDelegate);
/**
 * 
 */
UCLASS()
class XENOLIKEPROJECT_API UPartySubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	UFUNCTION(BlueprintCallable, Category="PartySubsystem")
	void DrawWeapon();

	UFUNCTION(BlueprintCallable, Category = "PartySubsystem")
	void SetDelegates
	(
		int Idx, FDrawWeaponDelegate DrawWeaponFunction
	);
private:
	TArray<FDrawWeaponDelegate> DrawWeaponDelegates
	{
		FDrawWeaponDelegate(),
		FDrawWeaponDelegate(),
		FDrawWeaponDelegate()
	};
};
