// Fill out your copyright notice in the Description page of Project Settings.


#include "Spell.h"

void USpell::Init(ESpellSlot IntialSpellSlot, TSubclassOf<UBaseSpell> IntialSpellType, int32 IntialLevel)
{
	this->SpellSlot = IntialSpellSlot;
	this->SpellType = IntialSpellType;
	this->Level = IntialLevel;
}

USpell* USpell::CreateSpell(ESpellSlot IntialSpellSlot, TSubclassOf<UBaseSpell> IntialSpellType, int32 IntialLevel, UObject* JustPutThis)
{
	USpell* NewSpell = NewObject<USpell>(JustPutThis, USpell::StaticClass());
	NewSpell->Init(IntialSpellSlot, IntialSpellType, IntialLevel);

	return NewSpell;
}