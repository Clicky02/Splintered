// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeComponent.h"
#include <GravityDirective/HealthComponent.h>

// Sets default values for this component's properties
UMeleeComponent::UMeleeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	UE_LOG(LogTemp, Warning, TEXT("start"));
	// ...
}


// Called when the game starts
void UMeleeComponent::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("PLAY"));

}


// Called every frame
void UMeleeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UMeleeComponent::GrabMeleeComponent(UPrimitiveComponent* SimObject)
{

	if (bIsOnHit)
	{
		SimObject->OnComponentHit.AddDynamic(this, &UMeleeComponent::OnCollide);
		SimObject->OnComponentBeginOverlap.AddDynamic(this, &UMeleeComponent::OnOverlapBegin);
	}
	else
	{
		SimObject->OnComponentHit.AddDynamic(this, &UMeleeComponent::OnCollide);
		SimObject->OnComponentBeginOverlap.AddDynamic(this, &UMeleeComponent::OnOverlapBegin);
	}
	
	SimulatedObject = SimObject;

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Setup!"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Setup"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Setup"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Setup"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Setup"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Setup"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Setup"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Setup"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Setup"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Setup"));
}

void UMeleeComponent::DropMeleeComponent()
{

	if (bIsOnHit)
	{
		SimulatedObject->OnComponentHit.RemoveDynamic(this, &UMeleeComponent::OnCollide);
		SimulatedObject->OnComponentBeginOverlap.RemoveDynamic(this, &UMeleeComponent::OnOverlapBegin);
	}
	else
	{
		SimulatedObject->OnComponentHit.RemoveDynamic(this, &UMeleeComponent::OnCollide);
		SimulatedObject->OnComponentBeginOverlap.RemoveDynamic(this, &UMeleeComponent::OnOverlapBegin);
	}
	
	SimulatedObject = nullptr;
}


void UMeleeComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("COLLIDERS"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("COLLIDERS"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("COLLIDERS"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("COLLIDERS"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("COLLIDERS"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("COLLIDERS"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("COLLIDERS"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("COLLIDERS"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("COLLIDERS"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("COLLIDERS"));
}

/*
void UMeleeComponent::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{
}
*/

void UMeleeComponent::OnCollide(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

	OtherActor->TakeDamage(Damage, FDamageEvent(), nullptr, GetOwner());


	UStaticMeshComponent* mesh = OtherActor->FindComponentByClass<UStaticMeshComponent>();

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("COLL"));

	if (mesh != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, (Hit.ImpactNormal *  -Knockback).ToString());
		mesh->AddForce(Hit.ImpactNormal *  -Knockback);
	}
}




