// Fill out your copyright notice in the Description page of Project Settings.


#include "GunComponent.h"

void UGunComponent::PrimaryPressed_Implementation() {
    this->Spawn();
}