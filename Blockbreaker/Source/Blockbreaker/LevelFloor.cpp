// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelFloor.h"
#include "Blockbreaker.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ALevelFloor::ALevelFloor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

  MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
  MeshComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ALevelFloor::BeginPlay()
{
	Super::BeginPlay();
  FString Timestamp = FDateTime::Now().ToString();
  
  LOG(_INF, "");
}

// Called every frame
void ALevelFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

