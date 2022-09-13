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
	VRCameraComponent->SetupAttachment(CameraRig);

	LeftHandMotionControllerComponent = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("Motion Controller Left"));
	LeftHandMotionControllerComponent->SetupAttachment(CameraRig);

	LeftHandPosition = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Left Hand Position"));
	LeftHandPosition->SetupAttachment(LeftHandMotionControllerComponent);

	LeftHandSkeletalMesh =  CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Left Hand Skeletal Mesh"));
	LeftHandSkeletalMesh->SetupAttachment(LeftHandMotionControllerComponent);;

	RightHandMotionControllerComponent = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("Motion Controller Right"));
	RightHandMotionControllerComponent->SetupAttachment(CameraRig);

	RightHandPosition = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Right Hand Position"));
	RightHandPosition->SetupAttachment(RightHandMotionControllerComponent);

	RightHandMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Right Hand Mesh"));
	RightHandMesh->SetupAttachment(RightHandMotionControllerComponent);

	HipAttachRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Hip Attach Point"));
	HipAttachRoot->SetupAttachment(CameraRig);

	HipAttachPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Hip Attach Root"));
	HipAttachPoint->SetupAttachment(HipAttachRoot);
}

// Called when the game starts or when spawned
void ABaseVRPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

FVector ABaseVRPawn::GetCameraPosition()
{
	return VRCameraComponent->GetComponentLocation();
}

// Called every frame
void ABaseVRPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FRotator Rotation = VRCameraComponent->GetRelativeRotation();
	Rotation.Pitch = 0;
	Rotation.Roll = 0;

	HipAttachRoot->SetRelativeLocationAndRotation(VRCameraComponent->GetRelativeLocation(), Rotation);
}

// Called to bind functionality to input
void ABaseVRPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseVRPawn::AttachToHip(AActor* AttachActor)
{
	AttachActor->AttachToComponent(HipAttachPoint, FAttachmentTransformRules::SnapToTargetIncludingScale);
	HipAttachedActor = AttachActor;
}

void ABaseVRPawn::UnattachHipActor()
{
	HipAttachedActor->DetachRootComponentFromParent(true);
	HipAttachedActor = nullptr;
}

