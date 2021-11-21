// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

USTRUCT(BlueprintType)
struct FOnHealthChangePayload
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health Change")
	float MaximumHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health Change")
	float NewHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health Change")
	float OldHealth;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChange, const FOnHealthChangePayload&, Payload);

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

	UFUNCTION()
	void Damage(float Damage);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

};