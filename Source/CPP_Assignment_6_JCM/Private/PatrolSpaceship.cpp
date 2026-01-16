// Fill out your copyright notice in the Description page of Project Settings.


#include "PatrolSpaceship.h"

// Sets default values
APatrolSpaceship::APatrolSpaceship()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComponent->SetupAttachment(SceneRoot);


	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Fab/SpaceShip/spaceship.spaceship"));
	if (MeshAsset.Succeeded())
	{
		StaticMeshComponent->SetStaticMesh(MeshAsset.Object);
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Game/Fab/SpaceShip/Material_003.Material_003"));
	if (MaterialAsset.Succeeded())
	{
		StaticMeshComponent->SetMaterial(0, MaterialAsset.Object);
	}
}

// Called when the game starts or when spawned
void APatrolSpaceship::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APatrolSpaceship::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bMovingToB)
	{
		FVector CurrentLocation = GetActorLocation();
		FVector Direction = PointB - CurrentLocation;
		float DistanceSquared = Direction.SizeSquared();
		float MoveStep = MoveSpeed * DeltaTime;
		if (DistanceSquared <= MoveStep * MoveStep)
		{
			SetActorLocation(PointB);
			bMovingToB = false;
			GetWorldTimerManager().SetTimer(PauseTimerHandle, this, &APatrolSpaceship::ResumeMovement, PauseDuration, false);
		}
		else
		{
			Direction.Normalize();
			FVector NewLocation = CurrentLocation + Direction * MoveStep;
			SetActorLocation(NewLocation);
		}
	}
	else if (bMovingToA)
	{
		FVector CurrentLocation = GetActorLocation();
		FVector Direction = PointA - CurrentLocation;
		float DistanceSquared = Direction.SizeSquared();
		float MoveStep = MoveSpeed * DeltaTime;
		if (DistanceSquared <= MoveStep * MoveStep)
		{
			SetActorLocation(PointA);
			bMovingToA = false;
			GetWorldTimerManager().SetTimer(PauseTimerHandle, this, &APatrolSpaceship::ResumeMovement, PauseDuration, false);
		}
		else
		{
			Direction.Normalize();
			FVector NewLocation = CurrentLocation + Direction * MoveStep;
			SetActorLocation(NewLocation);
		}
	}

	if (bIsRotating) {
		float RotationStep = RotationSpeed * DeltaTime;
		float RemainingAngle = TargetTurnAngle - TotalTurnedAngle;
		if (RotationStep >= RemainingAngle) {
			AddActorLocalRotation(FRotator(0.0f, RemainingAngle, 0.0f));
			bIsRotating = false;
			TotalTurnedAngle = 0.0f;

			float DistanceToA = FVector::Dist(GetActorLocation(), PointA);
			float DistanceToB = FVector::Dist(GetActorLocation(), PointB);

			if (!bMovingToB && !bMovingToA) {
				if (DistanceToA < DistanceToB) {
					bMovingToB = true;
				}
				else {
					bMovingToA = true;
				}
			}
		}
		else {
			AddActorLocalRotation(FRotator(0.0f, RotationStep, 0.0f));
			TotalTurnedAngle += RotationStep;
		}
	}

}

void APatrolSpaceship::ResumeMovement()
{
	bIsRotating = true;
}

