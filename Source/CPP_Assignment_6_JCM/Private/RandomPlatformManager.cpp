// Fill out your copyright notice in the Description page of Project Settings.


#include "RandomPlatformManager.h"
#include "RotatingUFO.h"
#include "MoveablePlatform.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ARandomPlatformManager::ARandomPlatformManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ARandomPlatformManager::BeginPlay()
{
	Super::BeginPlay();

	SpawnUFOGroup();

	SpawnPlatformGroup();

}

void ARandomPlatformManager::SpawnUFOGroup()
{
	if (!UFOClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("UFOClass is not set in RandomPlatformManager"));
		return;
	}

	FVector StartLocation = FVector(1900.0f, 0.0f, 80.0f);
	float IntervalX = 500.0f;

	for (int32 i = 0; i < 4; i++) {
		bool bRandom = FMath::RandBool();

		float RandomY = bRandom ? UpperY : LowerY;

		ERotationDirection Direction = bRandom ?
			ERotationDirection::Clockwise : ERotationDirection::CounterClockwise;

		FVector SpawnLocation = StartLocation + FVector(i * IntervalX, 0.0f, 0.0f);
		SpawnLocation.Y = RandomY;

		ARotatingUFO* NewUFO = GetWorld()->SpawnActorDeferred<ARotatingUFO>(
			UFOClass,
			FTransform(FRotator::ZeroRotator, SpawnLocation)
		);

		if (NewUFO)
		{
			NewUFO->RotationDirection = Direction;
			UGameplayStatics::FinishSpawningActor(NewUFO, FTransform(FRotator::ZeroRotator, SpawnLocation));
		}
	}
}

void ARandomPlatformManager::SpawnPlatformGroup() {
	if (!PlatformClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlatformClass is not set in RandomPlatformManager"));
		return;
	}

	int32 PatternIndex = FMath::RandRange(0, 3);

	FVector CenterLocation = PlatformStartLocation;
	float PlatformGap = 300.0f;

	switch (PatternIndex)
	{
	case 0:
	{
		for (int32 i = -1; i <= 1; i++)
		{
			FVector SpawnLocation = CenterLocation + FVector(i * PlatformGap, -300.0f, 0.0f);

			AMoveablePlatform* Platform = GetWorld()->SpawnActorDeferred<AMoveablePlatform>(PlatformClass, FTransform(SpawnLocation));
			if (Platform)
			{
				Platform->MovementType = EPlatformMovementType::PingPong;
				Platform->Direction = EPlatformDirection::Right;
				Platform->PingPongDistance = 600.0f;
				Platform->MoveSpeed = 150.0f;

				UGameplayStatics::FinishSpawningActor(Platform, FTransform(SpawnLocation));
			}
		}
		break;
	}
	case 1:
	{
		for (int32 i = -1; i <= 1; i++)
		{
			FVector SpawnLocation = CenterLocation + FVector(300.0f, i * PlatformGap, 0.0f);

			AMoveablePlatform* Platform = GetWorld()->SpawnActorDeferred<AMoveablePlatform>(PlatformClass, FTransform(SpawnLocation));
			if (Platform)
			{
				Platform->MovementType = EPlatformMovementType::PingPong;
				Platform->Direction = EPlatformDirection::Backward;
				Platform->PingPongDistance = 600.0f;
				Platform->MoveSpeed = 150.0f;

				UGameplayStatics::FinishSpawningActor(Platform, FTransform(SpawnLocation));
			}
		}
		break;
	}
	case 2:
	{
		AMoveablePlatform* CenterPlatform = GetWorld()->SpawnActorDeferred<AMoveablePlatform>(PlatformClass, FTransform(CenterLocation));
		if (CenterPlatform)
		{
			CenterPlatform->MovementType = EPlatformMovementType::None;
			CenterPlatform->Direction = EPlatformDirection::Still;
			UGameplayStatics::FinishSpawningActor(CenterPlatform, FTransform(CenterLocation));
		}

		TArray<FVector> Offsets = {
			FVector(-PlatformGap, -PlatformGap, 0.0f),
			FVector(PlatformGap, PlatformGap, 0.0f),
		};

		TArray<EPlatformDirection> Directions = {
			EPlatformDirection::Forward,
			EPlatformDirection::Backward,
		};

		for (int32 i = 0; i < Offsets.Num(); i++)
		{
			FVector SpawnLocation = CenterLocation + Offsets[i];
			AMoveablePlatform* Platform = GetWorld()->SpawnActorDeferred<AMoveablePlatform>(PlatformClass, FTransform(SpawnLocation));
			if (Platform)
			{
				Platform->MovementType = EPlatformMovementType::SquarePath;
				Platform->Direction = Directions[i];
				Platform->MoveSpeed = 300.0f;
				Platform->TurnDistance = 600.0f;
				Platform->bClockwise = true;
				UGameplayStatics::FinishSpawningActor(Platform, FTransform(SpawnLocation));
			}
		}
		break;
	}
	case 3:
	{
		AMoveablePlatform* CenterPlatform = GetWorld()->SpawnActorDeferred<AMoveablePlatform>(PlatformClass, FTransform(CenterLocation));
		if (CenterPlatform)
		{
			CenterPlatform->MovementType = EPlatformMovementType::None;
			CenterPlatform->Direction = EPlatformDirection::Still;
			UGameplayStatics::FinishSpawningActor(CenterPlatform, FTransform(CenterLocation));
		}

		TArray<FVector> Offsets = {
			FVector(-PlatformGap, PlatformGap, 0.0f),
			FVector(PlatformGap, -PlatformGap, 0.0f),
		};

		TArray<EPlatformDirection> Directions = {
			EPlatformDirection::Forward,
			EPlatformDirection::Backward,
		};

		for (int32 i = 0; i < Offsets.Num(); i++)
		{
			FVector SpawnLocation = CenterLocation + Offsets[i];
			AMoveablePlatform* Platform = GetWorld()->SpawnActorDeferred<AMoveablePlatform>(PlatformClass, FTransform(SpawnLocation));
			if (Platform)
			{
				Platform->MovementType = EPlatformMovementType::SquarePath;
				Platform->Direction = Directions[i];
				Platform->MoveSpeed = 300.0f;
				Platform->TurnDistance = 600.0f;
				Platform->bClockwise = false;
				UGameplayStatics::FinishSpawningActor(Platform, FTransform(SpawnLocation));
			}
		}
		break;
	}
	}
}

void ARandomPlatformManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}