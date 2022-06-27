// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SpellTargetingSystem.generated.h"

USTRUCT(BlueprintType)
struct FTargetingActivatePayload
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* Wielder;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCasterComponent* CasterComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* CasterActor;
	
};


/**
 * 
 */
UCLASS(Blueprintable)
class GRAVITYDIRECTIVE_API USpellTargetingSystem : public UObject
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting")
	bool bIsPrimed = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting")
	bool bUsesDirectionTarget = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting")
	bool bUsesActorTarget = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting")
	bool bUsesLocationTarget = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting")
	class UBaseSpell* Spell;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting")
	AActor* Wielder;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting")
	class UCasterComponent* CasterComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting")
	AActor* CasterActor;

protected:

	UWorld* GetWorld() const;

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Targeting")
	void Init(class UBaseSpell* SpellInstance);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Targeting")
	void Activate(const FTargetingActivatePayload& Payload);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Targeting")
	void StartTargeting();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Targeting")
	void TickTargeting(float DeltaTime);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Targeting")
	void EndTargeting();


	UFUNCTION(BlueprintCallable, Category = "Targeting")
	bool UsesDirectionTarget();

	UFUNCTION(BlueprintCallable, Category = "Targeting")
	bool UsesLocationTarget();

	UFUNCTION(BlueprintCallable, Category = "Targeting")
	bool UsesActorTarget();


	UFUNCTION(BlueprintImplementableEvent, Category = "Targeting")
	FVector GetDirectionTarget();

	UFUNCTION(BlueprintImplementableEvent, Category = "Targeting")
	void GetLocationTarget(TArray<FVector>& Result);

	UFUNCTION(BlueprintImplementableEvent, Category = "Targeting")
	void GetActorTarget(TArray<AActor*>& Result);
};
