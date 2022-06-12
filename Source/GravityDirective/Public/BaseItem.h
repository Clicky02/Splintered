// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Runtime/Engine/Classes/Engine/TextRenderActor.h>
#include <Runtime/Engine/Classes/Components/CapsuleComponent.h>
#include "FacePlayer.h"
#include "BaseItem.generated.h"


USTRUCT(BlueprintType)
struct FOnItemPickupPayload
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat Change")
	ABaseItem* Item;

};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemPickup, const FOnItemPickupPayload&, Payload);


UCLASS()
class GRAVITYDIRECTIVE_API ABaseItem : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* DisplayMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextRenderComponent* NameDisplay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextRenderComponent* DetailDisplay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCapsuleComponent* Hitbox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UFacePlayer* FacePlayerComponent;

	UPROPERTY(BlueprintAssignable)
	FOnItemPickup OnItemPickup;
	
public:	
	// Sets default values for this actor's properties
	ABaseItem();

protected:
	UFUNCTION(BlueprintCallable)
	void InitProperties(UStaticMesh* Mesh, FText Name, FText Description);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
