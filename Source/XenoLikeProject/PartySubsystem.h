// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PartySubsystem.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDrawWeaponDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLeaderChangeDelegate, AActor*, Leader);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPartyExtincutionDelegate);
/**
 * 
 */
UCLASS()
class XENOLIKEPROJECT_API UPartySubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "PartySubsystem|Delegate")
	FDrawWeaponDelegate DrawWeaponDelegate;

	UPROPERTY(BlueprintAssignable, Category = "PartySubsystem|Delegate")
	FLeaderChangeDelegate LeaderChangeDelegate;

	UPROPERTY(BlueprintAssignable, Category = "PartySubsystem|Delegate")
	FPartyExtincutionDelegate PartyExtincutionDelegate;

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	UFUNCTION(BlueprintCallable, Category="PartySubsystem")
	void DrawWeapon();

	UFUNCTION(BlueprintCallable, Category = "PartySubsystem|Party")
	void SetPartyMember(int Idx, AActor* Member);

	UFUNCTION(BlueprintCallable, Category = "PartySubsystem|Party")
	void SwapPartyMember(int Idx1, int Idx2);

	UFUNCTION(BlueprintCallable, Category = "PartySubsystem|Party")
	AActor* GetPartyMember(int Idx);

	UFUNCTION(BlueprintCallable, Category = "PartySubsystem|Party")
	TArray<AActor*> GetPartyMembers();

	UFUNCTION(BlueprintCallable, Category = "PartySubsystem|Party")
	AActor* GetLeader();

	UFUNCTION(BlueprintCallable, Category = "PartySubsystem|Party")
	int GetPartyMemberCount();

	UFUNCTION(BlueprintCallable, Category = "PartySubsystem|Party")
	void AddDeath(AActor* Member);

	UFUNCTION(BlueprintCallable, Category = "PartySubsystem|Party")
	void SubtractDeath(AActor* Member);

	void UpdateLeader();
	void UpdatePartyMemberCount();

private:
	const int LeaderIdx = 0;

	UPROPERTY(VisibleDefaultsOnly, Category =  "PartySubsystem|Party")
	TArray<TObjectPtr<AActor>> Party =
	{
		TObjectPtr<AActor>(), TObjectPtr<AActor>(), TObjectPtr<AActor>()
	};

	UPROPERTY(VisibleDefaultsOnly, Category = "PartySubsystem|Party")
	TObjectPtr<AActor> Leader;

	int DeathCount = 0;
	int PartyMemberCount = 0;
	float PartyGage = 0;
	bool LeaderDeath = false;
};
