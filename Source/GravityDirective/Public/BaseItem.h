// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"
#include <Runtime/Engine/Classes/Components/CapsuleComponent.h>
#include "FacePlayer.h"
#include <GravityDirective/Public/BaseVRPawn.h>
#include "BaseItem.generated.h"



USTRUCT(BlueprintType)
struct FOnItemPickupPayload
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat Change")
	ABaseItem* Item;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat Change")
	ABaseVRPawn* Pawn;

};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemPickup, const FOnItemPickupPayload&, Payload);


UCLASS()
class GRAVITYDIRECTIVE_API ABaseItem : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* Root;

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

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnItemPickup OnItemPickup;
	
public:	
	// Sets default values for this actor's properties
	ABaseItem();
	

protected:
	UFUNCTION(BlueprintCallable)
	void InitProperties(UStaticMesh* Mesh, FText Name, FText Description);

	UFUNCTION(BlueprintCallable)
	void InitPropertiesAndMeshRotation(UStaticMesh* Mesh, FRotator MeshRotation, FText Name, FText Description);

};
