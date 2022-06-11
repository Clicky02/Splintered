// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <GravityDirective/Public/WaveDataStructures.h>
#include <GravityDirective/Public/WaveMakeup.h>
#include "WaveInformation.generated.h"


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
	UWaveMakeup* GetWaveMakeup(int WaveNumber);

private:
	TArray<FWaveEnemy> GetWaveEnemies(int WaveNumber, int Subwave, int NumSubwave, bool isSubwave = true);
};

