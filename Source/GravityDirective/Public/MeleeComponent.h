// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MeleeComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GRAVITYDIRECTIVE_API UMeleeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UPrimitiveComponent* SimulatedObject;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Collider")
	bool bIsOnHit = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	float Damage = 10;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	float Knockback = 1;



	// Sets default values for this component's properties
	UMeleeComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	UFUNCTION(BlueprintCallable)
	virtual void GrabMeleeComponent(UPrimitiveComponent* SimulatedObject);

	UFUNCTION(BlueprintCallable)
	virtual void DropMeleeComponent();

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