// Fill out your copyright notice in the Description page of Project Settings.


#include "AsteroidBox.h"
#include "Components/BoxComponent.h"
#include "Asteroid.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AAsteroidBox::AAsteroidBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = BoxComponent;

	BoxComponent->SetBoxExtent(FVector(500.0f, 500.0f, 500.0f));


}

// Called when the game starts or when spawned
void AAsteroidBox::BeginPlay()
{
	Super::BeginPlay();

	if (!AsteroidClass) {
		UE_LOG(LogTemp, Warning, TEXT("AsteroidClass is not set in AsteroidBox"));
		return;
	}

	FBox SpawnBox = BoxComponent->Bounds.GetBox();

	for (int32 i = 0; i < AsteroidCount; ++i)
	{
		AAsteroid* NewAsteroid = GetWorld()->SpawnActorDeferred<AAsteroid>(
			AsteroidClass, 
			FTransform::Identity, 
			this, 
			nullptr, 
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn
		);
		if (NewAsteroid)
		{
			NewAsteroid->SetSpawnBox(SpawnBox);
			UGameplayStatics::FinishSpawningActor(NewAsteroid, FTransform::Identity);
		}
	}
}

// Called every frame
void AAsteroidBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

