// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GamePhaseStateEnum.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EGamePhaseStateEnum : uint8
{
	Normal,
	LockOn,
	DrawWeapon,
	Battle,
	ChainAttack,
	Escape,
	GameClear,
	GameOver
};
