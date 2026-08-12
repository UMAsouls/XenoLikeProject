// Fill out your copyright notice in the Description page of Project Settings.


#include "GameStateEventSubsystem.h"
#include "StateListener.h"

void UGameStateEventSubsystem::Publish(EGamePhaseStateEnum StatePhaseEnum) 
{

	if (!Listeners.Contains(StatePhaseEnum)) {
		return;
	}

	for (TObjectPtr<AActor> actor : Listeners[StatePhaseEnum]) 
	{
		if(actor->Implements<UStateListener>()) 
		{
			IStateListener::Execute_StateChanged(actor, StatePhaseEnum);
		}
	}
}

void UGameStateEventSubsystem::Subscribe(EGamePhaseStateEnum StatePhaseEnum, AActor* actor)
{
	if (!Listeners.Contains(StatePhaseEnum)) {
		Listeners.Add(StatePhaseEnum);
	}
	Listeners[StatePhaseEnum].Add(actor);
}
