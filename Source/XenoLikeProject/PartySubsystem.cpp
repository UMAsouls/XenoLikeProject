// Fill out your copyright notice in the Description page of Project Settings.


#include "PartySubsystem.h"

void UPartySubsystem::Initialize(FSubsystemCollectionBase& Collection)
{

}

void UPartySubsystem::Deinitialize()
{

}

void UPartySubsystem::SetPartyMember(int Idx, AXenoLikeProjectCharacter* Member)
{
	if (Idx < 0 or Idx >= Party.Num()) return;

	Party[Idx] = TObjectPtr<AXenoLikeProjectCharacter>(Member);
	UpdateLeader();
	UpdatePartyMemberCount();
}

void UPartySubsystem::SwapPartyMember(int Idx1, int Idx2)
{
	if (Idx1 < 0 or Idx1 >= Party.Num()) return;
	if (Idx2 < 0 or Idx2 >= Party.Num()) return;

	auto m = Party[Idx1];
	Party[Idx1] = Party[Idx2];
	Party[Idx2] = m;
	
	UpdateLeader();
	UpdatePartyMemberCount();
}

AXenoLikeProjectCharacter* UPartySubsystem::GetPartyMember(int Idx)
{
	return Party[Idx];
}

TArray<AXenoLikeProjectCharacter*> UPartySubsystem::GetPartyMembers()
{
	TArray<AXenoLikeProjectCharacter*> result;
	for (const auto m : Party) {
		if (IsValid(m)) result.Add(m);
	}
	
	return  result;
}
TArray<AXenoLikeProjectCharacter*> UPartySubsystem::GetAlivePartyMembers()
{
	TArray<AXenoLikeProjectCharacter*> result;
	for (const auto m : Party) {
		if (IsValid(m) && !m->IsDeath()) result.Add(m);
	}
	
	return  result;
}


AXenoLikeProjectCharacter* UPartySubsystem::GetLeader()
{
	return Leader;
}

int UPartySubsystem::GetPartyMemberCount()
{
	UpdatePartyMemberCount();
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
	auto array = GetPartyMembers();
	PartyMemberCount = array.Num();
}

void UPartySubsystem::DrawWeapon()
{
	DrawWeaponDelegate.Broadcast();
}

void UPartySubsystem::AddDeath(AXenoLikeProjectCharacter* Member)
{
	DeathCount++;
	if (Leader == Member)
	{
		LeaderDeath = true;
		LeaderDeathDelegate.Broadcast();
	}

	if ((LeaderDeath && PartyGage < OnePartyGage) || DeathCount >= PartyMemberCount)
	{
		PartyExtincutionDelegate.Broadcast();
	}
	
	MemberDeathDelegate.Broadcast();
}

void UPartySubsystem::SubtractDeath(AXenoLikeProjectCharacter* Member)
{
	DeathCount--;
	if (Leader == Member) LeaderDeath = false;
	MemberRebirthDelegate.Broadcast();
}

void UPartySubsystem::AddPartyGage(float Gage)
{
	PartyGage = FMath::Clamp(Gage+PartyGage, 0, 1);
}

bool UPartySubsystem::UsePartyGage(int count)
{
	if (PartyGage < count*OnePartyGage)
	{
		return  false;
	}
	else
	{
		PartyGage -= count*OnePartyGage;
		return true;
	}
}
