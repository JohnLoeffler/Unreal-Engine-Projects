// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelArch.h"
#include "Components/StaticMeshComponent.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"

// Sets default values
ALevelArch::ALevelArch(){
  static ConstructorHelpers::FObjectFinder<UStaticMesh> Archmesh(TEXT(
    "StaticMesh'/Game/Assets/Meshes/LevelProps/BasicBoundingArch.BasicBoundingArch'"));
 	
  // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
  Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ArchMesh"));
  Mesh->SetupAttachment(RootComponent);
  RootComponent = Mesh;
  
  UStaticMesh* SMesh = Archmesh.Object;
  Mesh->SetStaticMesh(SMesh);
  Mesh->SetWorldScale3D(FVector(1.25f, 1.0f, 1.25f));
  // /Game/Assets/Meshes/LevelProps/BasicBoundingArch.BasicBoundingArch
}

// Called when the game starts or when spawned
void ALevelArch::BeginPlay(){
	Super::BeginPlay();
}

// Called every frame
void ALevelArch::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
}

