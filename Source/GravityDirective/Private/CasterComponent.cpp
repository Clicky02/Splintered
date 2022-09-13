// Fill out your copyright notice in the Description page of Project Settings.

#define PERPINDICULAR_TO_OUTWARD_DOT_TOLERANCE 0.3
#define PERPINDICULAR_TO_UP_DOT_TOLERANCE 0.12
#define UPWARD_DOT_MIN 0.72

#include "CasterComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include <GravityDirective/Public/BaseVRPawn.h>
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>

const float MIN_UPWARD_DISTANCE = 50;

// Sets default values for this component's properties
UCasterComponent::UCasterComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	Locations.AddUninitialized(10);
	LocationTimes.AddUninitialized(10);

	// ...
}

// Instead, listen to events on the spells?
// Replace spell slots with array?
// Make spells components?


// Called when the game starts
void UCasterComponent::BeginPlay()
{
	Super::BeginPlay();

	CasterActorMesh = Cast<UStaticMeshComponent>(GetOwner()->GetComponentByClass(UStaticMeshComponent::StaticClass()));
	
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

	bForwardVelocityIsDirty = true;
	bOutwardVelocityIsDirty = true;
	bOutwardDirectionIsDirty = true;
	bCasterStanceIsDirty = true;
	bVelocityIsDirty = true;

	if (!bIsPrimed)
	{
		if (CurrentPrimeDelay >= 0)
		{
			CurrentPrimeDelay -= DeltaTime;
		}

		if (CurrentPrimeDelay < 0 && bPrimeButtonPressed)
		{
			bIsPrimed = true;
			PrimeAll();
		}
	}

	CurrentLocationIndex++;
	if (CurrentLocationIndex >= NumLocations) CurrentLocationIndex = 0;
	Locations[CurrentLocationIndex] = VelComp->GetComponentLocation();
	LocationTimes[CurrentLocationIndex] = UGameplayStatics::GetRealTimeSeconds(GetWorld());

	if (PrimarySpell) PrimarySpell->Tick(DeltaTime);
	if (UpwardSpell) UpwardSpell->Tick(DeltaTime);
	if (DownwardSpell) DownwardSpell->Tick(DeltaTime);
	if (BlockingSpell) BlockingSpell->Tick(DeltaTime);
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

void UCasterComponent::SetWandOccupied(ESpellSlot SpellSlot, bool IsOccupied)
{
	if (!bIsCasting && IsOccupied)
	{
		bIsCasting = IsOccupied;

		if (PrimarySpell && SpellSlot != ESpellSlot::Primary) PrimarySpell->Unprime();
		if (UpwardSpell && SpellSlot != ESpellSlot::Upward) UpwardSpell->Unprime();
		if (DownwardSpell && SpellSlot != ESpellSlot::Downward) DownwardSpell->Unprime();
		if (BlockingSpell && SpellSlot != ESpellSlot::Block) BlockingSpell->Unprime();
	}
	else if (bIsCasting && !IsOccupied)
	{
		SetWandOnCooldown();
	}

	
}

AActor* UCasterComponent::GetWielder()
{
	return Player;
}

void UCasterComponent::SetWandOnCooldown()
{
	bIsCasting = false;

	UnprimeAll();

	bIsPrimed = false;

	if (bPrimeButtonPressed)
	{
		CurrentPrimeDelay = MaxPrimeDelay;
	}
}

UMeshComponent* UCasterComponent::GetConnectedHand()
{
	return ConnectedHand;
}

UStaticMeshComponent* UCasterComponent::GetStaticMesh()
{
	return CasterActorMesh;
}

FVector UCasterComponent::GetVelocity()
{
	if (bVelocityIsDirty)
	{
		int LastIndex = CurrentLocationIndex - 1;
		if (LastIndex < 0) LastIndex = 9;

		Velocity = (Locations[CurrentLocationIndex] - Locations[LastIndex]) / (LocationTimes[CurrentLocationIndex] - LocationTimes[LastIndex]);
		
		bVelocityIsDirty = false;
	}

	return Velocity;
}

float UCasterComponent::GetForwardVelocity()
{
	if (bForwardVelocityIsDirty)
	{	
		FVector Vel = GetVelocity();

		ForwardVelocity = Vel.Dot(UKismetMathLibrary::GetForwardVector(CasterActorMesh->GetSocketRotation("CastPoint")));
		bForwardVelocityIsDirty = false;
	}

	return ForwardVelocity;
}

float UCasterComponent::GetOutwardVelocity()
{
	if (bOutwardVelocityIsDirty)
	{
		OutwardVelocity = GetVelocity().Dot(GetOutwardDirection());
		bOutwardVelocityIsDirty = false;
	}

	return OutwardVelocity;
}

FVector UCasterComponent::GetOutwardDirection()
{
	if (bOutwardDirectionIsDirty)
	{

		ABaseVRPawn* Pawn = Cast<ABaseVRPawn>(Player);

		// Set OutwardDirection to the center position of the player
		if (Pawn)
		{
			OutwardDirection = Pawn->GetCameraPosition();

			OutwardDirection.SetComponentForAxis(EAxis::Y, (Pawn->GetActorLocation().Y + OutwardDirection.Y) / 2);
		}
		else
		{
			OutwardDirection = Player->GetActorLocation();
		}

		//Set OutwardDirection to the Outward direction
		OutwardDirection = (VelComp->GetComponentLocation() - OutwardDirection);
		OutwardDirection.Normalize(0.01);

		bOutwardDirectionIsDirty = false;
	}

	return OutwardDirection;
}

FTransform UCasterComponent::GetCastPointTansform()
{
	return CasterActorMesh->GetSocketTransform("CastPoint");
}

FVector UCasterComponent::GetCastPointForward()
{
	return UKismetMathLibrary::GetForwardVector(CasterActorMesh->GetSocketRotation("CastPoint"));
}

ECasterStance UCasterComponent::GetCasterStance()
{
	if (bCasterStanceIsDirty)
	{
		FVector ForwardVec = UKismetMathLibrary::GetForwardVector(CasterActorMesh->GetSocketRotation("CastPoint"));

		float UpDot = ForwardVec.Dot(UKismetMathLibrary::Vector_Up());

		bool bIsPerpindicularToOutward = abs(ForwardVec.Dot(GetOutwardDirection())) < PERPINDICULAR_TO_OUTWARD_DOT_TOLERANCE;
		bool bIsPerpindicularToUp = abs(UpDot) < PERPINDICULAR_TO_UP_DOT_TOLERANCE;
		bool bIsUpward = UpDot > UPWARD_DOT_MIN;

		if (bIsPerpindicularToOutward && bIsPerpindicularToUp)
		{
			CasterStance = ECasterStance::Sideways;
		}
		else if (bIsUpward)
		{
			CasterStance = ECasterStance::Upward;
		}
		else
		{
			CasterStance = ECasterStance::None;
		}

		bCasterStanceIsDirty = false;
	}

	return CasterStance;
}

void UCasterComponent::SetSpell(UBaseSpell* Spell)
{
	if (Spell)
	{
		switch (Spell->GetSpellSlot()) {
		case ESpellSlot::Primary:
			PrimarySpell = Spell;
			break;
		case ESpellSlot::Upward:
			UpwardSpell = Spell;
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
	
	VelComp = ConnectedHand;

	if (!VelComp)
	{
		VelComp = GetOwner()->GetRootComponent();
	}
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
	bPrimeButtonPressed = false;
}

void UCasterComponent::PrimaryPressed_Implementation()
{
	bPrimeButtonPressed = true;

	if (!bIsPrimed && CurrentPrimeDelay < 0)
	{
		bIsPrimed = true;
		PrimeAll();
	}

}

void UCasterComponent::PrimaryReleased_Implementation()
{
	bPrimeButtonPressed = false;

	if (bIsPrimed)
	{
		bIsPrimed = false;
		UnprimeAll();
	}
}
