// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EStatVariant : uint8
{
	None UMETA(DisplayName = "None"),
	Health UMETA(DisplayName = "Health"),
	Mana UMETA(DisplayName = "Mana"),
	Armor UMETA(DisplayName = "Armor"),
	OutgoingDamageModifier UMETA(DisplayName = "OutgoingDamageModifier"),
	IncomingDamageModifier UMETA(DisplayName = "IncomingDamageModifier"),
};
