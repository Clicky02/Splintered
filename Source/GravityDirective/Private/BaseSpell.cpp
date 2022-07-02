// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseSpell.h"
#include "StatsComponent.h"
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
                bIsTargeting = true;
                TargetingSystem->StartTargeting();
            }
            else
            {
                CastSpell();
            }
            return true;
        }

        return false;
    }
    else
    {
        if (TargetingSystem)
        {
            bIsTargeting = true;
            TargetingSystem->StartTargeting();
        }
        else
        {
            CastSpell();
        }
        return true;
    }
    
}

void UBaseSpell::EndTargeting()
{
    bIsTargeting = false;

    if (TargetingSystem) TargetingSystem->EndTargeting();

    CastSpell();
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
            OnCastSpell();
            return true;
        }
        else if (!StatsComponent->Mana->IsActive())
        {
            OnCastSpell();
            return true;
        }

        return false;
    }
    else
    {
        OnCastSpell();
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

    bIsPrimed = false;
    bIsTargeting = false;
    bIsCasting = false;
}
