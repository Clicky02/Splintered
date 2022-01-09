// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Stat.generated.h"

USTRUCT(BlueprintType)
struct FOnStatChangePayload
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat Change")
	UStat* StatObject;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat Change")
	float OldValue;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStatChange, const FOnStatChangePayload&, Payload);

/**
 * 
 */
UCLASS()
class GRAVITYDIRECTIVE_API UStat : public UObject
{
	GENERATED_BODY()

public: 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	FString Name = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float MaxValue = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float MinValue = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float Value = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float RateOfChange = 0.0f;

	UPROPERTY(BlueprintAssignable, Category = "Stats")
	FOnStatChange OnStatChange;

	// Whether this stat should use the min and max values
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	bool bIsLimited = false;

	UFUNCTION(BlueprintCallable, Category = "Stats")
	void Set(float NewValue);

	UFUNCTION(BlueprintCallable, Category = "Stats")
	void Add(float Amount);


};
