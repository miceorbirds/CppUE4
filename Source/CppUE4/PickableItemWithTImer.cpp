// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/TextRenderComponent.h"
#include "PickableItemWithTImer.h"


// Sets default values
APickableItemWithTImer::APickableItemWithTImer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CountdownText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("CountdownNumber"));
	CountdownText->SetHorizontalAlignment(EHTA_Center);
	CountdownText->SetWorldSize(150.0f);
	RootComponent = CountdownText;

	CountdownTime = 3;
	
}

// Called when the game starts or when spawned
void APickableItemWithTImer::BeginPlay()
{
	Super::BeginPlay();
	
	UpdateTimerDisplay();
	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &APickableItemWithTImer::AdvanceTimer, 1.0f, true);
}

// Called every frame
void APickableItemWithTImer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickableItemWithTImer::UpdateTimerDisplay()
{
    CountdownText->SetText(FString::FromInt(FMath::Max(CountdownTime, 0)));
}

void APickableItemWithTImer::AdvanceTimer()
{
    --CountdownTime;
    UpdateTimerDisplay();
    if (CountdownTime < 1)
    {
        // We're done counting down, so stop running the timer.
        GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
        //Perform any special actions we want to do when the timer ends.
        CountdownHasFinished();
    }
}

void APickableItemWithTImer::CountdownHasFinished()
{
    //Change to a special readout
    CountdownText->SetText(TEXT("00::00"));
    Destroy();
}