// Fill out your copyright notice in the Description page of Project Settings.


#include "BlueprintUtils.h"

void UBlueprintUtils::SortByDistance(FVector Origin, TArray<AActor*> inArray, TArray<AActor*>& outArray)
{
	inArray.Sort([Origin](const AActor& A, const AActor& B) {
		float DistA = FVector::Dist(Origin, A.GetActorLocation());
		float DistB = FVector::Dist(Origin, B.GetActorLocation());
		return DistA < DistB;
	});
}