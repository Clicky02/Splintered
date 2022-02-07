// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "StatusEffect.generated.h"

class UStatsComponent;

/**
 * 
 */
UCLASS(Blueprintable)
class GRAVITYDIRECTIVE_API UStatusEffect : public UObject
{
	GENERATED_BODY()

private:

	float RemainingTime = 0.0f;

protected:

	UPROPERTY(BlueprintReadWrite)
	bool bIsActive = false;

	UPROPERTY(BlueprintReadWrite)
	AActor* TargetActor;

	UPROPERTY(BlueprintReadWrite)
	UStatsComponent* TargetStats;

	//How long the Status Effect should last
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DefaultDuration = 0.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanStack = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "bCanStack"))
	int32 MaxStacks = 1;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (EditCondition = "bCanStack"))
	int32 StackCount = 1;

public:
	// Sets default values
	UStatusEffect();
	
	/*
		This function is automatically when the affect is applied.
	*/
	UFUNCTION(BlueprintCallable)
	void ApplyStatusEffect(AActor* Target, UStatsComponent* Stats, float StartStacks = 1, float StartDuration = -1);

	/*
		This function is called automatically when the duration runs out. Calling it will end the status effect.
		To have something happen when the effect ends, OnEndStatusEffect should be overridden.
		This function makes the effect not active, and the stats component will automatically remove any effects that
		are not active.
	*/
	UFUNCTION(BlueprintCallable)
	void EndStatusEffect();

	UFUNCTION(BlueprintCallable)
	void RefreshRemainingTime();

	UFUNCTION(BlueprintCallable)
	void SetRemainingTime(float NewRemainingTime);

	UFUNCTION(BlueprintCallable)
	float GetRemainingTime();

	UFUNCTION(BlueprintCallable)
	int32 GetStackCount();

	UFUNCTION(BlueprintCallable)
	void AddStacks(int32 NumStacks);

	UFUNCTION(BlueprintCallable)
	void RemoveStacks(int32 NumStacks);

	UFUNCTION(BlueprintCallable)
	bool IsActive();


	/* Tick Implementation Functions*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Tick(float DeltaTime);
	virtual void Tick_Implementation(float DeltaTime);

	UWorld* GetWorld() const override;

protected:
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnStackCountChange();
	virtual void OnStackCountChange_Implementation() {};

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnApplyStatusEffect(AActor* Target, UStatsComponent* Stats);
	virtual void OnApplyStatusEffect_Implementation(AActor* Target, UStatsComponent* Stats) {};

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnEndStatusEffect();
	virtual void OnEndStatusEffect_Implementation() {};
};
