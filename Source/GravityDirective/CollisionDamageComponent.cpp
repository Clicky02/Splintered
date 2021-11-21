// Fill out your copyright notice in the Description page of Project Settings.


#include "CollisionDamageComponent.h"
#include <GravityDirective/HealthComponent.h>

// Sets default values for this component's properties
UCollisionDamageComponent::UCollisionDamageComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	UE_LOG(LogTemp, Warning, TEXT("start"));
	// ...
}


// Called when the game starts
void UCollisionDamageComponent::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("PLAY"));

}


// Called every frame
void UCollisionDamageComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UCollisionDamageComponent::Grab(UPrimitiveComponent* SimObject)
{

	if (bIsOnHit)
	{
		SimObject->OnComponentHit.AddDynamic(this, &UCollisionDamageComponent::OnCollide);
		SimObject->OnComponentBeginOverlap.AddDynamic(this, &UCollisionDamageComponent::OnOverlapBegin);
	}
	else
	{
		SimObject->OnComponentHit.AddDynamic(this, &UCollisionDamageComponent::OnCollide);
		SimObject->OnComponentBeginOverlap.AddDynamic(this, &UCollisionDamageComponent::OnOverlapBegin);
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

void UCollisionDamageComponent::Drop()
{

	if (bIsOnHit)
	{
		SimulatedObject->OnComponentHit.RemoveDynamic(this, &UCollisionDamageComponent::OnCollide);
		SimulatedObject->OnComponentBeginOverlap.RemoveDynamic(this, &UCollisionDamageComponent::OnOverlapBegin);
	}
	else
	{
		SimulatedObject->OnComponentHit.RemoveDynamic(this, &UCollisionDamageComponent::OnCollide);
		SimulatedObject->OnComponentBeginOverlap.RemoveDynamic(this, &UCollisionDamageComponent::OnOverlapBegin);
	}
	
	SimulatedObject = nullptr;
}


void UCollisionDamageComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
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
void UCollisionDamageComponent::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{
}
*/

void UCollisionDamageComponent::OnCollide(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

	UHealthComponent* enemyHealth = OtherActor->FindComponentByClass<UHealthComponent>();

	if (enemyHealth != nullptr) {

		enemyHealth->Damage(Damage);

		UStaticMeshComponent* mesh = OtherActor->FindComponentByClass<UStaticMeshComponent>();

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("COLL"));

		if (mesh != nullptr)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, (Hit.ImpactNormal *  -Knockback).ToString());
			mesh->AddForce(Hit.ImpactNormal *  -Knockback);
		}

	}
}




