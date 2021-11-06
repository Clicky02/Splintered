// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnHealthChange, float, MaximumHealth, float, NewHealth, float, OldHealth);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GRAVITYDIRECTIVE_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	// The maximum health this actor can have
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health")
	float MaxHealth = 100.0f;

	// How much health the actor currently has
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
	float Health = 100.0f;

	// The armor this actor has, which reduces damage taken
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health")
	float Armor = 0.0f;

public:	
	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnHealthChange OnHealthChange;

	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

};