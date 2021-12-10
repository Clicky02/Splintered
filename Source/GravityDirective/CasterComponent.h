// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HeldInteractable.h"
#include "CasterComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GRAVITYDIRECTIVE_API UCasterComponent : public UActorComponent, public IHeldInteractable
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCasterComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	virtual void BeginControl_Implementation(const FBeginControlPayload& Payload) override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
