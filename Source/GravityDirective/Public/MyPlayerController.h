// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GRAVITYDIRECTIVE_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

	public:
		// ~Overrides: APlayerController
		virtual void SetupInputComponent() override;
		// Declare your callbacks here
		// MoveForward(); MoveLateral(); Jump();
		void GrabLeft();
		void GrabRight();
		void UseLeft();
		void UseRight();
		void TESTDEBUG();
};


