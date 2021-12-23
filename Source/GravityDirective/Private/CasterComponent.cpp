// Fill out your copyright notice in the Description page of Project Settings.


#include "CasterComponent.h"

const float MIN_UPWARD_DISTANCE = 50;

// Sets default values for this component's properties
UCasterComponent::UCasterComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCasterComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UCasterComponent::GiveSpellAbility(USpell* Spell)
{
	if (ConnectedAbilitySystem)
	{
		if (Player->HasAuthority() && Spell)
		{
			Spell->SpellSpecHandle = ConnectedAbilitySystem->GiveAbility(FGameplayAbilitySpec(Spell->SpellType.GetDefaultObject(), Spell->Level, 0));
		}
	}

}

void UCasterComponent::RemoveSpellAbility(USpell* Spell)
{
	if (ConnectedAbilitySystem)
	{
		if (Player->HasAuthority() && Spell->SpellSpecHandle.IsValid() && Spell)
		{
			ConnectedAbilitySystem->ClearAbility(Spell->SpellSpecHandle);
			Spell->SpellSpecHandle = FGameplayAbilitySpecHandle();
		}
	}

}


// Called every frame
void UCasterComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsCasting)
	{
		FVector CurrentPosition = GetOwner()->GetActorLocation();

		// Upward Continuation 
		if (CastingSlot == ESpellSlot::Upward)
		{
			float DeltaZ = CurrentPosition.Z - StartPosition.Z;
			if (DeltaZ < MIN_UPWARD_DISTANCE)
			{
				ConnectedAbilitySystem->CancelAbilityHandle(UpwardSpell->SpellSpecHandle);
				bIsCasting = false;
				CastingSlot = ESpellSlot::None;
			}
		}
	} 
	else if (bIsActivated)
	{
		FVector CurrentPosition = GetOwner()->GetActorLocation();

		// Upward Activation 
		float DeltaZ = CurrentPosition.Z - StartPosition.Z;
		if (UpwardSpell && DeltaZ > MIN_UPWARD_DISTANCE)
		{
			ConnectedAbilitySystem->TryActivateAbilityByClass(UpwardSpell->SpellType);
			bIsCasting = true;
			CastingSlot = ESpellSlot::Upward;
		}
	}
}

USpell* UCasterComponent::GetSpell(ESpellSlot Slot) {
	switch (Slot) {
	case ESpellSlot::Primary:
		return PrimarySpell;
	case ESpellSlot::Upward:
		return UpwardSpell;
	case ESpellSlot::Downward:
		return DownwardSpell;
	case ESpellSlot::Block:
		return BlockingSpell;
	default:
		return nullptr;
	}
}

void UCasterComponent::SetSpell(USpell* Spell)
{
	if (Spell)
	{
		switch (Spell->SpellSlot) {
		case ESpellSlot::Primary:
			if (PrimarySpell) RemoveSpellAbility(PrimarySpell);
			PrimarySpell = Spell;
			break;
		case ESpellSlot::Upward:
			if (UpwardSpell) RemoveSpellAbility(UpwardSpell);
			UpwardSpell = Spell;
			break;
		case ESpellSlot::Downward:
			if (DownwardSpell) RemoveSpellAbility(DownwardSpell);
			DownwardSpell = Spell;
			break;
		case ESpellSlot::Block:
			if (BlockingSpell) RemoveSpellAbility(BlockingSpell);
			BlockingSpell = Spell;
			break;
		default:
			return;
		}

		GiveSpellAbility(Spell);
	}
}

void UCasterComponent::RemoveSpell(ESpellSlot Slot)
{
	switch (Slot) {
	case ESpellSlot::Primary:
		if (PrimarySpell) RemoveSpellAbility(PrimarySpell);
		PrimarySpell = nullptr;
		break;
	case ESpellSlot::Upward:
		if (UpwardSpell) RemoveSpellAbility(UpwardSpell);
		UpwardSpell = nullptr;
		break;
	case ESpellSlot::Downward:
		if (DownwardSpell) RemoveSpellAbility(DownwardSpell);
		DownwardSpell = nullptr;
		break;
	case ESpellSlot::Block:
		if (BlockingSpell) RemoveSpellAbility(BlockingSpell);
		BlockingSpell = nullptr;
		break;
	default:
		return;
	}
}



void UCasterComponent::BeginControl_Implementation(const FBeginControlPayload& Payload)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Control"));

	TArray<UActorComponent*> ConnectedAbilitySystems = Payload.Player->GetComponentsByClass(UAbilitySystemComponent::StaticClass());

	if (ConnectedAbilitySystems.Num() <= 0) return;
	
	ConnectedAbilitySystem = dynamic_cast<UAbilitySystemComponent*>(ConnectedAbilitySystems[0]);

	if (ConnectedAbilitySystem == nullptr) return;

	Player = Payload.Player;
	ConnectedHand = Payload.Hand;

	if (PrimarySpell) GiveSpellAbility(PrimarySpell);
	if (UpwardSpell) GiveSpellAbility(UpwardSpell);
	if (DownwardSpell) GiveSpellAbility(DownwardSpell);
	if (BlockingSpell) GiveSpellAbility(BlockingSpell);
	
}

void UCasterComponent::EndControl_Implementation()
{
	ConnectedAbilitySystem = nullptr;
	Player = nullptr;
	bIsActivated = false;
	CastingSlot = ESpellSlot::None;
	bIsCasting = false;
}

void UCasterComponent::PrimaryPressed_Implementation()
{
	bIsActivated = true;
	StartPosition = GetOwner()->GetActorLocation();
}

void UCasterComponent::PrimaryReleased_Implementation()
{
	bIsActivated = false;
}
