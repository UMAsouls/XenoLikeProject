// Fill out your copyright notice in the Description page of Project Settings.


#include "PartySubsystem.h"

void UPartySubsystem::Initialize(FSubsystemCollectionBase& Collection)
{

}

void UPartySubsystem::Deinitialize()
{

}

void UPartySubsystem::SetPartyMember(int Idx, AActor* Member)
{
	if (Idx < 0 or Idx >= Party.Num()) return;

	Party[Idx] = TObjectPtr<AActor>(Member);
	UpdateLeader();
}

void UPartySubsystem::SwapPartyMember(int Idx1, int Idx2)
{
	if (Idx1 < 0 or Idx1 >= Party.Num()) return;
	if (Idx2 < 0 or Idx2 >= Party.Num()) return;

	auto m = Party[Idx1];
	Party[Idx1] = Party[Idx2];
	Party[Idx2] = m;
}

AActor* UPartySubsystem::GetPartyMember(int Idx)
{
	return Party[Idx];
}

TArray<AActor*> UPartySubsystem::GetPartyMembers()
{
	return Party;
}

AActor* UPartySubsystem::GetLeader()
{
	return Leader;
}

int UPartySubsystem::GetPartyMemberCount()
{
	return PartyMemberCount;
}

void UPartySubsystem::UpdateLeader()
{
	if (Party[LeaderIdx] == Leader) return;

	Leader = Party[LeaderIdx];
	LeaderChangeDelegate.Broadcast(GetValid(Leader));
}

void UPartySubsystem::UpdatePartyMemberCount()
{
	int count = 0;
	for (const auto m : Party) {
		if (m != nullptr) count++;
	}
	PartyMemberCount = count;
}

void UPartySubsystem::DrawWeapon()
{
	DrawWeaponDelegate.Broadcast();
}

void UPartySubsystem::AddDeath(AActor* Member)
{
	DeathCount++;
	if (Leader == Member) LeaderDeath = true;

	if ((LeaderDeath && PartyGage < 1) || DeathCount >= PartyMemberCount)
	{
		PartyExtincutionDelegate.Broadcast();
	}
}

void UPartySubsystem::SubtractDeath(AActor* Member)
{
	DeathCount--;
	if (Leader == Member) LeaderDeath = false;
}
