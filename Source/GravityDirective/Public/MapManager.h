// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <BaseWaveSpawnLocation.h>
#include <ItemSpawnPoint.h>
#include <WaveInformation.h>
#include "Runtime/Engine/Classes/Engine/TextRenderActor.h"
#include <GravityDirective/Public/BaseTextDisplay.h>
#include "MapManager.generated.h"




UENUM(BlueprintType)
enum class GameModeType : uint8
{
	None = 0x0,
	Wave = 0x1
};


UCLASS()
class GRAVITYDIRECTIVE_API AMapManager : public AActor
{
	GENERATED_BODY()

public:
	static AMapManager* Main;

	UPROPERTY(EditAnywhere, meta = (Bitmask, BitmaskEnum = "GameModeType"), Category = "Map")
	uint32 SupportedGameModes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	TSubclassOf<UWaveInformation> WaveInfoType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	ABaseTextDisplay* MainTextDisplay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	TArray<ABaseWaveSpawnLocation*> WaveSpawnLocations;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	TArray<AItemSpawnPoint*> ItemSpawnLocations;

protected:
	UPROPERTY()
	UWaveInformation* WaveInfo;

public:	
	// Sets default values for this actor's properties
	AMapManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
