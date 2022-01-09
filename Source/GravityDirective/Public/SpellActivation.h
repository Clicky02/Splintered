// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SpellActivation.generated.h"

USTRUCT(BlueprintType)
struct FSpellActivationActivatePayload
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
class GRAVITYDIRECTIVE_API USpellActivation : public UObject
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell Activation")
	bool bIsPrimed = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell Activation")
	class UBaseSpell* Spell;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell Activation")
	AActor* Wielder;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell Activation")
	class UCasterComponent* CasterComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell Activation")
	AActor* CasterActor;

protected:

	UWorld* GetWorld() const;

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Spell Activation")
	void Init(class UBaseSpell* SpellInstance);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Spell Activation")
	void Activate(const FSpellActivationActivatePayload& Payload);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Spell Activation")
	void StartDetecting();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Spell Activation")
	void Tick();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Spell Activation")
	void EndDetecting();
	
};
