// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "EnemiesSubsystem.h"
#include "CheckEnemiesExtincutionSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEnemiesExtincutionDelegate);

/**
 * �G���S�ł������ǂ����m�F���邽�߂̃N���X
 * �Ƃ肠�����G�S��=GameClear�̏������s�����߂̂��́i�N���A�������Ⴍ�Ȃ�΂���Ȃ��Ȃ�j
 */
UCLASS()
class XENOLIKEPROJECT_API UCheckEnemiesExtincutionSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void AddEnemy(AActor* Enemy);
	
	UFUNCTION(BlueprintCallable)
	void RemoveEnemy(AActor* Enemy);

	UPROPERTY(BlueprintAssignable)
	FEnemiesExtincutionDelegate OnExtincution;
	
	TArray<TObjectPtr<AActor>> Enemies;
	
};
