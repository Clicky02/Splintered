// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BlueprintUtils.generated.h"

/**
 * 
 */
UCLASS()
class GRAVITYDIRECTIVE_API UBlueprintUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public: 
	UFUNCTION(BlueprintCallable, Category = "Helper")
	static void SortByDistance(FVector Origin, TArray<AActor*> inArray, TArray<AActor*>& outArray);

	UFUNCTION(BlueprintCallable, Category = "Helper")
	static FVector GetLocation(AActor* Actor, bool bUseCamera);

	UFUNCTION(BlueprintCallable, Category = "Helper")
	static FVector GetVRPawnCenter(ABaseVRPawn* Pawn);
};
