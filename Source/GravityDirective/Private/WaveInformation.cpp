// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveInformation.h"

UWaveInformation::UWaveInformation()
{
}

UWaveMakeup* UWaveInformation::GetWaveMakeup(int WaveNumber)
{
    
    if (NumSubwaves > 0)
    {
        TArray<UWaveMakeup*> Subwaves;
        for (int i = 0; i < NumSubwaves; i++)
        {
            UWaveMakeup* Subwave = NewObject<UWaveMakeup>();
            Subwave->InitEnemyWave(GetWaveEnemies(WaveNumber, i, NumSubwaves, true), 0, false);
            Subwaves.Add(Subwave);
        }

        UWaveMakeup* WaveMakeup = NewObject<UWaveMakeup>();
        WaveMakeup->SubWaves = Subwaves;
        WaveMakeup->WaveEndType = EWaveEndType::SubwavesComplete;

        return WaveMakeup;
    }
    else
    {
        UWaveMakeup* WaveMakeup = NewObject<UWaveMakeup>();
        WaveMakeup->InitEnemyWave(GetWaveEnemies(WaveNumber, 1, 1, false), 0, false);
        return WaveMakeup;
    }

    
}

TArray<FWaveEnemy> UWaveInformation::GetWaveEnemies(int WaveNumber, int Subwave, int NumSubwave, bool isSubwave)
{
    float TotalWeight = 0;
    float WaveProgress = Subwave / (NumSubwave - 1);
    int CurrentEnemies = 0;

    TArray<FWaveEnemyInstanceProfile> ViableEnemies;
    for (int i = 0; i < WaveEnemies.Num(); i++)
    {
        FWaveEnemyGeneralProfile Enemy = WaveEnemies[i];

        int DeltaWave = Enemy.StartingWave - WaveNumber;
        
        if (DeltaWave >= 0)
        {
            FWaveEnemyInstanceProfile instanceProfile;

            instanceProfile.EnemyType = Enemy.EnemyType;
            instanceProfile.Level = Enemy.StartingLevel + (DeltaWave / Enemy.WavesPerLevelIncrease);

            if (Enemy.bUseWeight)
            {
                if (Enemy.bUseSubWaveBias && isSubwave)
                {
                    instanceProfile.Weight = (Enemy.StartingWeight + (Enemy.WeightChangePerWave * DeltaWave)) * Enemy.SubWaveBias->GetFloatValue(WaveProgress);
                }
                else
                {
                    instanceProfile.Weight = Enemy.StartingWeight + (Enemy.WeightChangePerWave * DeltaWave);
                }
                instanceProfile.Count = 0;
            }
            else
            {
                if (Enemy.bUseSubWaveBias && isSubwave)
                {
                    instanceProfile.Count = Enemy.GetCountUsingBias(WaveNumber, Subwave, NumSubwave);
                }
                else
                {
                    instanceProfile.Count = FMath::FloorToInt(Enemy.EnemyCount + (Enemy.EnemyCountChangePerWave * DeltaWave)) / NumSubwave;
                }
                instanceProfile.Weight = -1;
                
                CurrentEnemies += instanceProfile.Count;
            }


            if (instanceProfile.Weight > 0)
            {
                TotalWeight += instanceProfile.Weight;

                ViableEnemies.Emplace(instanceProfile);
            }
            else if (instanceProfile.Count > 0)
            {
                ViableEnemies.Emplace(instanceProfile);
            }
        }
    }

    int MaxEnemies = ((StartingEnemiesPerWave + AdditionalEnemiesPerWave * (WaveNumber - 1)) / NumSubwaves) * SubWaveEnemyCountBias->GetFloatValue(WaveProgress);
    int EnemiesToSplit = MaxEnemies - CurrentEnemies;

    if (MaxEnemies < 1) MaxEnemies = 1;

    FWaveEnemyInstanceProfile HighestWeightedEnemy;

    for (int i = 0; i < ViableEnemies.Num(); i++)
    {
        FWaveEnemyInstanceProfile Enemy = ViableEnemies[i];

        if (Enemy.Weight > 0)
        {
            Enemy.Count = EnemiesToSplit * (Enemy.Weight / TotalWeight);
            CurrentEnemies += Enemy.Count;

            if (HighestWeightedEnemy.Weight < Enemy.Weight)
            {
                HighestWeightedEnemy = Enemy;
            }
        }
    }

    // Make any corrections to the enemy with the most weight
    HighestWeightedEnemy.Count += EnemiesToSplit - CurrentEnemies;
    if (HighestWeightedEnemy.Count < 0) HighestWeightedEnemy.Count = 0;

    TArray<FWaveEnemy> Enemies;
    for (int i = 0; i < ViableEnemies.Num(); i++)
    {
        FWaveEnemy Enemy;
        Enemy.EnemyType = ViableEnemies[i].EnemyType;
        Enemy.Count = ViableEnemies[i].Count;
        Enemy.Level = ViableEnemies[i].Level;
        Enemies.Add(Enemy);
    }

    return Enemies;
}

// Not entirely accurate because multiple things can be highest
// *And for other reasons*
// Its accurate enoguh and I don't really want to fix it
int FWaveEnemyGeneralProfile::GetCountUsingBias(int Wave, int SubWave, int TotalNumSubWave)
{
    float TotalBias = 0;

    float SubWaveProgress = SubWave / (TotalNumSubWave - 1);
    float CurSubWaveBias = SubWaveBias->GetFloatValue(SubWaveProgress);
    bool bIsHighest = true;

    int CurEnemyCount = FMath::FloorToInt(EnemyCount + (EnemyCountChangePerWave * (Wave - StartingWave)));

    if (CurSubWaveBias <= 0 || Wave < StartingWave || CurEnemyCount <= 0) return 0;

    for (int i = 0; i < TotalNumSubWave; i++)
    {
        float Bias = SubWaveBias->GetFloatValue(i / (TotalNumSubWave - 1));

        if (Bias > 0) 
        {
            TotalBias += Bias;
        }
        
        if (i != SubWave && Bias >= CurSubWaveBias) 
        {
            bIsHighest = false;
        }
    }

    
    int Count = FMath::FloorToInt(CurEnemyCount * (CurSubWaveBias / TotalBias));

    if (bIsHighest) // Error correction cause it underestimates
    {
        Count++;
    }

    if (Count < 0)
    {
        return 0;
    }

    return Count;
}
