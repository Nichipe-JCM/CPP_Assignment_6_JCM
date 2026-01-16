// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MoveablePlatform.generated.h"

UENUM(BlueprintType)
enum class EPlatformDirection : uint8
{
	Up UMETA(DisplayName = "Up (+Z)"),
	Down UMETA(DisplayName = "Down (-Z)"),
	Left UMETA(DisplayName = "Left (-Y)"),
	Right UMETA(DisplayName = "Right (+Y)"),
	Forward UMETA(DisplayName = "Forward (+X)"),
	Backward UMETA(DisplayName = "Backward (-X)"),
	Still UMETA(DisplayName = "Still (No Movement)")
};

UENUM(BlueprintType)
enum class EPlatformMovementType : uint8
{
	None        UMETA(DisplayName = "None (Linear Move)"),
	PingPong    UMETA(DisplayName = "Ping Pong"),
	SquarePath  UMETA(DisplayName = "Square Path")
};

UCLASS()
class CPP_ASSIGNMENT_6_JCM_API AMoveablePlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMoveablePlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MoveablePlatform|Components");
	USceneComponent* SceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MoveablePlatform|Components");
	UStaticMeshComponent* StaticMeshComponent;

	FVector CurrentLocation;
	FVector NewLocation;
	FVector ClampedLocation;
	float DistanceMoved;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MoveablePlatform|Properties");
	EPlatformDirection Direction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MoveablePlatform|Properties")
	EPlatformMovementType MovementType = EPlatformMovementType::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MoveablePlatform|Properties");
	float MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MoveablePlatform|Properties");
	float PingPongDistance = 500.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MoveablePlatform|Logic");
	float PingPong = 1.0f

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MoveablePlatform|Logic");
	FVector LastTurnLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MoveablePlatform|Logic");
	float MovedDistance = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MoveablePlatform|Properties");
	float TurnDistance = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MoveablePlatform|Properties");
	bool bClockwise = true;

};
