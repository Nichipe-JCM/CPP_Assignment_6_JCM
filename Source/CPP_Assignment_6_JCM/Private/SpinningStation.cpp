// Fill out your copyright notice in the Description page of Project Settings.


#include "SpinningStation.h"

// Sets default values
ASpinningStation::ASpinningStation()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComponent->SetupAttachment(SceneRoot);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Fab/Sci-Fi_Space_Station/sci_fi_space_station.sci_fi_space_station"));
	if (MeshAsset.Succeeded())
	{
		StaticMeshComponent->SetStaticMesh(MeshAsset.Object);
	}

#define SET_MAT(INDEX, PATH) \
   { \
	 static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset##INDEX(TEXT(PATH)); \
	 if (MaterialAsset##INDEX.Succeeded()) \
	 { \
		 StaticMeshComponent->SetMaterial(INDEX, MaterialAsset##INDEX.Object); \
	 } \
	}	
	{
		SET_MAT(0, "/Game/Fab/Sci-Fi_Space_Station/Material_029.Material_029");
		SET_MAT(1, "/Game/Fab/Sci-Fi_Space_Station/Material.Material");
		SET_MAT(2, "/Game/Fab/Sci-Fi_Space_Station/Material_039.Material_039");
		SET_MAT(3, "/Game/Fab/Sci-Fi_Space_Station/Material_030.Material_030");
		SET_MAT(4, "/Game/Fab/Sci-Fi_Space_Station/Material_056.Material_056");
		SET_MAT(5, "/Game/Fab/Sci-Fi_Space_Station/Material_057.Material_057");
		SET_MAT(6, "/Game/Fab/Sci-Fi_Space_Station/Material_010.Material_010");
		SET_MAT(7, "/Game/Fab/Sci-Fi_Space_Station/Material_007.Material_007");
		SET_MAT(8, "/Game/Fab/Sci-Fi_Space_Station/Material_050.Material_050");
		SET_MAT(9, "/Game/Fab/Sci-Fi_Space_Station/Material_048.Material_048");
		SET_MAT(10, "/Game/Fab/Sci-Fi_Space_Station/Material_038.Material_038");
		SET_MAT(11, "/Game/Fab/Sci-Fi_Space_Station/Material_059.Material_059");
		SET_MAT(12, "/Game/Fab/Sci-Fi_Space_Station/Material_013.Material_013");
		SET_MAT(13, "/Game/Fab/Sci-Fi_Space_Station/Material_004.Material_004");
		SET_MAT(14, "/Game/Fab/Sci-Fi_Space_Station/Material_003.Material_003");
		SET_MAT(15, "/Game/Fab/Sci-Fi_Space_Station/Material_005.Material_005");
		SET_MAT(16, "/Game/Fab/Sci-Fi_Space_Station/Material_006.Material_006");
		SET_MAT(17, "/Game/Fab/Sci-Fi_Space_Station/Material_034.Material_034");
		SET_MAT(18, "/Game/Fab/Sci-Fi_Space_Station/Material_044.Material_044");
		SET_MAT(19, "/Game/Fab/Sci-Fi_Space_Station/Material_043.Material_043");
		SET_MAT(20, "/Game/Fab/Sci-Fi_Space_Station/Material_036.Material_036");
		SET_MAT(21, "/Game/Fab/Sci-Fi_Space_Station/Material_035.Material_035");
		SET_MAT(22, "/Game/Fab/Sci-Fi_Space_Station/Material_033.Material_033");
		SET_MAT(23, "/Game/Fab/Sci-Fi_Space_Station/Material_047.Material_047");
		SET_MAT(24, "/Game/Fab/Sci-Fi_Space_Station/Material_052.Material_052");
		SET_MAT(25, "/Game/Fab/Sci-Fi_Space_Station/Material_051.Material_051");
		SET_MAT(26, "/Game/Fab/Sci-Fi_Space_Station/Material_053.Material_053");
		SET_MAT(27, "/Game/Fab/Sci-Fi_Space_Station/Material_054.Material_054");
		SET_MAT(28, "/Game/Fab/Sci-Fi_Space_Station/Material_055.Material_055");
		SET_MAT(29, "/Game/Fab/Sci-Fi_Space_Station/Material_011.Material_011");
		SET_MAT(30, "/Game/Fab/Sci-Fi_Space_Station/Material_012.Material_012");
		SET_MAT(31, "/Game/Fab/Sci-Fi_Space_Station/Material_021.Material_021");
		SET_MAT(32, "/Game/Fab/Sci-Fi_Space_Station/Material_014.Material_014");
		SET_MAT(33, "/Game/Fab/Sci-Fi_Space_Station/Material_015.Material_015");
		SET_MAT(34, "/Game/Fab/Sci-Fi_Space_Station/Material_016.Material_016");
		SET_MAT(35, "/Game/Fab/Sci-Fi_Space_Station/Material_017.Material_017");
		SET_MAT(36, "/Game/Fab/Sci-Fi_Space_Station/Material_018.Material_018");
		SET_MAT(37, "/Game/Fab/Sci-Fi_Space_Station/Material_019.Material_019");
		SET_MAT(38, "/Game/Fab/Sci-Fi_Space_Station/Material_020.Material_020");
		SET_MAT(39, "/Game/Fab/Sci-Fi_Space_Station/Material_009.Material_009");
		SET_MAT(40, "/Game/Fab/Sci-Fi_Space_Station/Material_025.Material_025");
		SET_MAT(41, "/Game/Fab/Sci-Fi_Space_Station/Material_024.Material_024");
		SET_MAT(42, "/Game/Fab/Sci-Fi_Space_Station/Material_026.Material_026");
		SET_MAT(43, "/Game/Fab/Sci-Fi_Space_Station/Material_028.Material_028");
		SET_MAT(44, "/Game/Fab/Sci-Fi_Space_Station/Material_023.Material_023");
		SET_MAT(45, "/Game/Fab/Sci-Fi_Space_Station/Material_042.Material_042");
		SET_MAT(46, "/Game/Fab/Sci-Fi_Space_Station/Material_040.Material_040");
		SET_MAT(47, "/Game/Fab/Sci-Fi_Space_Station/Material_041.Material_041");
		SET_MAT(48, "/Game/Fab/Sci-Fi_Space_Station/Cube_033__0.Cube_033__0");
	}
}

// Called when the game starts or when spawned
void ASpinningStation::BeginPlay()
{
	Super::BeginPlay();
	SetActorRotation(FRotator(0.0f, 90.0f, 0.0f));
	SetActorScale3D(FVector(0.005f));
}

// Called every frame
void ASpinningStation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!FMath::IsNearlyZero(RotationSpeed))
	{
		AddActorLocalRotation(FRotator(0.0f , 0.0f, -RotationSpeed * DeltaTime));
	}
}

