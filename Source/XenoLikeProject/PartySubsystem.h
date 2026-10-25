// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XenoLikeProjectCharacter.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PartySubsystem.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDrawWeaponDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUnEquipDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLeaderChangeDelegate, AXenoLikeProjectCharacter*, Leader);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPartyExtincutionDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLeaderDeathDelegate);
/**
 * 
 */
UCLASS()
class XENOLIKEPROJECT_API UPartySubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "PartySubsystem|Delegate")
	FDrawWeaponDelegate DrawWeaponDelegate;
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "PartySubsystem|Delegate")
	FUnEquipDelegate UnEquipDelegate;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "PartySubsystem|Delegate")
	FLeaderChangeDelegate LeaderChangeDelegate;
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "PartySubsystem|Delegate")
	FLeaderDeathDelegate LeaderDeathDelegate;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "PartySubsystem|Delegate")
	FPartyExtincutionDelegate PartyExtincutionDelegate;

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	UFUNCTION(BlueprintCallable, Category="PartySubsystem")
	void DrawWeapon();

	UFUNCTION(BlueprintCallable, Category = "PartySubsystem|Party")
	void SetPartyMember(int Idx, AXenoLikeProjectCharacter* Member);

	UFUNCTION(BlueprintCallable, Category = "PartySubsystem|Party")
	void SwapPartyMember(int Idx1, int Idx2);

	UFUNCTION(BlueprintCallable, Category = "PartySubsystem|Party")
	AXenoLikeProjectCharacter* GetPartyMember(int Idx);

	UFUNCTION(BlueprintCallable, Category = "PartySubsystem|Party")
	TArray<AXenoLikeProjectCharacter*> GetPartyMembers();

	UFUNCTION(BlueprintCallable, Category = "PartySubsystem|Party")
	AXenoLikeProjectCharacter* GetLeader();

	UFUNCTION(BlueprintCallable, Category = "PartySubsystem|Party")
	int GetPartyMemberCount();

	UFUNCTION(BlueprintCallable, Category = "PartySubsystem|Party")
	void AddDeath(AXenoLikeProjectCharacter* Member);

	UFUNCTION(BlueprintCallable, Category = "PartySubsystem|Party")
	void SubtractDeath(AXenoLikeProjectCharacter* Member);

	void UpdateLeader();
	void UpdatePartyMemberCount();
	
	UPROPERTY(BlueprintReadOnly, Category = "PartySubsystem|Gage")
	float PartyGage = 0;
	
	UPROPERTY(BlueprintReadOnly, Category = "PartySubsystem|Gage")
	float OnePartyGage = 0.33f;
	
	UFUNCTION(BlueprintCallable, Category = "PartySubsystem|Gage")
	void AddPartyGage(float Gage);
	
	// 1パーティゲージ分を消費
	// 消費できなかったらfalse
	UFUNCTION(BlueprintCallable, Category = "PartySubsystem|Gage")
	bool UsePartyGage(int count);

private:
	const int LeaderIdx = 0;
	

	UPROPERTY(VisibleDefaultsOnly, Category =  "PartySubsystem|Party")
	TArray<TObjectPtr<AXenoLikeProjectCharacter>> Party =
	{
		TObjectPtr<AXenoLikeProjectCharacter>(), 
		TObjectPtr<AXenoLikeProjectCharacter>(), 
		TObjectPtr<AXenoLikeProjectCharacter>()
	};

	UPROPERTY(VisibleDefaultsOnly, Category = "PartySubsystem|Party")
	TObjectPtr<AXenoLikeProjectCharacter> Leader;

	int DeathCount = 0;
	int PartyMemberCount = 0;
	bool LeaderDeath = false;
};
