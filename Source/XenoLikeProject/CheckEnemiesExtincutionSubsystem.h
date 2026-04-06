// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "EnemiesSubsystem.h"
#include "CheckEnemiesExtincutionSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEnemiesExtincutionDelegate);

/**
 * 敵が全滅したかどうか確認するためのクラス
 * とりあえず敵全滅=GameClearの処理を行うためのもの（クリア条件が違くなればいらなくなる）
 */
UCLASS()
class XENOLIKEPROJECT_API UCheckEnemiesExtincutionSubsystem : public UEnemiesSubsystem
{
	GENERATED_BODY()

public:
	void RemoveEnemy(AActor* Enemy) override;

	UPROPERTY(BlueprintAssignable)
	FEnemiesExtincutionDelegate OnExtincution;
	
};
