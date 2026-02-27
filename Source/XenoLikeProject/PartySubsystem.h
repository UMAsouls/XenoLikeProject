// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PartySubsystem.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDrawWeaponDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLeaderChangeDelegate, AActor*, Leader);
/**
 * 
 */
UCLASS()
class XENOLIKEPROJECT_API UPartySubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = "PartySubsystem|Delegate")
	FDrawWeaponDelegate DrawWeaponDelegate;

	UPROPERTY(BlueprintReadOnly, Category = "PartySubsystem|Delegate")
	FLeaderChangeDelegate LeaderChangeDelegate;

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	UFUNCTION(BlueprintCallable, Category="PartySubsystem")
	void DrawWeapon();

	UFUNCTION(BlueprintCallable, Category = "PartySubsystem|Party")
	void SetPartyMember(int Idx, int BeforeIdx, AActor* Member);

	UFUNCTION(BlueprintCallable, Category = "PartySubsystem|Party")
	AActor* GetLeader();

	void UpdateLeader();

private:
	const int LeaderIdx = 0;

	UPROPERTY(VisibleDefaultsOnly, Category =  "PartySubsystem|Party")
	TArray<TObjectPtr<AActor>> Party =
	{
		TObjectPtr<AActor>(), TObjectPtr<AActor>(), TObjectPtr<AActor>()
	};

	UPROPERTY(VisibleDefaultsOnly, Category = "PartySubsystem|Party")
	TObjectPtr<AActor> Leader;
};
