// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellActivation.h"

UWorld* USpellActivation::GetWorld() const
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

void USpellActivation::StartDetecting_Implementation() 
{
    bIsPrimed = true;
}

void USpellActivation::Tick_Implementation(float DeltaTime)
{
}

void USpellActivation::EndDetecting_Implementation()
{
    bIsPrimed = false;
}

void USpellActivation::Init_Implementation(UBaseSpell* SpellInstance)
{
    Spell = SpellInstance;
}

void USpellActivation::Activate_Implementation(const FSpellActivationActivatePayload& Payload)
{
    Wielder = Payload.Wielder;
    CasterComponent = Payload.CasterComponent;
    CasterActor = Payload.CasterActor;
}
