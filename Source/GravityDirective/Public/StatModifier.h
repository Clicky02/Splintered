// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "StatType.h"
#include "StatModifier.generated.h"


UENUM(BlueprintType)
enum class EStatModifierDurationType : uint8
{
	Instant UMETA(DisplayName = "Instant"),
	Lasting UMETA(DisplayName = "Lasting"),
	Infinite UMETA(DisplayName = "Infinite"),
};

UENUM(BlueprintType)
enum class EStatModificationType : uint8
{
	Additive UMETA(DisplayName = "Additive"),
	Multiplicitive UMETA(DisplayName = "Multiplicitive"),
	Override UMETA(DisplayName = "Override")
};

/**
 * 
 */
USTRUCT(BlueprintType)
struct FStatModifier
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite)
	EStatVariant StatType = EStatVariant::None;

	UPROPERTY(BlueprintReadWrite)
	EStatModifierDurationType DurationType;
	UPROPERTY(BlueprintReadWrite)
	EStatModificationType ModificationType;

	UPROPERTY(BlueprintReadWrite)
	float Duration = 0.0f;

	UPROPERTY(BlueprintReadWrite)
	bool bShouldModifyMaxValue = false;
	UPROPERTY(BlueprintReadWrite)
	float MaxValueModifier = 0.0f;

	UPROPERTY(BlueprintReadWrite)
	bool bShouldModifyMinValue = false;
	UPROPERTY(BlueprintReadWrite)
	float MinValueModifier = 0.0f;

	UPROPERTY(BlueprintReadWrite)
	bool bShouldModifyValue = false;
	UPROPERTY(BlueprintReadWrite)
	float ValueModifier = 0.0f;

	UPROPERTY(BlueprintReadWrite)
	bool bShouldModifyRateOfChange = false;
	UPROPERTY(BlueprintReadWrite)
	float RateOfChangeModifier = 0.0f;

	// Order in which Stat Modifiers should be applied, lower is sooner
	UPROPERTY(BlueprintReadWrite)
	int32 Priority = 3;

	UPROPERTY()
	int32 Id;
	
};