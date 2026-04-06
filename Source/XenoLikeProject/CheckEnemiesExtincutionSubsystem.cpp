// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckEnemiesExtincutionSubsystem.h"
#include "BattleSubsystem.h"

void UCheckEnemiesExtincutionSubsystem::RemoveEnemy(AActor* Enemy) 
{
	if (Enemies.Num() == 0) return;

	Enemies.RemoveSingle(TObjectPtr<AActor>(Enemy));
	if (Enemies.Num() == 0) {
		OnExtincution.Broadcast();
	}
}

