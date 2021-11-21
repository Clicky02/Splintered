// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HeldInteractable.generated.h"

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
	void PrimaryAxis(float value);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Control Functions")
	void PrimaryPressed();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Control Functions")
	void PrimaryReleased();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Control Functions")
	void SecondaryAxis(float value);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Control Functions")
	void SecondaryPressed();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Control Functions")
	void GeneralPressed(int action);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Control Functions")
	void GeneralReleased(int action);
};
