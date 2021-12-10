// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GameAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class GRAVITYDIRECTIVE_API UGameAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:

	UGameAttributeSet();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UGameAttributeSet, Health);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UGameAttributeSet, Mana);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UGameAttributeSet, Armor);
	
};
