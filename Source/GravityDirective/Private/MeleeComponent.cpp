// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeComponent.h"
#include "HealthComponent.h"

// Sets default values for this component's properties
UMeleeComponent::UMeleeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UMeleeComponent::BeginPlay()
{
	Super::BeginPlay();
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

	if (mesh != nullptr)
	{
		mesh->AddForce(Hit.ImpactNormal *  -Knockback);
	}
}




