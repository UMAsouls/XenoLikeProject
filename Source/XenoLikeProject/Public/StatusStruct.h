// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StatusStruct.generated.h"


/**
 * 
 */
USTRUCT(BlueprintType)
struct FStatusStruct
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UCharacterDataAsset/Status")
	int HP = 100;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UCharacterDataAsset/Status")
	int Power = 100;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UCharacterDataAsset/Status")
	int Defence = 100;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UCharacterDataAsset/Status")
	int Speed = 100;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UCharacterDataAsset/Status")
	int HealPower = 100;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UCharacterDataAsset/Status",
			meta = (ClampMin = "0", ClampMax = "1.0"))
	float CriticalRate = 0.05;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UCharacterDataAsset/Status",
			meta = (ClampMin = "0", ClampMax = "1.0"))
	float GuardRate = 0.05;
};

