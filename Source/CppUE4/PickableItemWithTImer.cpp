// Fill out your copyright notice in the Description page of Project Settings.

#include "PickableItemWithTImer.h"
#include "Components/TextRenderComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
APickableItemWithTImer::APickableItemWithTImer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    // Our root component is a collision box
    CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("RootComponent"));
    RootComponent = CollisionBox;
    CollisionBox->SetCollisionProfileName(TEXT("Item"));
    // Add a mesh component
    StaticMesh = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("MeshComponent"));
    StaticMesh->SetupAttachment(RootComponent);
    // Add a Countdown text component
	CountdownText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("CountdownNumber"));
    CountdownText->SetupAttachment(RootComponent);
    CountdownText->SetHorizontalAlignment(EHTA_Center);
	CountdownText->SetWorldSize(50.0f);
	CountdownTime = 10;

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
    Timer = FTimespan::FromSeconds(CountdownTime);
    CountdownText->SetText(FText::AsTimespan(Timer,0));
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
    CountdownText->SetText(TEXT("Bye"));
    Destroy();
}
