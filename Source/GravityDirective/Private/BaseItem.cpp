// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseItem.h"

// Sets default values
ABaseItem::ABaseItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DisplayMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Display Mesh"));
	NameDisplay = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Name Display"));
	DetailDisplay = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Detail Display"));
	Hitbox = CreateDefaultSubobject<UCapsuleCollisionComponent>(TEXT("Hitbox"));
	FacePlayerComponent = CreateDefaultSubobject<UFacePlayer>(TEXT("Face Player"));
}

void ABaseItem::InitProperties(UStaticMesh* Mesh, FText Name, FText Description)
{
	DisplayMesh->SetStaticMesh(Mesh);
	NameDisplay->SetText(Name);
	DetailDisplay->SetText(Description);
}

// Called when the game starts or when spawned
void ABaseItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

