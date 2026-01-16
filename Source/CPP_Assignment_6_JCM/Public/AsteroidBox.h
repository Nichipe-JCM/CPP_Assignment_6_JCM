// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AsteroidBox.generated.h"

class AAsteroid;
class UBoxComponent;


UCLASS()
class CPP_ASSIGNMENT_6_JCM_API AAsteroidBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAsteroidBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AsteroidBox|Components")
	UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AsteroidBox|Components")
	TSubclassOf<AAsteroid> AsteroidClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AsteroidBox|Properties")
	int32 AsteroidCount = 10;



public:	

	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
