// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "LevelBumper.generated.h"

class USkeletalMesh;
class USkeletalMeshComponent;

class UAudioComponent;
class ALevelPaddle;

UENUM(BlueprintType)
enum class EBumperType : uint8 {
  NORMAL UMETA(DisplayName = "Normal"),
  GUNS UMETA(DisplayName = "Guns")
};

UCLASS()
class BLOCKBREAKER_API ALevelBumper : public AActor{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ALevelBumper();
  
  UFUNCTION(BlueprintCallable, Category = "Setup")
    FORCEINLINE bool SetParentPaddle(ALevelPaddle* Parent) { this->ParentPaddle = Parent; return true; }
  
  UFUNCTION(BlueprintCallable, Category = "Setup")
    bool SetActiveMesh(EBumperType Type);
  
  UFUNCTION(Category = "")
    USkeletalMeshComponent* GetSkeletalBumperMesh() { return SkeletalMesh; }
  
  UFUNCTION(Category = "")
    UStaticMeshComponent* GetStaticBumperMesh() { return StaticMesh; }
  
  UFUNCTION(Category = "")
    void SetParentPaddleLocation(float Location) { this->LastParentPosition = Location; }

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    uint32 bTrailing : 1;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
  
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    USkeletalMeshComponent* SkeletalMesh;
  
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    UStaticMeshComponent* StaticMesh;
  
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Releations")
    ALevelPaddle* ParentPaddle;
  
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meshes")
    UStaticMesh* DefaultMesh;
  
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meshes")
    USkeletalMesh* GunsMesh;

  float LastParentPosition;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
