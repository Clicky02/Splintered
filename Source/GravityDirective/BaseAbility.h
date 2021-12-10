// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilityInputID.h"
#include "Abilities/GameplayAbility.h"
#include "BaseAbility.generated.h"

/**
 * 
 */
UCLASS()
class GRAVITYDIRECTIVE_API UBaseAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:

	UBaseAbility();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities)
    EAbilityInputID AbilityInputID = EAbilityInputID::None;

};
