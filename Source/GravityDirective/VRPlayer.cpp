// Fill out your copyright notice in the Description page of Project Settings.

#include "VRPlayer.h"
#include "GameAttributeSet.h"
#include "AbilityInputID.h"


// Sets default values
AVRPlayer::AVRPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystem = CreateDefaultSubobject<UPlayerAbilitySystemComponent>("AbilitySystem");
	AbilitySystem->SetIsReplicated(false);

	Attributes = CreateDefaultSubobject<UGameAttributeSet>("Attributes");

}

// Called when the game starts or when spawned
void AVRPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVRPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AVRPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (AbilitySystem && InputComponent) {
		const FGameplayAbilityInputBinds Binds("Confirm", "Cancel", "EAbilityInputID", static_cast<int32>(EAbilityInputID::Confirm), static_cast<int32>(EAbilityInputID::Cancel) );
		AbilitySystem->BindAbilityActivationToInputComponent(InputComponent, Binds);
	}

}

class UAbilitySystemComponent* AVRPlayer::GetAbilitySystemComponent() const
{
	return AbilitySystem;
}

void AVRPlayer::InitializeAttributes()
{
	if (AbilitySystem && DefaultAttributeEffect)
	{
		FGameplayEffectContextHandle Context = AbilitySystem->MakeEffectContext();
		Context.AddSourceObject(this);

		FGameplayEffectSpecHandle Spec = AbilitySystem->MakeOutgoingSpec(DefaultAttributeEffect, 1, Context);

		if (Spec.IsValid())
		{
			FActiveGameplayEffectHandle GE = AbilitySystem->ApplyGameplayEffectSpecToSelf(*Spec.Data.Get());
		}
	}
}

void AVRPlayer::GiveDefaultAbilities()
{
	if (HasAuthority() && AbilitySystem)
	{
		for (auto Ability : DefaultAbilities) 
		{
			AbilitySystem->GiveAbility(FGameplayAbilitySpec(Ability, 1, static_cast<int32>(Ability.GetDefaultObject()->AbilityInputID), this));
		}
	}
}

void AVRPlayer::PossessedBy(AController* NewController) 
{
	Super::PossessedBy(NewController);

	// Change if the player gets a seperate avatar
	AbilitySystem->InitAbilityActorInfo(this, this);

	InitializeAttributes();
	GiveDefaultAbilities();

	if (AbilitySystem && InputComponent) {
		const FGameplayAbilityInputBinds Binds("Confirm", "Cancel", "EAbilityInputID", static_cast<int32>(EAbilityInputID::Confirm), static_cast<int32>(EAbilityInputID::Cancel) );
		AbilitySystem->BindAbilityActivationToInputComponent(InputComponent, Binds);
	}
}
