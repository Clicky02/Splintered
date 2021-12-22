// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseSpell.h"
#include "SpellSlot.h"
#include "AbilitySystemComponent.h"
#include "Spell.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, ClassGroup = (Custom))
class GRAVITYDIRECTIVE_API USpell: public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
	ESpellSlot SpellSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
	TSubclassOf<UBaseSpell> SpellType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
	int32 Level;

	FGameplayAbilitySpecHandle SpellSpecHandle;

	UFUNCTION(BlueprintCallable, Category = "Spell")
	void Init(ESpellSlot IntialSpellSlot, TSubclassOf<UBaseSpell> IntialSpellType, int32 IntialLevel);

	UFUNCTION(BlueprintCallable, Category = "Caster")
	static USpell* CreateSpell(ESpellSlot IntialSpellSlot, TSubclassOf<UBaseSpell> IntialSpellType, int32 IntialLevel, UObject* JustPutThis);
};
