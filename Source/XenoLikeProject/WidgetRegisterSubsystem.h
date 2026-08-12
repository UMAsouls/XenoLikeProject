// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "WidgetRegisterSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class XENOLIKEPROJECT_API UWidgetRegisterSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void RegisterWidget(TSubclassOf<UUserWidget> WidgetClass, UUserWidget* Widget);

	UFUNCTION(BlueprintCallable)
	UUserWidget* GetWidget(TSubclassOf<UUserWidget> WidgetClass) const;

	UFUNCTION(BlueprintCallable)
	void RemoveWidget(TSubclassOf<UUserWidget> WidgetClass);

private:
	UPROPERTY()
	TMap<TSubclassOf<UUserWidget>, TObjectPtr<UUserWidget>> WidgetMap;
	
};
