// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseVRPawn.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "MotionControllerComponent.h"

// Sets default values
ABaseVRPawn::ABaseVRPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraRig = CreateDefaultSubobject<USceneComponent>(TEXT("Camera Rig"));

	VRCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("VR Camera"));
	VRCameraComponent->AttachToComponent(CameraRig, FAttachmentTransformRules::KeepRelativeTransform);

	LeftHandMotionControllerComponent = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("Motion Controller Left"));
	LeftHandMotionControllerComponent->AttachToComponent(CameraRig, FAttachmentTransformRules::KeepRelativeTransform);

	LeftHandPosition = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Left Hand Position"));
	LeftHandPosition->AttachToComponent(LeftHandMotionControllerComponent, FAttachmentTransformRules::KeepRelativeTransform);

	LeftHandMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Left Hand Mesh"));
	LeftHandMesh->AttachToComponent(LeftHandMotionControllerComponent, FAttachmentTransformRules::KeepWorldTransform);

	RightHandMotionControllerComponent = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("Motion Controller Right"));
	RightHandMotionControllerComponent->AttachToComponent(CameraRig, FAttachmentTransformRules::KeepRelativeTransform);

	RightHandPosition = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Right Hand Position"));
	RightHandPosition->AttachToComponent(RightHandMotionControllerComponent, FAttachmentTransformRules::KeepRelativeTransform);

	RightHandMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Right Hand Mesh"));
	RightHandMesh->AttachToComponent(RightHandMotionControllerComponent, FAttachmentTransformRules::KeepWorldTransform);

}

// Called when the game starts or when spawned
void ABaseVRPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseVRPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseVRPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

