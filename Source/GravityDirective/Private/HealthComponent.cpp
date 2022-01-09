// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	Health = MaxHealth;
	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UHealthComponent::Damage(float Damage)
{
	float OldHealth = Health;
	Health -= Damage - Armor;

	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Lost Health!"));

	/*
	FOnHealthChangePayload eventPayload;
	eventPayload.MaximumHealth = MaxHealth;
	eventPayload.NewHealth = Health;
	eventPayload.OldHealth = OldHealth;

	OnHealthChange.Broadcast(eventPayload);
	*/
}

