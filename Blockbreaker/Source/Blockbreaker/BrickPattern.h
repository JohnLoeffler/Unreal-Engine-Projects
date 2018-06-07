// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BrickPattern.generated.h"

UENUM(BlueprintType)
enum class EBrickType : uint8 {
    NORMAL UMETA(DisplayName = "Normal"),
    BOMB UMETA(DisplayName = "Bomb"),
    BONUS UMETA(DisplayName = "Bonus"),
    UNBREAKABLE UMETA(DisplayName = "Unbreakable"),
    EMPTY UMETA(DisplayName = "Empty"),
    ENVIRONMENTAL UMETA(DisplayName = "Environmental")
};

UENUM(BlueprintType)
enum class ETierType : uint8 {
  STANDARD UMETA(DisplayName = "Standard"), 
  HARDENED UMETA(DisplayName = "Hardened"),
  REINFORCED UMETA(DisplayName = "Reinforced") // , HOSTILE, BOSS // TO BE IMPLEMENTED
};



/**
 * More struct than class, but allows for future functionality
 */
UCLASS(BlueprintType)
class BLOCKBREAKER_API UBrickPattern : public UObject
{
	GENERATED_BODY()
public:
  UBrickPattern() {}
  virtual ~UBrickPattern() {}
  
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
    TArray<EBrickType> BrickType;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
    TArray<ETierType> TierType;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
    TArray<FVector> Color;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
    TArray<FVector> Position;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
    TArray<FRotator> Rotation;
  
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
    class UStaticMeshComponent *MeshComponent;
  
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
    class UAudioComponent *AudioComponent;
  
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
    class UParticleSystemComponent *ParticleComponent;

protected:
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Datatable")
    class UDataTable* AssetLocations;
};
