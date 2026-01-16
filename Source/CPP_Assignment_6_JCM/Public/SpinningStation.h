// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpinningStation.generated.h"


UCLASS()
class CPP_ASSIGNMENT_6_JCM_API ASpinningStation : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpinningStation();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SpinningStation|Components");
	USceneComponent* SceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpinningStation|Components");
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SpinningStation|Properties");
	float RotationSpeed = 30.0f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
