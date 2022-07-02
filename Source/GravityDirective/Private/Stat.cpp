// Fill out your copyright notice in the Description page of Project Settings.


#include "Stat.h"

#define MIN_RATE_OF_CHANGE 0.00005

void UStat::ModifyValues(float* ValuePointer, float* BaseValuePointer, EStatModifierDurationType DurationType, EStatModificationType ModificationType, float ModifierValue)
{
	if (DurationType == EStatModifierDurationType::Instant)
	{
		switch (ModificationType)
		{
		case EStatModificationType::Additive:
			*BaseValuePointer += ModifierValue;
			*ValuePointer += ModifierValue;
			break;
		case EStatModificationType::Multiplicitive:
			*BaseValuePointer *= ModifierValue;
			*ValuePointer *= ModifierValue;
			break;
		case EStatModificationType::Override:
			*BaseValuePointer = ModifierValue;
			*ValuePointer = ModifierValue;
			break;
		}
	}
	else if (DurationType == EStatModifierDurationType::Lasting || DurationType == EStatModifierDurationType::Infinite)
	{
		switch (ModificationType)
		{
		case EStatModificationType::Additive:
			*BaseValuePointer += ModifierValue;
			break;
		case EStatModificationType::Multiplicitive:
			*BaseValuePointer *= ModifierValue;
			break;
		case EStatModificationType::Override:
			*BaseValuePointer = ModifierValue;
			break;
		}
	}
}

void UStat::RefreshValues()
{
	MaxValue = BaseMaxValue;
	MinValue = BaseMinValue;
	Value = BaseValue;
	RateOfChange = BaseRateOfChange;

	ApplyModifiersToMaxValue();
	ApplyModifiersToMinValue();
	ApplyModifiersToValue();
	ApplyModifiersToRateOfChange();
}

void UStat::ApplyModifiersToValue()
{
	CheckValid();

	for (int32 i = 0; i < StatModifiers.Num(); i++)
	{
		auto Modifier = StatModifiers[i];

		if (Modifier.bShouldModifyValue)
		{
			ModifyValues(&Value, &BaseValue, Modifier.DurationType, Modifier.ModificationType, Modifier.ValueModifier);
		}

		CheckValid();
	}
}

void UStat::ApplyModifiersToMaxValue()
{
	if (bHasMaxValue) 
	{

		for (int32 i = 0; i < StatModifiers.Num(); i++)
		{
			auto Modifier = StatModifiers[i];

			if (Modifier.bShouldModifyMaxValue)
			{
				ModifyValues(&MaxValue, &BaseMaxValue, Modifier.DurationType, Modifier.ModificationType, Modifier.MaxValueModifier);
			}

			CheckValid();
		}
	}
}

void UStat::ApplyModifiersToMinValue()
{
	if (bHasMinValue)
	{

		for (int32 i = 0; i < StatModifiers.Num(); i++)
		{
			auto Modifier = StatModifiers[i];

			if (Modifier.bShouldModifyMinValue)
			{
				ModifyValues(&MinValue, &BaseMinValue, Modifier.DurationType, Modifier.ModificationType, Modifier.MinValueModifier);
			}

			CheckValid();
		}
	}
}

void UStat::ApplyModifiersToRateOfChange()
{

	for (int32 i = 0; i < StatModifiers.Num(); i++)
	{
		auto Modifier = StatModifiers[i];

		if (Modifier.bShouldModifyRateOfChange)
		{
			ModifyValues(&RateOfChange, &BaseRateOfChange, Modifier.DurationType, Modifier.ModificationType, Modifier.RateOfChangeModifier);
		}
	}

}

void UStat::CheckValid()
{
	if (bHasMinValue && bHasMaxValue && MinValue > MaxValue)
	{
		MaxValue = MinValue;
	}

	if (bHasMinValue && Value < MinValue)
	{
		Value = MinValue;
	}

	if (bHasMaxValue && Value > MaxValue)
	{
		Value = MaxValue;
	}

	if (bHasMinValue && bHasMaxValue && BaseMinValue > BaseMaxValue)
	{
		BaseMaxValue = BaseMinValue;
	}

	if (bHasMinValue && Value < BaseMinValue)
	{
		BaseValue = BaseMinValue;
	}

	if (bHasMaxValue && Value > BaseMaxValue)
	{
		BaseValue = BaseMaxValue;
	}
}

UStat::UStat()
{
	MaxValue = BaseMaxValue;
	MinValue = BaseMinValue;
	Value = BaseValue;
	RateOfChange = BaseRateOfChange;
}

EStatVariant UStat::GetStatVariant()
{
	return Type;
}

