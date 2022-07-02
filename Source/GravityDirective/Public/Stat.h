// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "StatModifier.h"
#include "StatType.h"
#include "Stat.generated.h"


USTRUCT(BlueprintType)
struct FOnStatChangePayload
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat Change")
	UStat* StatObject;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat Change")
	float OldValue;
};

USTRUCT(BlueprintType)
struct FOnStatModifierAppliedPayload
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat Change")
	UStat* StatObject;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat Change")
	FStatModifier Modifier;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStatChange, const FOnStatChangePayload&, Payload);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStatModifierApplied, const FOnStatModifierAppliedPayload&, Payload);

/**
 * 
 */
UCLASS(DefaultToInstanced, EditInlineNew, Blueprintable)
class GRAVITYDIRECTIVE_API UStat : public UObject, public FTickableGameObject
{
	GENERATED_BODY()

private:

	//int32 CurrentId = 0;

	float TimeSinceLastTick = 0;

protected:

	TArray<FStatModifier> StatModifiers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	EStatVariant Type = EStatVariant::None;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	bool bHasMaxValue = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (EditCondition = "bHasMaxValue"))
	float BaseMaxValue = 0.0f;
	UPROPERTY(BlueprintReadWrite, Category = "Stats", meta = (EditCondition = "bHasMaxValue"))
	float MaxValue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	bool bHasMinValue = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (EditCondition = "bHasMinValue"))
	float BaseMinValue = 0.0f;
	UPROPERTY(BlueprintReadWrite, Category = "Stats", meta = (EditCondition = "bHasMinValue"))
	float MinValue;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float BaseValue = 0.0f;
	UPROPERTY(BlueprintReadWrite, Category = "Stats")
	float Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float BaseRateOfChange = 0.0f;
	UPROPERTY(BlueprintReadWrite, Category = "Stats")
	float RateOfChange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float MinTimeBetweenTick = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	bool bIsActive = false;


public: 

	UPROPERTY(BlueprintAssignable, Category = "Stats")
	FOnStatChange OnStatChange;

	UPROPERTY(BlueprintAssignable, Category = "Stats")
	FOnStatModifierApplied OnStatModifierApplied;

protected:

	void ModifyValues(float* BaseValue, float* Value, EStatModifierDurationType DurationType, EStatModificationType ModificationType, float ModifierValue);

	void RefreshValues();

	void ApplyModifiersToValue();

	void ApplyModifiersToMaxValue();

	void ApplyModifiersToMinValue();

	void ApplyModifiersToRateOfChange();

	void CheckValid();

public:

	UStat();

	UFUNCTION(BlueprintCallable, Category = "Stats")
	EStatVariant GetStatVariant();

	UFUNCTION(BlueprintCallable, Category = "Stats")
	float GetMaxValue();
	UFUNCTION(BlueprintCallable, Category = "Stats")
	float GetBaseMaxValue();

	UFUNCTION(BlueprintCallable, Category = "Stats")
	float GetMinValue();
	UFUNCTION(BlueprintCallable, Category = "Stats")
	float GetBaseMinValue();

	UFUNCTION(BlueprintCallable, Category = "Stats")
	float GetValue();
	UFUNCTION(BlueprintCallable, Category = "Stats")
	float GetBaseValue();

	UFUNCTION(BlueprintCallable, Category = "Stats")
	float GetRateOfChange();
	UFUNCTION(BlueprintCallable, Category = "Stats")
	float GetBaseRateOfChange();

	UFUNCTION(BlueprintCallable, Category = "Stats")
	bool IsActive();


	UFUNCTION(BlueprintCallable, Category = "Stats")
	void Set(float NewValue);

	UFUNCTION(BlueprintCallable, Category = "Stats")
	void Add(float Amount);

	UFUNCTION(BlueprintCallable, Category = "Stats")
	int32 ApplyStatModifier(const FStatModifier& NewModifier);
	
	UFUNCTION(BlueprintCallable, Category = "Stats")
	UPARAM(ref) FStatModifier& GetStatModifier(int32 Id);

	UFUNCTION(BlueprintCallable, Category = "Stats")
	void RemoveStatModifier(int32 Id);

	/* Tick Implementation Functions*/
	void Tick(float DeltaTime) override;
	bool IsTickable() const override;
	bool IsTickableInEditor() const override;
	bool IsTickableWhenPaused() const override;
	TStatId GetStatId() const override;

	UWorld* GetWorld() const override;

	friend class UStatsComponent;
};
