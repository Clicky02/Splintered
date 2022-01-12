// Fill out your copyright notice in the Description page of Project Settings.


#include "CollisionDamageComponent.h"
#include "StatsComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UCollisionDamageComponent::UCollisionDamageComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	// ...
}


// Called when the game starts
void UCollisionDamageComponent::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void UCollisionDamageComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UCollisionDamageComponent::Start(UPrimitiveComponent* SimObject)
{
	if (bIsOnHit)
	{
		SimObject->OnComponentHit.AddDynamic(this, &UCollisionDamageComponent::OnCollide);
	}
	else
	{
		SimObject->OnComponentBeginOverlap.AddDynamic(this, &UCollisionDamageComponent::OnOverlapBegin);
	}
	
	SimulatedObject = SimObject;

}

void UCollisionDamageComponent::End()
{

	if (bIsOnHit)
	{
		SimulatedObject->OnComponentHit.RemoveDynamic(this, &UCollisionDamageComponent::OnCollide);
	}
	else
	{
		SimulatedObject->OnComponentBeginOverlap.RemoveDynamic(this, &UCollisionDamageComponent::OnOverlapBegin);
	}
	
	SimulatedObject = nullptr;
}


void UCollisionDamageComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != this->GetOwner()) 
	{
		UStatsComponent* enemyStats = OtherActor->FindComponentByClass<UStatsComponent>();

		float currentTime = UGameplayStatics::GetRealTimeSeconds(GetWorld());

		if (enemyStats != nullptr && currentTime - LastAttackTime > MinTimeBetweenDamage)
		{

			enemyStats->Damage(Damage);
			LastAttackTime = currentTime;

		}
	}
}

/*
void UCollisionDamageComponent::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{
}
*/

void UCollisionDamageComponent::OnCollide(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor != this->GetOwner())
	{
		UStatsComponent* enemyStats = OtherActor->FindComponentByClass<UStatsComponent>();

		float currentTime = UGameplayStatics::GetRealTimeSeconds(GetWorld());

		if (enemyStats != nullptr && currentTime - LastAttackTime > MinTimeBetweenDamage) {

			enemyStats->Damage(Damage);
			LastAttackTime = currentTime;

			UStaticMeshComponent* mesh = OtherActor->FindComponentByClass<UStaticMeshComponent>();


			if (mesh != nullptr)
			{
				mesh->AddForce(Hit.ImpactNormal * -Knockback);
			}

		}
	}
}




