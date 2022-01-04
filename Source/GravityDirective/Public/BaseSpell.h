// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpellSlot.h"
#include "SpellTargetingSystem.h"
#include "SpellActivation.h"
#include "BaseSpell.generated.h"

/**
 * 
 */
UCLASS()
class GRAVITYDIRECTIVE_API UBaseSpell : public UObject
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(VisibleAnywhere, Category = "Spell")
	ESpellSlot SpellSlot;

	UPROPERTY(VisibleAnywhere, Category = "Spell")
	int32 Level;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
	USpellActivation* Activation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
	USpellTargetingSystem* TargetingSystem;

protected:


public:

	UBaseSpell();
};
