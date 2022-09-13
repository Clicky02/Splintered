// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HeldInteractable.h"
#include "BaseSpell.h"
#include "Spell.h"
#include "SpellSlot.h"
#include "Math/Vector.h"
#include "CasterComponent.generated.h"


UENUM(BlueprintType)
enum class ECasterStance : uint8
{
	None UMETA(DisplayName = "None"),
	Upward UMETA(DisplayName = "Upward"),
	Sideways UMETA(DisplayName = "Sideways"),
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GRAVITYDIRECTIVE_API UCasterComponent : public UActorComponent, public IHeldInteractable
{
	GENERATED_BODY()
		

	bool bIsActivated = false;

	bool bPrimeButtonPressed = false;

	float CurrentPrimeDelay = -1;

	float MaxPrimeDelay = 0.6f;

	bool bIsPrimed = false;

	bool bIsCasting = false;

	ESpellSlot CastingSlot = ESpellSlot::None;

	bool bForwardVelocityIsDirty = true;
	float ForwardVelocity = 0;

	bool bOutwardVelocityIsDirty = true;
	float OutwardVelocity = 0;

	bool bOutwardDirectionIsDirty = true;
	FVector OutwardDirection;

	bool bCasterStanceIsDirty = true;
	ECasterStance CasterStance = ECasterStance::None;

	const int NumLocations = 10;
	int CurrentLocationIndex = 0;
	TArray<FVector> Locations;
	TArray<float> LocationTimes;

	bool bVelocityIsDirty = true;
	FVector Velocity;

	USceneComponent* VelComp;

protected:

	// The actor wielding the caster
	AActor* Player;

	// The static mesh of the hand holding the staff
	UMeshComponent* ConnectedHand;

	// The static mesh of the staff
	UStaticMeshComponent* CasterActorMesh;

public:	

	UPROPERTY(VisibleAnywhere, Instanced)
	UBaseSpell* PrimarySpell;

	UPROPERTY(VisibleAnywhere, Instanced)
	UBaseSpell* UpwardSpell;

	UPROPERTY(VisibleAnywhere, Instanced)
	UBaseSpell* DownwardSpell;

	UPROPERTY(VisibleAnywhere, Instanced)
	UBaseSpell* BlockingSpell;


	// Sets default values for this component's properties
	UCasterComponent();

protected:

	// Called when the game starts
	virtual void BeginPlay() override;

	inline void PrimeAll();

	inline void UnprimeAll();

public:	

	virtual void BeginControl_Implementation(const FBeginControlPayload& Payload) override;

	virtual void EndControl_Implementation() override;

	virtual void PrimaryPressed_Implementation() override;

	virtual void PrimaryReleased_Implementation() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Caster")
	void SetSpell(UBaseSpell* Spell);

	UFUNCTION(BlueprintCallable, Category = "Caster")
	void RemoveSpell(ESpellSlot Slot);

	UFUNCTION(BlueprintCallable, Category = "Caster")
	UBaseSpell* GetSpell(ESpellSlot Slot);

	UFUNCTION(BlueprintCallable, Category = "Caster")
	void SetWandOccupied(ESpellSlot SpellSlot, bool IsOccupied);

	UFUNCTION(BlueprintCallable, Category = "Caster")
	void SetWandOnCooldown();

	UFUNCTION(BlueprintCallable, Category = "Caster")
	AActor* GetWielder();

	UFUNCTION(BlueprintCallable, Category = "Caster")
	UMeshComponent* GetConnectedHand();

	UFUNCTION(BlueprintCallable, Category = "Caster")
	UStaticMeshComponent* GetStaticMesh();

	UFUNCTION(BlueprintCallable, Category = "Caster")
	FVector GetVelocity();

	UFUNCTION(BlueprintCallable, Category = "Caster")
	float GetForwardVelocity();

	UFUNCTION(BlueprintCallable, Category = "Caster")
	float GetOutwardVelocity();

	UFUNCTION(BlueprintCallable, Category = "Caster")
	FVector GetOutwardDirection();

	UFUNCTION(BlueprintCallable, Category = "Caster")
	FTransform GetCastPointTansform();

	UFUNCTION(BlueprintCallable, Category = "Caster")
	FVector GetCastPointForward();

	// Currently will only return upward, sideways, or none
	UFUNCTION(BlueprintCallable, Category = "Caster")
	ECasterStance GetCasterStance();
};
