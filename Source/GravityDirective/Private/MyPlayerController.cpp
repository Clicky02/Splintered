// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"

void AMyPlayerController::GrabLeft()
{

}

void AMyPlayerController::GrabRight()
{
}

void AMyPlayerController::UseLeft()
{
}

void AMyPlayerController::UseRight()
{
}

void AMyPlayerController::TESTDEBUG()
{
	UE_LOG(LogTemp, Warning, TEXT("I just started running"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Screen Message"));
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (InputComponent)
	{
		InputComponent->BindAction("GrabLeft", IE_Pressed, this, &AMyPlayerController::GrabLeft);
		InputComponent->BindAction("AButton", IE_Pressed, this, &AMyPlayerController::TESTDEBUG);
	}
}

