// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveMakeup.h"

bool UWaveMakeup::HasSubwaves()
{
	return SubWaves.Num() > 0;
}

void UWaveMakeup::InitParentWave(TArray<UWaveMakeup*> InitialSubWaves)
{
	WaveEndType = EWaveEndType::SubwavesComplete;
	SubWaves = InitialSubWaves;
}

void UWaveMakeup::InitEnemyWave(TArray<FWaveEnemy> InitialEnemies, int InitialRemainingEnemiesWhenEnd, bool bInitialKillRemainingEnemiesOnEnd)
{
	WaveEndType = EWaveEndType::RemainingEnemies;
	Enemies = InitialEnemies;
	RemainingEnemiesWhenEnd = InitialRemainingEnemiesWhenEnd;
	bKillRemainingEnemiesOnEnd = bInitialKillRemainingEnemiesOnEnd;
}

void UWaveMakeup::InitTimedWave()
{
}
