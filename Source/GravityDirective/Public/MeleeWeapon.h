// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "CollisionDamageComponent.h"
#include "MeleeWeapon.generated.h"


UCLASS(Blueprintable)
class GRAVITYDIRECTIVE_API AMeleeWeapon : public AWeapon
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMeleeWeapon();
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Test")
	class UCollisionDamageComponent* DamageComponent;

};
