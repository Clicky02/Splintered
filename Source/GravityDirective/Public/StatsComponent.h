// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Stat.h"
#include "Components/ActorComponent.h"
#include "StatsComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GRAVITYDIRECTIVE_API UStatsComponent : public UActorComponent
{
	GENERATED_BODY()

protected:



public:

	// The maximum health this actor can have
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = "Stats")
	UStat* Health;

	// How much health the actor currently has
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = "Stats")
	UStat* Armor;

	// The armor this actor has, which reduces damage taken
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = "Stats")
	UStat* Mana;


public:	

	// Sets default values for this component's properties
	UStatsComponent();

protected:

	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