int32 UStat::ApplyStatModifier(const FStatModifier& NewModifier)
{
	int32 Id = FMath::RandRange(0, INT_MAX);

	FStatModifier Modifier = NewModifier;

	Modifier.Id = Id;

	if (Modifier.DurationType == EStatModifierDurationType::Lasting || Modifier.DurationType == EStatModifierDurationType::Infinite)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("5!"));
		for (int32 i = 0; i <= StatModifiers.Num(); i++)
		{
			if (i == StatModifiers.Num())
			{
				StatModifiers.Add(Modifier);
				break;
			}
			else if (Modifier.Priority >= StatModifiers[i].Priority)
			{
				StatModifiers.Insert(Modifier, i);
				break;
			}
		}
	}
	else if (Modifier.DurationType == EStatModifierDurationType::Instant)
	{
		float OldValue = Value;

		if (Modifier.bShouldModifyMaxValue)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("1!"));
			MaxValue = BaseMaxValue;
			ModifyValues(&MaxValue, &BaseMaxValue, Modifier.DurationType, Modifier.ModificationType, Modifier.MaxValueModifier);
			ApplyModifiersToMaxValue();
		}

		if (Modifier.bShouldModifyMinValue)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("2!"));
			MinValue = BaseMinValue;
			ModifyValues(&MinValue, &BaseMinValue, Modifier.DurationType, Modifier.ModificationType, Modifier.MinValueModifier);
			ApplyModifiersToMinValue();
		}

		if (Modifier.bShouldModifyValue)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("3!"));
			Value = BaseValue;
			ModifyValues(&Value, &BaseValue, Modifier.DurationType, Modifier.ModificationType, Modifier.ValueModifier);
			ApplyModifiersToValue();

			FOnStatChangePayload Payload;
			Payload.StatObject = this;
			Payload.OldValue = OldValue;

			OnStatChange.Broadcast(Payload);
		}

		if (Modifier.bShouldModifyRateOfChange)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("4!"));
			RateOfChange = BaseRateOfChange;
			ModifyValues(&RateOfChange, &BaseRateOfChange, Modifier.DurationType, Modifier.ModificationType, Modifier.RateOfChangeModifier);
			ApplyModifiersToRateOfChange();
		}
	}
	
	FOnStatModifierAppliedPayload Payload;
	Payload.StatObject = this;
	Payload.Modifier = Modifier;

	OnStatModifierApplied.Broadcast(Payload);

	return Id;
}

UPARAM(ref) FStatModifier& UStat::GetStatModifier(int32 Id)
{
	return StatModifiers[Id];
}

void UStat::RemoveStatModifier(int32 Id)
{
	for (int32 i = 0; i < StatModifiers.Num(); i++)
	{
		if (StatModifiers[i].Id == Id)
		{
			StatModifiers.RemoveAt(i);
			RefreshValues();
			break;
		}
	}
	
}

float UStat::GetMaxValue()
{
	return MaxValue;
}

float UStat::GetBaseMaxValue()
{
	return BaseMaxValue;
}

float UStat::GetMinValue()
{
	return MinValue;
}

float UStat::GetBaseMinValue()
{
	return BaseMinValue;
}

float UStat::GetValue()
{
	return Value;
}

float UStat::GetBaseValue()
{
	return BaseValue;
}

float UStat::GetRateOfChange()
{
	return RateOfChange;
}

float UStat::GetBaseRateOfChange()
{
	return BaseRateOfChange;
}

bool UStat::IsActive()
{
	return bIsActive;
}

void UStat::Set(float NewValue)
{
	if (NewValue > MaxValue) NewValue = MaxValue;
	else if (NewValue < MinValue) NewValue = MinValue;
	float OldValue = Value;
	BaseValue = NewValue;
	Value = BaseValue;

	ApplyModifiersToValue();

	FOnStatChangePayload Payload;
	Payload.StatObject = this;
	Payload.OldValue = OldValue;

	OnStatChange.Broadcast(Payload);
}

void UStat::Add(float Amount)
{
	Set(BaseValue + Amount);
}

void UStat::Tick(float DeltaTime)
{
	TimeSinceLastTick += DeltaTime;

	if (TimeSinceLastTick > MinTimeBetweenTick)
	{
		if (RateOfChange > MIN_RATE_OF_CHANGE || RateOfChange < -MIN_RATE_OF_CHANGE)
		{
			Add(RateOfChange * TimeSinceLastTick);
		}

		TimeSinceLastTick = 0;
	}

	for (int32 i = 0; i < StatModifiers.Num(); i++)
	{
		if (StatModifiers[i].DurationType != EStatModifierDurationType::Infinite)
		{
			StatModifiers[i].Duration -= DeltaTime;

			if (StatModifiers[i].Duration <= 0)
			{
				StatModifiers.RemoveAt(i);
				RefreshValues();
				i--;
			}
		}

	}
}

bool UStat::IsTickable() const
{
	return true;
}

bool UStat::IsTickableInEditor() const
{
	return false;
}

bool UStat::IsTickableWhenPaused() const
{
	return false;
}

TStatId UStat::GetStatId() const
{
	return TStatId();
}

UWorld* UStat::GetWorld() const
{
	if (GetOuter() == nullptr)
	{
		return nullptr;
	}

	// Special case for behavior tree nodes in the editor
	if (Cast<UPackage>(GetOuter()) != nullptr)
	{
		// GetOuter should return a UPackage and its Outer is a UWorld
		return Cast<UWorld>(GetOuter()->GetOuter());
	}

	// In all other cases...
	return GetOuter()->GetWorld();
}