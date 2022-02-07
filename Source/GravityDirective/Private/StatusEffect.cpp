// Fill out your copyright notice in the Description page of Project Settings.


#include "StatusEffect.h"
#include "StatsComponent.h"
#include "..\Public\StatusEffect.h"

UStatusEffect::UStatusEffect()
{

}

void UStatusEffect::Tick_Implementation(float DeltaTime)
{
    RemainingTime -= DeltaTime;

    if (RemainingTime < 0)
    {
        EndStatusEffect();
    }
}

void UStatusEffect::ApplyStatusEffect(AActor* Target, UStatsComponent* Stats, float StartStacks, float StartDuration)
{
    TargetActor = Target;
    TargetStats = Stats;

    StackCount = StartStacks;

    if (StartDuration > 0)
    {
        RemainingTime = StartDuration;
    }
    else 
    {
        RemainingTime = DefaultDuration;
    }

    OnApplyStatusEffect(Target, Stats);

    bIsActive = true;
}

void UStatusEffect::EndStatusEffect()
{
    bIsActive = false;

    OnEndStatusEffect();    
}

void UStatusEffect::RefreshRemainingTime()
{
    RemainingTime = DefaultDuration;
}

void UStatusEffect::SetRemainingTime(float NewRemainingTime)
{
    RemainingTime = NewRemainingTime;
}

float UStatusEffect::GetRemainingTime()
{
    return RemainingTime;
}

int32 UStatusEffect::GetStackCount()
{
    return StackCount;
}

void UStatusEffect::AddStacks(int32 NumStacks)
{
    if (bCanStack && NumStacks > 0)
    {
        StackCount += NumStacks;

        if (StackCount > MaxStacks)
        {
            StackCount = MaxStacks;
        }

        OnStackCountChange();
    }
}

void UStatusEffect::RemoveStacks(int32 NumStacks)
{
    if (bCanStack && NumStacks > 0)
    {
        StackCount -= NumStacks;

        if (StackCount <= 0)
        {
            EndStatusEffect();
        }

        OnStackCountChange();
    }
}

bool UStatusEffect::IsActive()
{
    return bIsActive;
}

UWorld* UStatusEffect::GetWorld() const
{
    if (GetOuter() == nullptr)
    {
        return nullptr;
    }

    // Special case for behavior tree nodes in the editor
    if (Cast<UPackage>(GetOuter()) != nullptr)
    {
        // GetOuter should return a UPackage and its Outer is a UWorld
        return Cast<UWorld>(GetOuter()->GetOuter());
    }

    // In all other cases...
    return GetOuter()->GetWorld();
}

