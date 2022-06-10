// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModeState.h"

void UGameModeState::Init(FTickSignature TickFunc, FOnStartSignature OnStartFunc, FOnEndSignature OnEndFunc)
{
	Tick = TickFunc;
	OnStart = OnStartFunc;
	OnEnd = OnEndFunc;
}

void UGameModeState::StartState()
{
	bIsActive = true;
	OnStart.ExecuteIfBound();
}

void UGameModeState::TickState(float DeltaTime)
{
	if (bIsActive)
	{
		Tick.ExecuteIfBound(DeltaTime);
	}
}

void UGameModeState::EndState()
{
	bIsActive = false;
	OnEnd.ExecuteIfBound();
}

UGameModeState* UGameModeState::CreateGameModeSate(FTickSignature TickFunc, FOnStartSignature OnStartFunc, FOnEndSignature OnEndFunc)
{
	UGameModeState* NewState = NewObject<UGameModeState>();
	//NewState->Init(TickFunc, OnStartFunc, OnEndFunc);
	return NewState;
}