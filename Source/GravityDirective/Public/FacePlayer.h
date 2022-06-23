// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FacePlayer.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GRAVITYDIRECTIVE_API UFacePlayer : public UActorComponent
{
	GENERATED_BODY()
		
protected:
	AActor* Target;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bUseZRotationOnly = true;

public:	
	// Sets default values for this component's properties
	UFacePlayer();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
