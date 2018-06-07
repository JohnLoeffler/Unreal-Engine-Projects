// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelBrick.generated.h"

class UStaticMeshComponent;
class UAudioComponent;

UENUM(BlueprintType)
enum class EBrickStrength : uint8 {
  STANDARD UMETA(DisplayName = "Standard"),
  HARDENED UMETA(DisplayName = "Hardened"),
  REINFORCED UMETA(DisplayName = "Reinforced"),
  BOMB UMETA(DisplayName = "Bomb"),
  EMPTY UMETA(DisplayName = "Empty")
};

UCLASS()
class BLOCKBREAKER_API ALevelBrick : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelBrick();
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
    EBrickStrength Type;
  bool SetBrickType(EBrickStrength Type);
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
    float BaseHealth;
  void DamageBrick(float Damage) { this->BrickHealth -= Damage; }
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes")
    float BrickHealth;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Brick Type|Meshes")
    UStaticMesh* Standard;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Brick Type|Meshes")
    UStaticMesh* Hardened;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Brick Type|Meshes")
    UStaticMesh* Reinforced;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Brick Type|Meshes")
    UStaticMesh* Bomb;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    UStaticMeshComponent* Mesh;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
    class UAudioComponent* AudioComponent;



  TArray<class UMaterialInstanceDynamic*> MaterialInstances;

public:
  UFUNCTION(Category = "Dynamic Appearance")
    void SetBrickColors(TArray<FVector> Colors);
  UFUNCTION(Category = "Dynamic Appearance")
    void SetBrickColor(FVector Color);
  UFUNCTION(Category = "Setup")
    bool Init();



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
