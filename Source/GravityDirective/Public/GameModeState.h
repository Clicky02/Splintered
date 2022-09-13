// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameModeState.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FTickSignature, float, DeltaTime);
DECLARE_DYNAMIC_DELEGATE(FOnStartSignature);
DECLARE_DYNAMIC_DELEGATE(FOnEndSignature);

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class GRAVITYDIRECTIVE_API UGameModeState : public UObject
{
	GENERATED_BODY()



private:
	bool bIsActive = false;

	FTickSignature Tick;
	FOnStartSignature OnStart;
	FOnEndSignature OnEnd;

public:
	void Init(FTickSignature TickFunc, FOnStartSignature OnStartFunc, FOnEndSignature OnEndFunc);
	void Init(FOnStartSignature OnStartFunc, FOnEndSignature OnEndFunc);
	void StartState();
	void TickState(float DeltaTime);
	void EndState();

	UFUNCTION(BlueprintCallable, Category = "Helper")
	static UGameModeState* CreateGameModeSate(FTickSignature TickFunc, FOnStartSignature OnStartFunc, FOnEndSignature OnEndFunc);

	UFUNCTION(BlueprintCallable, Category = "Helper")
	static UGameModeState* CreateBasicGameModeState(FOnStartSignature OnStartFunc, FOnEndSignature OnEndFunc);
};
