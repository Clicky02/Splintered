// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <StatsComponent.h>
#include "BaseManaFlask.generated.h"

UCLASS(Blueprintable)
class GRAVITYDIRECTIVE_API ABaseManaFlask : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* Flask;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* FlaskFill;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	UStatsComponent* TargetStats;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float ManaInFlask = 0;

	bool IsPouring = false;
	bool Finished = false;

	UMaterialInstanceDynamic* FlaskMat;


public:	

	// Sets default values for this actor's properties
	ABaseManaFlask();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
		
	UFUNCTION(BlueprintImplementableEvent)
	void OnStartPouring();

	UFUNCTION(BlueprintImplementableEvent)
	void OnStopPouring();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void Init(UStatsComponent* InitialTargetStats);
};
