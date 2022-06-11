// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WaveDataStructures.generated.h"

UENUM(BlueprintType)
enum class EWaveEndType : uint8
{
	Timer UMETA(DisplayName = "Timer"),
	RemainingEnemies UMETA(DisplayName = "Remaining Enemies"),
	SubwavesComplete UMETA(DisplayName = "Subwaves Complete"),
};

USTRUCT(BlueprintType)
struct FWaveEnemyGeneralProfile
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	TSubclassOf<ACharacter> EnemyType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	int StartingWave;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	int StartingLevel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	int WavesPerLevelIncrease;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	bool bUseWeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	float StartingWeight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	float WeightChangePerWave;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	int EnemyCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	float EnemyCountChangePerWave;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	bool bUseSubWaveBias;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	UCurveFloat* SubWaveBias;

public:
	int GetCountUsingBias(int Wave, int Subwave, int TotalNumSubwave);
};

USTRUCT(BlueprintType)
struct FWaveEnemyInstanceProfile
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	TSubclassOf<ACharacter> EnemyType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	int Level = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	int Count = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	float Weight = 0;
};

USTRUCT(BlueprintType)
struct FWaveEnemy
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	TSubclassOf<ACharacter> EnemyType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	int Level;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	int Count;
};