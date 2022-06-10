// Fill out your copyright notice in the Description page of Project Settings.


#include "StateGameMode.h"

// Sets default values
AStateGameMode::AStateGameMode()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AStateGameMode::BeginPlay()
{
	Super::BeginPlay();

	CurrentState = StartingState;

}

// Called every frame
void AStateGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentState->TickState(DeltaTime);
}

void AStateGameMode::SetState(UGameModeState* NewState)
{
	CurrentState->EndState();
	CurrentState = NewState;
	CurrentState->StartState();
}

