// Fill out your copyright notice in the Description page of Project Settings.


#include "PartySubsystem.h"

void UPartySubsystem::Initialize(FSubsystemCollectionBase& Collection)
{

}

void UPartySubsystem::Deinitialize()
{

}

void UPartySubsystem::SetPartyMember(int Idx, int BeforeIdx, AActor* Member)
{
	if (Idx < 0 or Idx >= Party.Num()) return;

	TObjectPtr<AActor> ChangeMember = Party[Idx]; ;
	if (BeforeIdx >= 0 and BeforeIdx < Party.Num()) Party[BeforeIdx] = ChangeMember;

	Party[Idx] = TObjectPtr<AActor>(Member);
}

AActor* UPartySubsystem::GetLeader()
{
	return Leader;
}

void UPartySubsystem::UpdateLeader()
{
	if (Party[LeaderIdx] == Leader) return;

	Leader = Party[LeaderIdx];
	LeaderChangeDelegate.Broadcast(GetValid(Leader));
}

void UPartySubsystem::DrawWeapon()
{
	DrawWeaponDelegate.Broadcast();
}
