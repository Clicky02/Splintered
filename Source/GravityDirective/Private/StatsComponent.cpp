// Fill out your copyright notice in the Description page of Project Settings.


#include "StatsComponent.h"

// Sets default values for this component's properties
UStatsComponent::UStatsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	Health = CreateDefaultSubobject<UStat>("Health");
	Health->Name = "Health";
	Health->IsActive = true;

	Armor = CreateDefaultSubobject<UStat>("Armor");
	Armor->Name = "Armor";

	Mana = CreateDefaultSubobject<UStat>("Mana");
	Mana->Name = "Mana";

	OutgoingDamageModifier = CreateDefaultSubobject<UStat>("OutgoingDamageModifier");
	OutgoingDamageModifier->Name = "OutgoingDamageModifier";
	OutgoingDamageModifier->Value = 1;

	IncomingDamageModifier = CreateDefaultSubobject<UStat>("IncomingDamageModifier");
	IncomingDamageModifier->Name = "IncomingDamageModifier";
	IncomingDamageModifier->Value = 1;
	// ...
}


// Called when the game starts
void UStatsComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UStatsComponent::Damage(float Damage)
{
	float DamageDealt = Damage - Armor->Value;

	if (DamageDealt < 0)
	{
		DamageDealt = 0;
	}

	Health->Add(-DamageDealt);
}
