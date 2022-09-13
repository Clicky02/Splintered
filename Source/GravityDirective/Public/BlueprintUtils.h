// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include <GravityDirective/Public/BaseMapManager.h>
#include <GameModeState.h>
#include "StatModifier.h"
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

	UFUNCTION(BlueprintCallable, Category = "Helper")
	static ABaseMapManager* GetCurrentMapManagerBase();

	UFUNCTION(BlueprintCallable, Category = "Helper")
	static FString GetStatName(EStatVariant Stat);

	UFUNCTION(BlueprintCallable, Category = "Helper")
	static float Round(float in);

	UFUNCTION(BlueprintCallable, Category = "Helper")
	static bool IsOnSameTeam(int Team1, int Team2);

};
