// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Asteroid.generated.h"

UCLASS()
class CPP_ASSIGNMENT_6_JCM_API AAsteroid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAsteroid();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Asteroid|Components");
	USceneComponent* SceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Asteroid|Components");
	UStaticMeshComponent* StaticMeshComponent;

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Asteroid|Properties");
	FBox SpawnBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Asteroid|Properties");
	FRotator RotationRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Asteroid|Properties");
	FVector MoveVelocity;

	void ResetAsteroid(bool bRandomizeLocation);

	void SetSpawnBox(const FBox& NewSpawnBox);

};
