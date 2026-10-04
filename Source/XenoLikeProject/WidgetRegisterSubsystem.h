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
	/*
	* @brief 指定したクラスに該当するwidgetを登録する
	* 
	* @param WidgetClass クラス
	* @param Widget ウィジェット本体
	*/
	UFUNCTION(BlueprintCallable)
	void RegisterWidget(TSubclassOf<UUserWidget> WidgetClass, UUserWidget* Widget);

	/*
	* @brief 指定したクラスで登録されたウィジェットを取得する	
	* 後でそのクラスにキャストできる
	* @param WidgetClass 指定クラス
	*/
	UFUNCTION(BlueprintCallable)
	UUserWidget* GetWidget(TSubclassOf<UUserWidget> WidgetClass) const;
	
	/*
	* @brief 指定したクラスで登録されたwidgetを削除する
	* @param WidgetClass 指定クラス
	*/
	UFUNCTION(BlueprintCallable)
	void RemoveWidget(TSubclassOf<UUserWidget> WidgetClass);
	
	/*
	* @brief 全てのwidgetを無くす(リセットする)
	*/
	UFUNCTION(BlueprintCallable)
	void ResetWidget();

private:
	UPROPERTY()
	TMap<TSubclassOf<UUserWidget>, TObjectPtr<UUserWidget>> WidgetMap;
	
};
