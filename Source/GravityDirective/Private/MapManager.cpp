// Fill out your copyright notice in the Description page of Project Settings.


#include "MapManager.h"


AMapManager* AMapManager::Main = nullptr;

// Sets default values
AMapManager::AMapManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMapManager::BeginPlay()
{
	Super::BeginPlay();

	Main = this;
	
	WaveInfo = NewObject<UWaveInformation>(this, WaveInfoType);
}

// Called every frame
void AMapManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

