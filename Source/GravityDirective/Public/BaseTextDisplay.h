// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Runtime/Engine/Classes/Components/TextRenderComponent.h>
#include "BaseTextDisplay.generated.h"


UCLASS()
class GRAVITYDIRECTIVE_API ABaseTextDisplay : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextRenderComponent* TextRenderer;

	// Sets default values for this actor's properties
	ABaseTextDisplay();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetText(const FString& Text);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void FadeIn();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void FadeOut();
};
