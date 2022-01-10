// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseSpell.h"
#include "..\Public\BaseSpell.h"

UWorld* UBaseSpell::GetWorld() const
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

UBaseSpell::UBaseSpell()
{

}

ESpellSlot UBaseSpell::GetSpellSlot()
{
    return SpellSlot;
}

int32 UBaseSpell::GetSpellLevel()
{
    return Level;
}

void UBaseSpell::Init_Implementation(ESpellSlot InitialSpellSlot, int32 InitialLevel)
{
    this->SpellSlot = InitialSpellSlot;
    this->Level = InitialLevel;
}

void UBaseSpell::Activate_Implementation(const FSpellActivatePayload& Payload)
{

    Wielder = Payload.Wielder;
    CasterComponent = Payload.CasterComponent;
    CasterActor = Payload.CasterActor;

    FSpellActivationActivatePayload ActivationPayload;
    ActivationPayload.Wielder = Wielder;
    ActivationPayload.CasterComponent = CasterComponent;
    ActivationPayload.CasterActor = CasterActor;  

    Activation->Activate(ActivationPayload);

    FTargetingActivatePayload TargetingPayload;
    TargetingPayload.Wielder = Wielder;
    TargetingPayload.CasterComponent = CasterComponent;
    TargetingPayload.CasterActor = CasterActor;

    TargetingSystem->Activate(TargetingPayload);
}

void UBaseSpell::Deactivate_Implementation()
{
    Wielder = nullptr;
    CasterComponent = nullptr;
    CasterActor = nullptr;
}


void UBaseSpell::Tick_Implementation()
{
    if (bIsPrimed)
    {
        if (Activation) Activation->Tick();
        if (TargetingSystem) TargetingSystem->TickTargeting();
    }
}


void UBaseSpell::StartTargeting()
{
    Activation->EndDetecting();

    if (TargetingSystem)
    {
        bIsTargeting = true;
        TargetingSystem->StartTargeting();
    }
    else
    {
        CastSpell();
    }
    
}

void UBaseSpell::EndTargeting()
{
    bIsTargeting = false;

    if (TargetingSystem) TargetingSystem->EndTargeting();
}

void UBaseSpell::Prime()
{
    bIsPrimed = true;

    Activation->StartDetecting();

}

void UBaseSpell::Unprime()
{
    if (bIsTargeting)
    {
        if (TargetingSystem) TargetingSystem->EndTargeting();
    }
    else if (bIsPrimed && !bIsCasting)
    {
        Activation->EndDetecting();
    }

    bIsPrimed = false;
    bIsTargeting = false;
    bIsCasting = false;
}
