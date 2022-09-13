// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseItem.h"

// Sets default values
ABaseItem::ABaseItem()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	DisplayMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Display Mesh"));
	DisplayMesh->SetupAttachment(Root);

	NameDisplay = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Name Display"));
	NameDisplay->SetupAttachment(Root);

	DetailDisplay = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Detail Display"));
	DetailDisplay->SetupAttachment(Root);

	Hitbox = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Hitbox"));
	Hitbox->SetupAttachment(Root);

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


