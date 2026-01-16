// Fill out your copyright notice in the Description page of Project Settings.


#include "StartAsteroid.h"

// Sets default values
AStartAsteroid::AStartAsteroid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComponent->SetupAttachment(SceneRoot);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Fab/Platform/scene.scene"));
	if (MeshAsset.Succeeded())
	{
		StaticMeshComponent->SetStaticMesh(MeshAsset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Game/Fab/Platform/platform_defaultMat.platform_defaultMat"));
	if (MaterialAsset.Succeeded())
	{
		StaticMeshComponent->SetMaterial(0, MaterialAsset.Object);
	}

	RotationSpeed = 10.0f;

}

// Called when the game starts or when spawned
void AStartAsteroid::BeginPlay()
{
	Super::BeginPlay();
	SetActorRotation(FRotator(0.0f));
	SetActorScale3D(FVector(1.0f));
}

// Called every frame
void AStartAsteroid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!FMath::IsNearlyZero(RotationSpeed))
	{
		AddActorLocalRotation(FRotator(0.0f, RotationSpeed * DeltaTime, 0.0f));
	}

}

