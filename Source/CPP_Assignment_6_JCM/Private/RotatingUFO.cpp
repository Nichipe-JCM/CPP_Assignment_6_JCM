// Fill out your copyright notice in the Description page of Project Settings.


#include "RotatingUFO.h"

// Sets default values
ARotatingUFO::ARotatingUFO()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComponent->SetupAttachment(SceneRoot);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Fab/UFO_Doodle/scene.scene"));
	if (MeshAsset.Succeeded())
	{
		StaticMeshComponent->SetStaticMesh(MeshAsset.Object);
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Game/Fab/UFO_Doodle/Ovni.Ovni"));
	if (MaterialAsset.Succeeded())
	{
		StaticMeshComponent->SetMaterial(0, MaterialAsset.Object);
	}

}

// Called when the game starts or when spawned
void ARotatingUFO::BeginPlay()
{
	Super::BeginPlay();
	SetActorScale3D(FVector(0.25f));
	SetActorRotation(FRotator(0.0f));
}

// Called every frame
void ARotatingUFO::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (RotationDirection)
	{
	case ERotationDirection::Clockwise:
		if (!FMath::IsNearlyZero(RotationSpeed))
			AddActorLocalRotation(FRotator(0.0f, RotationSpeed * DeltaTime, 0.0f));
		break;

	case ERotationDirection::CounterClockwise:
		if (!FMath::IsNearlyZero(RotationSpeed))
			AddActorLocalRotation(FRotator(0.0f, -RotationSpeed * DeltaTime, 0.0f));
		break;

	case ERotationDirection::Still:
		//아무것도 안함
		break;
	}
}

