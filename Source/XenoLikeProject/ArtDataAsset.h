// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Engine/DataAsset.h"
#include "ArtDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class XENOLIKEPROJECT_API UArtDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UArtDataAsset() {}

	virtual FPrimaryAssetId GetPrimaryAssetId() const override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UArtDataAsset")
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UArtDataAsset")
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UArtDataAsset")
	TObjectPtr<UTexture> Icon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UArtDataAsset")
	float RecastSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UArtDataAsset")
	TSubclassOf<UGameplayAbility> ArtAbility;

};
