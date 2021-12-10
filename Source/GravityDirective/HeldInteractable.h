// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HeldInteractable.generated.h"

UENUM(BlueprintType)
enum class HandSide : uint8
{
  None      UMETA(DisplayName = "None"),
  Right      UMETA(DisplayName = "Right"),
  Left    UMETA(DisplayName = "Left"),
};

USTRUCT(BlueprintType)
struct FBeginControlPayload
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Control Functions")
	AActor* Player;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Control Functions")
	HandSide handSide;
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UHeldInteractable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GRAVITYDIRECTIVE_API IHeldInteractable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Control Functions")
	void BeginControl(const FBeginControlPayload& Payload);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Control Functions")
	void EndControl();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Control Functions")
	void PrimaryAxis(float Value);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Control Functions")
	void PrimaryPressed();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Control Functions")
	void PrimaryReleased();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Control Functions")
	void SecondaryAxis(float Value);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Control Functions")
	void SecondaryPressed();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Control Functions")
	void GeneralPressed(int Action);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Control Functions")
	void GeneralReleased(int Action);
};
