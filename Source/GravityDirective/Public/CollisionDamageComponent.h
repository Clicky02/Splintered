// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CollisionDamageComponent.generated.h"

USTRUCT(Blueprintable)
struct FOnHitPayload
{
	GENERATED_BODY()

	AActor* HitActor;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHit, const FOnHitPayload&, Payload);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GRAVITYDIRECTIVE_API UCollisionDamageComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UPrimitiveComponent* SimulatedObject;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Collider")
	bool bIsOnHit = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	float Damage = 10;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	float Knockback = 1;



	// Sets default values for this component's properties
	UCollisionDamageComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	UFUNCTION(BlueprintCallable)
	virtual void Grab(UPrimitiveComponent* SimulatedObject);

	UFUNCTION(BlueprintCallable)
	virtual void Drop();

protected:
	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/*
	UFUNCTION()
	virtual void OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor);
	*/

	UFUNCTION()
	virtual void OnCollide(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

		

		
};
