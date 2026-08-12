// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetRegisterSubsystem.h"

void UWidgetRegisterSubsystem::RegisterWidget(TSubclassOf<UUserWidget> WidgetClass, UUserWidget* Widget)
{
	WidgetMap.Add(WidgetClass, Widget);
}

UUserWidget* UWidgetRegisterSubsystem::GetWidget(TSubclassOf<UUserWidget> WidgetClass) const
{

    if (const TObjectPtr<UUserWidget>* Found = WidgetMap.Find(WidgetClass))
    {
        return Found->Get();
    }

    return nullptr;
}

void UWidgetRegisterSubsystem::RemoveWidget(TSubclassOf<UUserWidget> WidgetClass)
{
    if (const TObjectPtr<UUserWidget>* Found = WidgetMap.Find(WidgetClass)) 
    {
        WidgetMap[WidgetClass]->RemoveFromParent();
        WidgetMap[WidgetClass] = nullptr;
    }
}

