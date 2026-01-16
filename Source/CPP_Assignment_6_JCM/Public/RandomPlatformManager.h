// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RandomPlatformManager.generated.h"

class ARotatingUFO;
class AMoveablePlatform;

UCLASS()
class CPP_ASSIGNMENT_6_JCM_API ARandomPlatformManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARandomPlatformManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RandomPlatformManager|Classes")
	TSubclassOf<ARotatingUFO> UFOClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RandomPlatformManager|Properties")
	float UpperY = 250.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RandomPlatformManager|Properties")
	float LowerY = -250.0f;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RandomPlatformManager|Classes")
	TSubclassOf<AMoveablePlatform> PlatformClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RandomPlatformManager|Properties")
	FVector PlatformStartLocation = FVector(4500.0f, 20.0f, 0.0f);


private:

	void SpawnUFOGroup();

	void SpawnPlatformGroup();

};
