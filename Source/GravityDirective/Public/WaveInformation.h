// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WaveInformation.generated.h"

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

USTRUCT(BlueprintType)
struct FWaveMakeup
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	TArray<FWaveEnemy> Enemies;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	EWaveEndType WaveEndType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	int RemainingEnemiesWhenEnd;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	bool bKillRemainingEnemiesOnEnd;


};

USTRUCT(BlueprintType)
struct FDistributedWaveMakeup : public FWaveMakeup
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	TArray<FWaveMakeup> SubWaves;

};

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class GRAVITYDIRECTIVE_API UWaveInformation : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	int StartingEnemiesPerWave;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	int AdditionalEnemiesPerWave;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	int MaximumEnemiesPerWave = 30;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	int NumSubwaves = 3;

	// TODO
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	int WavesPerBossWave = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	float SpawnDelay = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	bool bUseRandom = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	bool bUseSubWaveEnemyCountBias = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	UCurveFloat* SubWaveEnemyCountBias;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	TArray<FWaveEnemyGeneralProfile> WaveEnemies;

public:
	UWaveInformation();

	UFUNCTION(BlueprintCallable)
	FWaveMakeup GetWaveMakeup(int WaveNumber);

private:
	FWaveMakeup GetIndividualWave(int WaveNumber, int Subwave, int NumSubwave, bool isSubwave = true);
};

