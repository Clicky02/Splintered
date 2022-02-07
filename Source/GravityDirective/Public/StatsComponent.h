// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Stat.h"
#include "Components/ActorComponent.h"
#include "StatusEffect.h"
#include "StatType.h"
#include "StatsComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GRAVITYDIRECTIVE_API UStatsComponent : public UActorComponent
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadWrite)
	TArray<UStatusEffect*> ActiveStatusEffects;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = "Stats")
	UStat* Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = "Stats")
	UStat* Armor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = "Stats")
	UStat* Mana;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = "Stats")
	UStat* OutgoingDamageModifier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = "Stats")
	UStat* IncomingDamageModifier;


public:	

	// Sets default values for this component's properties
	UStatsComponent();

protected:

	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Stats")
	UStat* GetStat(EStatVariant StatVariant);

public:	

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Stats")
	virtual void Damage(float Damage);

	UFUNCTION(BlueprintCallable, Category = "Stats")
	void ApplyStatusEffect(TSubclassOf<UStatusEffect> StatusEffect, float StartStacks = 1, float StartDuration = -1);

	UFUNCTION(BlueprintCallable, Category = "Stats")
	void RemoveStatusEffect(TSubclassOf<UStatusEffect> StatusEffect, float NumStacks = -1);

	UFUNCTION(BlueprintCallable, Category = "Stats")
	UStatusEffect* GetStatusEffect(TSubclassOf<UStatusEffect> StatusEffect);

	UFUNCTION(BlueprintCallable, Category = "Stats")
	int32 ApplyStatModifier(const FStatModifier& NewModifier);

	UFUNCTION(BlueprintCallable, Category = "Stats")
	UPARAM(ref) FStatModifier& GetStatModifier(EStatVariant StatVariant, int32 Id);
};
