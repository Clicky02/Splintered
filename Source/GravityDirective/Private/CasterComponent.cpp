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

inline void UCasterComponent::PrimeAll()
{
	if (PrimarySpell) PrimarySpell->Prime();
	if (UpwardSpell) UpwardSpell->Prime();
	if (DownwardSpell) DownwardSpell->Prime();
	if (BlockingSpell) BlockingSpell->Prime();
}

inline void UCasterComponent::UnprimeAll()
{
	if (PrimarySpell) PrimarySpell->Unprime();
	if (UpwardSpell) UpwardSpell->Unprime();
	if (DownwardSpell) DownwardSpell->Unprime();
	if (BlockingSpell) BlockingSpell->Unprime();
}



// Called every frame
void UCasterComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PrimarySpell) PrimarySpell->Tick();
	if (UpwardSpell) UpwardSpell->Tick();
	if (DownwardSpell) DownwardSpell->Tick();
	if (BlockingSpell) BlockingSpell->Tick();
}

UBaseSpell* UCasterComponent::GetSpell(ESpellSlot Slot) {
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

void UCasterComponent::SetCasting(ESpellSlot SpellSlot, bool IsCasting)
{

	if (!bIsCasting && IsCasting) 
	{
		bIsCasting = IsCasting;
		if (PrimarySpell && SpellSlot != ESpellSlot::Primary) PrimarySpell->Unprime();
		if (UpwardSpell && SpellSlot != ESpellSlot::Upward) UpwardSpell->Unprime();
		if (DownwardSpell && SpellSlot != ESpellSlot::Downward) DownwardSpell->Unprime();
		if (BlockingSpell && SpellSlot != ESpellSlot::Block) BlockingSpell->Unprime();
	}
	else if (bIsCasting && !IsCasting)
	{
		bIsCasting = IsCasting;
		PrimeAll();
	}

	
}

void UCasterComponent::SetSpell(UBaseSpell* Spell)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("A"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("A"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("A"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("A"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("A"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("A"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("A"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("A"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("A"));
	if (Spell)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("B"));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("B"));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("B"));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("b"));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("b"));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("b"));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("b"));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("b"));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("b"));
		switch (Spell->GetSpellSlot()) {
		case ESpellSlot::Primary:
			PrimarySpell = Spell;
			break;
		case ESpellSlot::Upward:
			UpwardSpell = Spell;
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("c"));
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("c"));
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("c"));
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("c"));
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("c"));
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("c"));
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("c"));
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("c"));
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("c"));
			break;
		case ESpellSlot::Downward:
			DownwardSpell = Spell;
			break;
		case ESpellSlot::Block:
			BlockingSpell = Spell;
			break;
		default:
			return;
		}
		
		if (bIsActivated)
		{
			FSpellActivatePayload Payload;
			Payload.Wielder = Player;
			Payload.CasterComponent = this;
			Payload.CasterActor = this->GetOwner();

			Spell->Activate(Payload);
		}

		if (bIsPrimed)
		{
			Spell->Prime();
		}
	}
}

void UCasterComponent::RemoveSpell(ESpellSlot Slot)
{
	UBaseSpell* Spell;

	switch (Slot) {
	case ESpellSlot::Primary:
		Spell = PrimarySpell;
		PrimarySpell = nullptr;
		break;
	case ESpellSlot::Upward:
		Spell = UpwardSpell;
		UpwardSpell = nullptr;
		break;
	case ESpellSlot::Downward:
		Spell = DownwardSpell;
		DownwardSpell = nullptr;
		break;
	case ESpellSlot::Block:
		Spell = BlockingSpell;
		BlockingSpell = nullptr;
		break;
	default:
		return;
	}

	if (Spell)
	{
		if (bIsActivated)
		{
			Spell->Deactivate();
		}

		if (bIsPrimed)
		{
			Spell->Unprime();
		}
	}

}



void UCasterComponent::BeginControl_Implementation(const FBeginControlPayload& Payload)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Control"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Control"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Control"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Control"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Control"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Control"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Control"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Control"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Control"));

	Player = Payload.Player;
	ConnectedHand = Payload.Hand;

	FSpellActivatePayload ActivatePayload;
	ActivatePayload.Wielder = Player;
	ActivatePayload.CasterComponent = this;
	ActivatePayload.CasterActor = this->GetOwner();

	if (PrimarySpell) PrimarySpell->Activate(ActivatePayload);
	if (UpwardSpell) UpwardSpell->Activate(ActivatePayload);
	if (DownwardSpell) DownwardSpell->Activate(ActivatePayload);
	if (BlockingSpell) BlockingSpell->Activate(ActivatePayload);
	
}

void UCasterComponent::EndControl_Implementation()
{
	Player = nullptr;
	CastingSlot = ESpellSlot::None;

	if (bIsPrimed)
	{
		UnprimeAll();

		if (PrimarySpell) PrimarySpell->Deactivate();
		if (UpwardSpell) UpwardSpell->Deactivate();
		if (DownwardSpell) DownwardSpell->Deactivate();
		if (BlockingSpell) BlockingSpell->Deactivate();
	}

	bIsActivated = false;
	bIsPrimed = false;
	
}

void UCasterComponent::PrimaryPressed_Implementation()
{

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Press"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Press"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Press"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Press"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Press"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Press"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Press"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Press"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Press"));
	bIsPrimed = true;

	PrimeAll();
}

void UCasterComponent::PrimaryReleased_Implementation()
{
	bIsPrimed = false;

	UnprimeAll();
}
