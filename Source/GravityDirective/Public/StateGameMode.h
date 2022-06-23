// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include <GravityDirective/Public/GameModeState.h>
#include "StateGameMode.generated.h"

/**
 * 
 */
UCLASS()
class GRAVITYDIRECTIVE_API AStateGameMode : public AGameModeBase
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UGameModeState* StartingState;
	UGameModeState* CurrentState;
public:
	// Sets default values for this actor's properties
	AStateGameMode();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SetState(UGameModeState* NewState);
};
