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


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GRAVITYDIRECTIVE_API UCasterComponent : public UActorComponent, public IHeldInteractable
{
	GENERATED_BODY()
		

	bool bIsActivated = false;

	bool bIsPrimed = false;

	bool bIsCasting = false;

	ESpellSlot CastingSlot = ESpellSlot::None;

protected:

	AActor* Player;

	UStaticMeshComponent* ConnectedHand;

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
	void SetCasting(ESpellSlot SpellSlot, bool IsCasting);
};
