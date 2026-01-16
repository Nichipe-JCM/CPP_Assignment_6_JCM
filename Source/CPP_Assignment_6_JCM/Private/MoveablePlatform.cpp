// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveablePlatform.h"

// Sets default values
AMoveablePlatform::AMoveablePlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComponent->SetupAttachment(SceneRoot);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Engine/EditorMeshes/AssetViewer/Floor_Mesh.Floor_Mesh"));
	if (MeshAsset.Succeeded())
	{
		StaticMeshComponent->SetStaticMesh(MeshAsset.Object);
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Engine/EditorLandscapeResources/MirrorPlaneMaterial.MirrorPlaneMaterial"));
	if (MaterialAsset.Succeeded())
	{
		StaticMeshComponent->SetMaterial(0, MaterialAsset.Object);
	}
	Direction = EPlatformDirection::Forward;
	SetActorScale3D(FVector(0.2f));
	SetActorRotation(FRotator(0.0f));
	MoveSpeed = 100.0f;
}

// Called when the game starts or when spawned
void AMoveablePlatform::BeginPlay()
{
	Super::BeginPlay();
	LastTurnLocation = GetActorLocation();
}

// Called every frame
void AMoveablePlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector MoveDirection = FVector::ZeroVector;

	switch (Direction)
	{
	case EPlatformDirection::Up:
		MoveDirection = FVector(0.0f, 0.0f, 1.0f);
		break;
	case EPlatformDirection::Down:
		MoveDirection = FVector(0.0f, 0.0f, -1.0f);
		break;
	case EPlatformDirection::Left:
		MoveDirection = FVector(0.0f, -1.0f, 0.0f);
		break;
	case EPlatformDirection::Right:
		MoveDirection = FVector(0.0f, 1.0f, 0.0f);
		break;
	case EPlatformDirection::Forward:
		MoveDirection = FVector(1.0f, 0.0f, 0.0f);
		break;
	case EPlatformDirection::Backward:
		MoveDirection = FVector(-1.0f, 0.0f, 0.0f);
		break;
	case EPlatformDirection::Still:
		MoveDirection = FVector::ZeroVector;
		break;
	}

	switch(MovementType)	
	{
	case EPlatformMovementType::PingPong:

		CurrentLocation = GetActorLocation();
		NewLocation = MoveDirection * MoveSpeed * DeltaTime * PingPong;
		if (NewLocation != FVector::ZeroVector)
		{
			AddActorLocalOffset(NewLocation);
		}
		DistanceMoved = FVector::Dist(LastTurnLocation, GetActorLocation());
		if (DistanceMoved >= PingPongDistance)
		{
			ClampedLocation = LastTurnLocation + (MoveDirection * PingPong * PingPongDistance);
			PingPong *= -1.0f;
			SetActorLocation(ClampedLocation);
			LastTurnLocation = ClampedLocation;
		}
		break;


	case EPlatformMovementType::SquarePath:

		CurrentLocation = GetActorLocation();
		NewLocation = MoveDirection * MoveSpeed * DeltaTime;
		if (NewLocation != FVector::ZeroVector)
		{
			AddActorLocalOffset(NewLocation);
		}
		DistanceMoved = FVector::Dist(LastTurnLocation, GetActorLocation());

		if (DistanceMoved >= TurnDistance)
		{
			ClampedLocation = LastTurnLocation + (MoveDirection * TurnDistance);
			SetActorLocation(ClampedLocation);
			LastTurnLocation = ClampedLocation;
			if (bClockwise)
			{
				switch (Direction)
				{
				case EPlatformDirection::Forward:  Direction = EPlatformDirection::Right; break;
				case EPlatformDirection::Right:    Direction = EPlatformDirection::Backward; break;
				case EPlatformDirection::Backward: Direction = EPlatformDirection::Left; break;
				case EPlatformDirection::Left:     Direction = EPlatformDirection::Forward; break;
				}
			}
			else
			{
				switch (Direction)
				{
				case EPlatformDirection::Forward:  Direction = EPlatformDirection::Left; break;
				case EPlatformDirection::Left:     Direction = EPlatformDirection::Backward; break;
				case EPlatformDirection::Backward: Direction = EPlatformDirection::Right; break;
				case EPlatformDirection::Right:    Direction = EPlatformDirection::Forward; break;
				}
			}
		}
		break;
	case EPlatformMovementType::None:
	default:
		NewLocation = MoveDirection * MoveSpeed * DeltaTime;
		if (NewLocation != FVector::ZeroVector)
		{
			AddActorLocalOffset(NewLocation);
		}
		break;
	}

	
}

