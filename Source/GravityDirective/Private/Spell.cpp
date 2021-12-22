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
	UE_LOG(LogTemp, Warning, TEXT("------------------------------"));
	UE_LOG(LogTemp, Warning, TEXT("%d"), IntialSpellSlot);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *(IntialSpellType.GetDefaultObject()->GetFName().ToString()));
	UE_LOG(LogTemp, Warning, TEXT("%d"), IntialLevel);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *(JustPutThis->GetFName().ToString()));

	USpell* NewSpell = NewObject<USpell>(JustPutThis, USpell::StaticClass());
	NewSpell->Init(IntialSpellSlot, IntialSpellType, IntialLevel);

	UE_LOG(LogTemp, Warning, TEXT("-------------2-----------------"));
	UE_LOG(LogTemp, Warning, TEXT("%s"), *(NewSpell->GetFName().ToString()));
	UE_LOG(LogTemp, Warning, TEXT("%d"), NewSpell->SpellSlot);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *(NewSpell->SpellType.GetDefaultObject()->GetFName().ToString()));
	UE_LOG(LogTemp, Warning, TEXT("%d"), NewSpell->Level);

	return NewSpell;
}