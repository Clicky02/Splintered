// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseSpell.h"
#include "StatsComponent.h"
#include "..\Public\BaseSpell.h"
#include "CasterComponent.h"


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

void UBaseSpell::Init_Implementation(int32 InitialLevel)
{
    this->Level = InitialLevel;
}

void UBaseSpell::Activate_Implementation(const FSpellActivatePayload& Payload)
{

    Wielder = Payload.Wielder;
    CasterComponent = Payload.CasterComponent;
    CasterActor = Payload.CasterActor;

    StatsComponent = Cast<UStatsComponent>(Wielder->GetComponentByClass(UStatsComponent::StaticClass()));

    FSpellActivationActivatePayload ActivationPayload;
    ActivationPayload.Wielder = Wielder;
    ActivationPayload.CasterComponent = CasterComponent;
    ActivationPayload.CasterActor = CasterActor;  

    Activation->Activate(ActivationPayload);
    if (TargetingSystem) 
    {
        FTargetingActivatePayload TargetingPayload;
        TargetingPayload.Wielder = Wielder;
        TargetingPayload.CasterComponent = CasterComponent;
        TargetingPayload.CasterActor = CasterActor;

        TargetingSystem->Activate(TargetingPayload);
    }
}

void UBaseSpell::Deactivate_Implementation()
{
    Wielder = nullptr;
    CasterComponent = nullptr;
    CasterActor = nullptr;
}


void UBaseSpell::Tick_Implementation(float DeltaTime)
{
    if (bIsPrimed)
    {
        if (Activation) Activation->Tick(DeltaTime);
        if (TargetingSystem) TargetingSystem->TickTargeting(DeltaTime);
    }
}


bool UBaseSpell::StartTargeting()
{
    Activation->EndDetecting();

    if (StatsComponent && bUseManaBeforeTargeting && StatsComponent->Mana->IsActive())
    {
        if (StatsComponent->UseMana(ManaCost))
        {
            if (TargetingSystem)
            {
                TargetSuccessfully();
            }
            else
            {
                CastSuccessfully();
            }
            return true;
        }

        CastFail();
        return false;
    }
    else
    {
        if (TargetingSystem)
        {
            TargetSuccessfully();
        }
        else
        {
            CastSpell();
        }
        return true;
    }
    
}

// If ever add a fail targeting make sure to call EndSpellCast()
void UBaseSpell::EndTargeting()
{
    bIsTargeting = false;

    if (TargetingSystem) TargetingSystem->EndTargeting();

    if (WandOccupationTime == EWandOccupationType::WhileTargeting)
    {
        bIsOccupyingWand = false;
        CasterComponent->SetWandOccupied(SpellSlot, false);
    }

    CastSpell();
}

void UBaseSpell::CastSuccessfully()
{
    bIsCasting = true;
    if (WandOccupationTime == EWandOccupationType::WhileCasting || WandOccupationTime == EWandOccupationType::AtCast)
    {
        bIsOccupyingWand = true;
        CasterComponent->SetWandOccupied(SpellSlot, true);
    }
    OnCastSpell();
    if (WandOccupationTime == EWandOccupationType::AtCast)
    {
        bIsOccupyingWand = false;
        CasterComponent->SetWandOccupied(SpellSlot, false);
    }
}

void UBaseSpell::CastFail()
{
    bIsCasting = false;

    CasterComponent->SetWandOnCooldown();

    OnCastFail();
}

void UBaseSpell::TargetSuccessfully()
{
    bIsTargeting = true;
    if (WandOccupationTime == EWandOccupationType::WhileTargeting || WandOccupationTime == EWandOccupationType::AtTargetingBegin)
    {
        bIsOccupyingWand = true;
        CasterComponent->SetWandOccupied(SpellSlot, true);
    }
    TargetingSystem->StartTargeting();
    if (WandOccupationTime == EWandOccupationType::AtTargetingBegin)
    {
        bIsOccupyingWand = false;
        CasterComponent->SetWandOccupied(SpellSlot, false);
    }
}


FName UBaseSpell::GetName()
{
    return Name;
}

UStaticMesh* UBaseSpell::GetItemDisplayMesh()
{
    return ItemDisplayMesh;
}

bool UBaseSpell::CastSpell()
{
    if (StatsComponent && !bUseManaBeforeTargeting)
    {
        if (StatsComponent->UseMana(ManaCost))
        {
            CastSuccessfully();
            return true;
        }
        else if (!StatsComponent->Mana->IsActive())
        {
            CastSuccessfully();
            return true;
        }

        CastFail();
        return false;
    }
    else
    {
        CastSuccessfully();
        return true;
    }
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
    else if (bIsCasting)
    {
        EndSpellCast();
    }

    bIsPrimed = false;
    bIsTargeting = false;
    bIsCasting = false;
}

void UBaseSpell::EndSpellCast()
{
    bIsCasting = false;

    if (WandOccupationTime == EWandOccupationType::WhileCasting)
    {
        bIsOccupyingWand = false;
        CasterComponent->SetWandOccupied(SpellSlot, false);
    }
}
