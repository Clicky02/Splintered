// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <GravityDirective/Public/WaveDataStructures.h>
#include "WaveMakeup.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class GRAVITYDIRECTIVE_API UWaveMakeup : public UObject
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	TArray<UWaveMakeup*> SubWaves;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	TArray<FWaveEnemy> Enemies;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	EWaveEndType WaveEndType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	int RemainingEnemiesWhenEnd;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	bool bKillRemainingEnemiesOnEnd;

	UFUNCTION(BlueprintCallable)
	bool HasSubwaves();

	UFUNCTION(BlueprintCallable)
	void InitParentWave(TArray<UWaveMakeup*> InitialSubWaves);

	UFUNCTION(BlueprintCallable)
	void InitEnemyWave(TArray<FWaveEnemy> InitialEnemies, int InitialRemainingEnemiesWhenEnd, bool bInitialKillRemainingEnemiesOnEnd);

	// TODO - Unimplemented, placeholder
	void InitTimedWave();
};