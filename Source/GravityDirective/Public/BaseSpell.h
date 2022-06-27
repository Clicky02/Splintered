// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SpellSlot.h"
#include "SpellTargetingSystem.h"
#include "SpellActivation.h"
#include "BaseSpell.generated.h"


USTRUCT(BlueprintType)
struct FSpellActivatePayload
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
class GRAVITYDIRECTIVE_API UBaseSpell : public UObject
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
	FName Name = TEXT("Unnamed");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
	bool bIsPrimed = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
	bool bIsTargeting = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
	bool bIsCasting = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
	ESpellSlot SpellSlot = ESpellSlot::None;

	UPROPERTY(EditAnywhere, Category = "Spell")
	int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
	float ManaCost = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
	UStaticMesh* ItemDisplayMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
	AActor* Wielder;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
	class UCasterComponent* CasterComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
	AActor* CasterActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
	class UStatsComponent* StatsComponent;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
	USpellActivation* Activation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
	USpellTargetingSystem* TargetingSystem;

protected:

	UFUNCTION(BlueprintCallable)
	UWorld* GetWorld() const;

public:

	UBaseSpell();
	
	UFUNCTION(BlueprintCallable, Category = "Spell")
	ESpellSlot GetSpellSlot();

	UFUNCTION(BlueprintCallable, Category = "Spell")
	int32 GetSpellLevel();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Spell")
	void Init(int32 InitialLevel);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Spell")
	void Activate(const FSpellActivatePayload& Payload);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Spell")
	void Deactivate();

	UFUNCTION(BlueprintNativeEvent, Category = "Spell")
	void Tick(float DeltaTime);

	UFUNCTION(BlueprintCallable, Category = "Spell")
	void Prime();

	UFUNCTION(BlueprintCallable, Category = "Spell")
	void Unprime();

	UFUNCTION(BlueprintCallable, Category = "Spell")
	void StartTargeting();

	UFUNCTION(BlueprintCallable, Category = "Spell")
	void EndTargeting();

	UFUNCTION(BlueprintPure, Category = "Spell")
	FName GetName();

	UFUNCTION(BlueprintPure, Category = "Spell")
	UStaticMesh* GetItemDisplayMesh();

	UFUNCTION(BlueprintCallable, Category = "Spell")
	bool CastSpell();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Spell")
	void OnCastSpell();
};
