// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PatrolSpaceship.generated.h"

UCLASS()
class CPP_ASSIGNMENT_6_JCM_API APatrolSpaceship : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APatrolSpaceship();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PatrolSpaceship|Components");
	USceneComponent* SceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PatrolSpaceship|Components");
	UStaticMeshComponent* StaticMeshComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PatrolSpaceship|Properties")
	float MoveSpeed = 2000.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PatrolSpaceship|Properties")
	float RotationSpeed = 180.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PatrolSpaceship|Properties")
	float PauseDuration = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PatrolSpaceship|Properties")
	FVector PointA = FVector(5500.0f, 0.0f, 0.0f);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PatrolSpaceship|Properties")
	FVector PointB = FVector(14000.0f, 0.0f, 2000.0f);

private:
	FTimerHandle PauseTimerHandle;

	bool bMovingToB = true;
	bool bMovingToA = false;
	bool bIsRotating = false;
	float TotalTurnedAngle = 0.0f;
	float TargetTurnAngle = 180.0f;

	void ResumeMovement();

};
