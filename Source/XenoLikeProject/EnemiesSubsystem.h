// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "EnemiesSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class XENOLIKEPROJECT_API UEnemiesSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category="EnemiesSubsystem")
	void AddEnemy(AActor* Enemy);

	UFUNCTION(BlueprintCallable, Category="EnemiesSubsystem")
	virtual void RemoveEnemy(AActor* Enemy);
	
	/*
	 * @brief 敵が倒される時に呼び出される
	 * これによって最後の敵が倒されると、戦闘終了となる
	 */
	UFUNCTION(BlueprintCallable, Category="EnemiesSubsystem")
	virtual void DefeatEnemy(AActor* Enemy);
	
	/*
	 * @brief 敵が追いかけるのをやめたとき（プレイヤー逃走成功時）に呼び出される
	 */
	UFUNCTION(BlueprintCallable, Category="EnemiesSubsystem")
	virtual void EscapeEnemy(AActor* Enemy);

protected:
	TArray<TObjectPtr<AActor>> Enemies;
	
	int DefeatCount = 0;
	
};
