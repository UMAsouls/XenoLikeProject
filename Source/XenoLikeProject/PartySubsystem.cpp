// Fill out your copyright notice in the Description page of Project Settings.


#include "PartySubsystem.h"

void UPartySubsystem::Initialize(FSubsystemCollectionBase& Collection)
{

}

void UPartySubsystem::Deinitialize()
{

}

void UPartySubsystem::DrawWeapon()
{
	for (const auto& delegate : DrawWeaponDelegates)
	{
		delegate.ExecuteIfBound();
	}
}

void UPartySubsystem::SetDelegates
(
	int Idx, FDrawWeaponDelegate DrawWeaponFunction
)
{
	DrawWeaponDelegates[Idx] = DrawWeaponFunction;
}
