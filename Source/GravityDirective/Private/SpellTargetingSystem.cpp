// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellTargetingSystem.h"

void USpellTargetingSystem::StartTargeting_Implementation() 
{

}

void USpellTargetingSystem::TickTargeting_Implementation()
{

}

void USpellTargetingSystem::EndTargeting_Implementation()
{

}

UWorld* USpellTargetingSystem::GetWorld() const
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

void USpellTargetingSystem::Init_Implementation(UBaseSpell* SpellInstance)
{
   Spell = SpellInstance;
}

void USpellTargetingSystem::Activate_Implementation(const FTargetingActivatePayload& Payload)
{
    Wielder = Payload.Wielder;
    CasterComponent = Payload.CasterComponent;
    CasterActor = Payload.CasterActor;
}
