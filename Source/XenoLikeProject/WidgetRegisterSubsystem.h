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
class XENOLIKEPROJECT_API UWidgetRegisterSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	/*
	* @brief �w�肵���N���X�ɊY������widget��o�^����
	* 
	* @param WidgetClass �N���X
	* @param Widget �E�B�W�F�b�g�{��
	*/
	UFUNCTION(BlueprintCallable)
	void RegisterWidget(TSubclassOf<UUserWidget> WidgetClass, UUserWidget* Widget);

	/*
	* @brief �w�肵���N���X�œo�^���ꂽ�E�B�W�F�b�g���擾����	
	* ��ł��̃N���X�ɃL���X�g�ł���
	* @param WidgetClass �w��N���X
	*/
	UFUNCTION(BlueprintCallable)
	UUserWidget* GetWidget(TSubclassOf<UUserWidget> WidgetClass) const;
	
	/*
	* @brief �w�肵���N���X�œo�^���ꂽwidget���폜����
	* @param WidgetClass �w��N���X
	*/
	UFUNCTION(BlueprintCallable)
	void RemoveWidget(TSubclassOf<UUserWidget> WidgetClass);
	
	/*
	* @brief �S�Ă�widget�𖳂���(���Z�b�g����)
	*/
	UFUNCTION(BlueprintCallable)
	void ResetWidget();

private:
	UPROPERTY()
	TMap<TSubclassOf<UUserWidget>, TObjectPtr<UUserWidget>> WidgetMap;
	
};
