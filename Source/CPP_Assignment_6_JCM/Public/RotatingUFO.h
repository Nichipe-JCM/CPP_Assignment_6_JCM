// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RotatingUFO.generated.h"

UENUM(BlueprintType)
enum class ERotationDirection : uint8
{
	Clockwise UMETA(DisplayName = "Clockwise"),
	CounterClockwise UMETA(DisplayName = "Counter-Clockwise"),
	Still UMETA(DisplayName = "Still (No Movement)")
};



UCLASS()
class CPP_ASSIGNMENT_6_JCM_API ARotatingUFO : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARotatingUFO();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RotatingUFO|Components");
	USceneComponent* SceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RotatingUFO|Components");
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RotatingUFO|Properties");
	float RotationSpeed = 90.0f;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RotatingUFO|Properties");
	ERotationDirection RotationDirection = ERotationDirection::Clockwise;

};
