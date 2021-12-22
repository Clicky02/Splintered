// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseSpawnComponent.h"
#include "HeldInteractable.h"
#include "GunComponent.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GRAVITYDIRECTIVE_API UGunComponent : public UBaseSpawnComponent, public IHeldInteractable
{
	GENERATED_BODY()

public:
	virtual void PrimaryPressed_Implementation() override;
};
