// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemiesSubsystem.h"
#include "BattleSubsystem.h"

void UEnemiesSubsystem::AddEnemy(AActor* Enemy) {
	Enemies.Add(TObjectPtr<AActor>(Enemy));
}

void UEnemiesSubsystem::RemoveEnemy(AActor* Enemy) {
	if (Enemies.Num() == 0) return;

	Enemies.RemoveSingle(TObjectPtr<AActor>(Enemy));
	if (Enemies.Num() == 0) {
		UBattleSubsystem* bs = GetGameInstance()->GetSubsystem<UBattleSubsystem>();
		if (bs) bs->BattleWin();
	}
}

