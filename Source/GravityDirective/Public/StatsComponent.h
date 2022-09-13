// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Stat.h"
#include "Components/ActorComponent.h"
#include "StatusEffect.h"
#include "StatType.h"
#include "StatsComponent.generated.h"

USTRUCT(BlueprintType)
struct FOnDeathPayload
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStatsComponent* StatsComponent;
};

USTRUCT(BlueprintType)
struct FOnStatsInitPayload
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStatsComponent* StatsComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Level;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDeath, const FOnDeathPayload&, Payload);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStatsInit, const FOnStatsInitPayload&, Payload);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GRAVITYDIRECTIVE_API UStatsComponent : public UActorComponent
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadWrite)
	TArray<UStatusEffect*> ActiveStatusEffects;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32 Team = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32 Level = -1;

	static TArray<AActor*> StatActors;

	bool bIsAlive = true;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	bool bShouldTickWhenDead = false;

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

	UPROPERTY(BlueprintAssignable)
	FOnDeath OnDeath;

	UPROPERTY(BlueprintCallable)
	FOnStatsInit OnStatsInit;


public:	

	// Sets default values for this component's properties
	UStatsComponent();

protected:

	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION(BlueprintCallable, Category = "Stats")
	UStat* GetStat(EStatVariant StatVariant);

public:	

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Stats")
	static TArray<AActor*> GetStatActors();

	UFUNCTION(BlueprintCallable, Category = "Stats")
	void Init(int32 initialLevel, int32 initialTeam = 0);

	UFUNCTION(BlueprintCallable, Category = "Stats")
	int32 GetTeam();

	UFUNCTION(BlueprintCallable, Category = "Stats")
	void SetTeam(int32 NewTeam);

	UFUNCTION(BlueprintCallable, Category = "Stats")
	virtual void Damage(float Damage, UStatsComponent* OtherStats = nullptr);

	UFUNCTION(BlueprintCallable, Category = "Stats")
	bool IsAlive();

	UFUNCTION(BlueprintCallable, Category = "Stats")
	bool UseMana(float BaseManaCost, bool Force = false);

	UFUNCTION(BlueprintCallable, Category = "Stats")
	bool HasEnoughMana(float BaseManaCost);

	UFUNCTION(BlueprintCallable, Category = "Stats")
	float GetRealManaCost(float BaseManaCost);

	UFUNCTION(BlueprintCallable, Category = "Stats")
	bool Kill();

	UFUNCTION(BlueprintCallable, Category = "Stats")
	void ApplyStatusEffect(TSubclassOf<UStatusEffect> StatusEffect, float StartStacks = 1, float StartDuration = -1);

	UFUNCTION(BlueprintCallable, Category = "Stats")
	void RemoveStatusEffect(TSubclassOf<UStatusEffect> StatusEffect, float NumStacks = -1);

	UFUNCTION(BlueprintCallable, Category = "Stats")
	void RemoveAllStatusEffects();

	UFUNCTION(BlueprintCallable, Category = "Stats")
	UStatusEffect* GetStatusEffect(TSubclassOf<UStatusEffect> StatusEffect);

	UFUNCTION(BlueprintCallable, Category = "Stats")
	int32 ApplyStatModifier(const FStatModifier& NewModifier);

	UFUNCTION(BlueprintCallable, Category = "Stats")
	UPARAM(ref) FStatModifier& GetStatModifier(EStatVariant StatVariant, int32 Id);
};
