// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickableItemWithTImer.generated.h"


class UTextRenderComponent;
struct FTimerHandle;

UCLASS()
class CPPUE4_API APickableItemWithTImer : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	APickableItemWithTImer();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//How long, in seconds, the countdown will run
	UPROPERTY(EditAnywhere, Category="Timer")
	int32 CountdownTime;

	UTextRenderComponent* CountdownText;
	void UpdateTimerDisplay();
	void AdvanceTimer();
	void CountdownHasFinished();
	FTimerHandle CountdownTimerHandle;
};
