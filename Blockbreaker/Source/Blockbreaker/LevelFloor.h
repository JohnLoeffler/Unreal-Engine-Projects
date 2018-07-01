// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Blockbreaker.h"
#include "LevelFloor.generated.h"

class UStaticMeshComponent;
class UStaticMesh;

UCLASS()
class BLOCKBREAKER_API ALevelFloor : public AActor
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	ALevelFloor();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
  /** The StaticMesh component for the floor */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
    UStaticMeshComponent* MeshComponent;
  /** The Mesh to use for the level floor */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
    UStaticMesh* FloorMesh;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
