// Fill out your copyright notice in the Description page of Project Settings.


#include "FacePlayer.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UFacePlayer::UFacePlayer()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFacePlayer::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UFacePlayer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!Target)
	{
		Target = Cast<AActor>(UGameplayStatics::GetPlayerCharacter(this, 0));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Screen Message"));
	}

	if (Target)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("------"));
		GetOwner()->SetActorRotation((Target->GetActorLocation() - GetOwner()->GetActorLocation()).Rotation());
	}
	// ...
}

