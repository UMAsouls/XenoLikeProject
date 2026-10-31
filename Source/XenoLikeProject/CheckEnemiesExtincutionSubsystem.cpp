// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckEnemiesExtincutionSubsystem.h"
#include "BattleSubsystem.h"

void UCheckEnemiesExtincutionSubsystem::RemoveEnemy(AActor* Enemy, int Point) 
{
	if (Enemies.Num() == 0) return;

	Enemies.RemoveSingle(TObjectPtr<AActor>(Enemy));
	DefeatNum += Point;
	if (Enemies.Num() == 0 || DefeatNum >= ExtinctionEnemyNum)  {
		OnExtincution.Broadcast();
	}
}

void UCheckEnemiesExtincutionSubsystem::AddEnemy(AActor* Enemy) {
	Enemies.Add(TObjectPtr<AActor>(Enemy));
}

void UCheckEnemiesExtincutionSubsystem::SetExtinctionEnemyNum(int Num)
{
	ExtinctionEnemyNum = Num;
}
