
#pragma once

UENUM(BlueprintType)
enum class ESpellSlot: uint8
{
	None UMETA(DisplayName = "None"),
	Primary UMETA(DisplayName = "Primary"),
	Upward UMETA(DisplayName = "Upward"),
	Downward UMETA(DisplayName = "Downward"),
	Block UMETA(DisplayName = "Block"),
};