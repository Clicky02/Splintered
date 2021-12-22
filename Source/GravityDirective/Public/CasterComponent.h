// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HeldInteractable.h"
#include "BaseSpell.h"
#include "Spell.h"
#include "SpellSlot.h"
#include "AbilitySystemComponent.h"
#include "Math/Vector.h"
#include "CasterComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GRAVITYDIRECTIVE_API UCasterComponent : public UActorComponent, public IHeldInteractable
{
	GENERATED_BODY()
		
	const float MIN_UPWARD_DISTANCE = 0.1;

	FVector StartPosition;

	bool bIsActivated = false;

	bool bIsCasting = false;

	ESpellSlot CastingSlot = ESpellSlot::None;

protected:

	UAbilitySystemComponent* ConnectedAbilitySystem;

	AActor* Player;

	UStaticMeshComponent* ConnectedHand;

public:	

	USpell* PrimarySpell;

	USpell* UpwardSpell;

	USpell* DownwardSpell;

	USpell* BlockingSpell;


	// Sets default values for this component's properties
	UCasterComponent();

protected:

	// Called when the game starts
	virtual void BeginPlay() override;

	void GiveSpellAbility(USpell* Spell);

	void RemoveSpellAbility(USpell* Spell);

public:	

	virtual void BeginControl_Implementation(const FBeginControlPayload& Payload) override;

	virtual void EndControl_Implementation() override;

	virtual void PrimaryPressed_Implementation() override;

	virtual void PrimaryReleased_Implementation() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Caster")
	void SetSpell(USpell* Spell);

	UFUNCTION(BlueprintCallable, Category = "Caster")
	void RemoveSpell(ESpellSlot Slot);

	UFUNCTION(BlueprintCallable, Category = "Caster")
	USpell* GetSpell(ESpellSlot Slot);

};
