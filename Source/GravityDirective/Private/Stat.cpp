// Fill out your copyright notice in the Description page of Project Settings.


#include "Stat.h"

void UStat::Set(float NewValue)
{
	float OldValue = Value;

	Value = NewValue;

	if (bIsLimited)
	{
		if (Value < MinValue) 
		{
			Value = MinValue;
		}
		else if (Value > MaxValue)
		{
			Value = MaxValue;
		}
	}

	FOnStatChangePayload Payload;
	Payload.StatObject = this;
	Payload.OldValue = OldValue;

	OnStatChange.Broadcast(Payload);
}

void UStat::Add(float Amount)
{
	Set(Value + Amount);
}