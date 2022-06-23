// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseItem.h"

// Sets default values
ABaseItem::ABaseItem()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	DisplayMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Display Mesh"));
	DisplayMesh->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);

	NameDisplay = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Name Display"));
	NameDisplay->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);

	DetailDisplay = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Detail Display"));
	DetailDisplay->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);

	Hitbox = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Hitbox"));
	Hitbox->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);

	FacePlayerComponent = CreateDefaultSubobject<UFacePlayer>(TEXT("Face Player"));
}

void ABaseItem::InitProperties(UStaticMesh* Mesh, FText Name, FText Description)
{
	DisplayMesh->SetStaticMesh(Mesh);
	NameDisplay->SetText(Name);
	DetailDisplay->SetText(Description);
}

void ABaseItem::InitPropertiesAndMeshRotation(UStaticMesh* Mesh, FRotator MeshRotation, FText Name, FText Description)
{
	InitProperties(Mesh, Name, Description);
	DisplayMesh->SetRelativeRotation(MeshRotation);
}


