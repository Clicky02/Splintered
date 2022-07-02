// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseManaFlask.h"

// Sets default values
ABaseManaFlask::ABaseManaFlask()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Flask = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Flask"));

	FlaskFill = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FlaskFill"));
	FlaskFill->AttachToComponent(Flask, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void ABaseManaFlask::BeginPlay()
{
	Super::BeginPlay();

	FlaskMat = UMaterialInstanceDynamic::Create(FlaskFill->GetMaterial(0), this);
	FlaskFill->SetMaterial(0, FlaskMat);
}

// Called every frame
void ABaseManaFlask::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Flask->GetUpVector().Dot(FVector3d::DownVector) > 0.3f)
	{
		if (!IsPouring)
		{
			Finished = false;
			OnStartPouring();
			IsPouring = true;
		}

		if (!Finished)
		{
			float ManaToGain = DeltaTime * 20;
			if (ManaToGain > ManaInFlask)
			{
				ManaToGain = ManaInFlask;

				Finished = true;
				OnStopPouring();
			}
			ManaInFlask -= ManaToGain;
			TargetStats->Mana->Add(ManaToGain);
			FlaskMat->SetScalarParameterValue("PercentLeft", ManaInFlask / TargetStats->Mana->GetMaxValue());
		}
		
	}
	else
	{
		if (IsPouring)
		{
			Finished = false;
			IsPouring = false;
			OnStopPouring();
		}

		if (!Finished)
		{
			ManaInFlask += DeltaTime * TargetStats->Mana->GetRateOfChange() * 2;
			float MaxMana = TargetStats->Mana->GetMaxValue();
			if (ManaInFlask > MaxMana)
			{
				ManaInFlask = TargetStats->Mana->GetMaxValue();
			}
			FlaskMat->SetScalarParameterValue("PercentLeft", ManaInFlask / MaxMana);
		}
	}
}

void ABaseManaFlask::Init(UStatsComponent* InitialTargetStats)
{
	TargetStats = InitialTargetStats;
}

