// Fill out your copyright notice in the Description page of Project Settings.


#include "Asteroid.h"

// Sets default values
AAsteroid::AAsteroid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComponent->SetupAttachment(SceneRoot);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Fab/Asteroid/asteroid_01.asteroid_01"));
	if (MeshAsset.Succeeded())
	{
		StaticMeshComponent->SetStaticMesh(MeshAsset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Game/Fab/Asteroid/Mat1.Mat1"));
	if (MaterialAsset.Succeeded())
	{
		StaticMeshComponent->SetMaterial(0, MaterialAsset.Object);
	}
}

// Called when the game starts or when spawned
void AAsteroid::BeginPlay()
{
	Super::BeginPlay();
	ResetAsteroid(true);
}

// Called every frame
void AAsteroid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation() + (MoveVelocity * DeltaTime);
	SetActorLocation(NewLocation);
	
	AddActorLocalRotation(RotationRate * DeltaTime);

	if (SpawnBox.IsValid && !SpawnBox.IsInside(NewLocation)) ResetAsteroid(true);

}

void AAsteroid::SetSpawnBox(const FBox& NewSpawnBox)
{
	SpawnBox = NewSpawnBox;
}

void AAsteroid::ResetAsteroid(bool bRandomizeLocation)
{

	float MinScale = 0.0005f;
	float MaxScale = 0.0045f;

	FVector NewScale = FVector(
		FMath::RandRange(MinScale, MaxScale),
		FMath::RandRange(MinScale, MaxScale),
		FMath::RandRange(MinScale, MaxScale)
	);

	SetActorScale3D(NewScale);

	if (bRandomizeLocation && SpawnBox.IsValid)
	{
		FVector RandomLocation = FMath::RandPointInBox(SpawnBox);
		SetActorLocation(RandomLocation);
	}

	float RandomX = FMath::RandRange(-1000.0f, 1000.0f);
	float RandomY = FMath::RandRange(-1000.0f, 1000.0f);
	float RandomZ = FMath::RandRange(-1000.0f, 1000.0f);
	MoveVelocity = FVector(RandomX, RandomY, RandomZ);

	RotationRate = FRotator(
		FMath::RandRange(-90.0f, 90.0f),
		FMath::RandRange(-90.0f, 90.0f),
		FMath::RandRange(-90.0f, 90.0f)
	);


}