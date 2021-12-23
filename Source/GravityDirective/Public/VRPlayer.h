// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AbilitySystemInterface.h"
#include "PlayerAbilitySystemComponent.h"
#include "BaseAbility.h"
#include "VRPlayer.generated.h"

UCLASS()
class GRAVITYDIRECTIVE_API AVRPlayer : public APawn, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities)
    TArray<TSubclassOf<class UBaseAbility>> DefaultAbilities;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities)
    TSubclassOf<class UGameplayEffect> DefaultAttributeEffect;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Abilities", meta = (AllowPrivateAccess = "true"))
	class UPlayerAbilitySystemComponent* AbilitySystem;

	UPROPERTY()
	class UGameAttributeSet* Attributes;

	// Sets default values for this pawn's properties
	AVRPlayer();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual void InitializeAttributes();

	virtual void GiveDefaultAbilities();

	virtual void PossessedBy(AController* NewController) override;

};
