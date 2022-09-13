// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseMapManager.h"


ABaseMapManager* ABaseMapManager::Main = nullptr;

// Sets default values
ABaseMapManager::ABaseMapManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABaseMapManager::BeginPlay()
{
	Super::BeginPlay();

	Main = this;
	
	if (WaveInfoType != nullptr)
	{
		WaveInfo = NewObject<UWaveInformation>(this, WaveInfoType);
	}
}

// Called every frame
void ABaseMapManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

