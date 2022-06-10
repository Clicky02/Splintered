// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseTextDisplay.h"

// Sets default values
ABaseTextDisplay::ABaseTextDisplay()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TextRenderer = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Text Renderer"));
}

// Called when the game starts or when spawned
void ABaseTextDisplay::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseTextDisplay::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

