// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleSubsystem.h"

void UBattleSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{

}

void UBattleSubsystem::Deinitialize()
{

}

void UBattleSubsystem::BattleStart() 
{
	IsBattle = true;
}

void UBattleSubsystem::BattleEnd()
{
	IsBattle = false;
}
