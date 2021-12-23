// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeWeapon.h"

// Sets default values
AMeleeWeapon::AMeleeWeapon()
{
    
    DamageComponent = CreateDefaultSubobject<UCollisionDamageComponent>(TEXT("DamageComponent"));

}