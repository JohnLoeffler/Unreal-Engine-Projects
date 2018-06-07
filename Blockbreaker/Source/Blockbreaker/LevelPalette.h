// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LevelPalette.generated.h"

/**
 * 
 */
UCLASS()
class BLOCKBREAKER_API ULevelPalette : public UObject
{

  GENERATED_BODY()
public:

  ULevelPalette() {}
  virtual ~ULevelPalette() {};

  virtual TArray<FVector> GenerateScheme(FVector const& HSL, uint32 NumColors=5);
protected:
  FRandomStream RNG;
};

UCLASS(BlueprintType)
class BLOCKBREAKER_API UMonochrome : public ULevelPalette
{
  GENERATED_BODY()
public:
  UMonochrome() {}
  virtual ~UMonochrome() {}

  TArray<FVector> GenerateScheme(FVector const& HSL, uint32 NumColors=5);
};

UCLASS(BlueprintType)
  class BLOCKBREAKER_API UComplementary : public ULevelPalette {
  GENERATED_BODY()
  public:
    UComplementary() {}
    virtual ~UComplementary() {}

    TArray<FVector> GenerateScheme(FVector const& HSL, uint32 NumColors=5);
};

UCLASS(BlueprintType)
  class BLOCKBREAKER_API UAnalogous : public ULevelPalette {
  GENERATED_BODY()
  public:
    UAnalogous() {}
    virtual ~UAnalogous() {}

    TArray<FVector> GenerateScheme(FVector const& HSL, uint32 NumColors=5);
};

UCLASS(BlueprintType)
  class BLOCKBREAKER_API UAccentedAnalogous : public ULevelPalette {
  GENERATED_BODY()
  public:
    UAccentedAnalogous() {}
    virtual ~UAccentedAnalogous() {}

    TArray<FVector> GenerateScheme(FVector const& HSL, uint32 NumColors=5);
};

UCLASS(BlueprintType)
  class BLOCKBREAKER_API UTriadic : public ULevelPalette {
  GENERATED_BODY()
  public:
    UTriadic() {}
    virtual ~UTriadic() {}

    TArray<FVector> GenerateScheme(FVector const& HSL, uint32 NumColors=5);
};

UCLASS(BlueprintType)
  class BLOCKBREAKER_API UTetradic : public ULevelPalette {
  GENERATED_BODY()
  public:
    UTetradic() {}
    virtual ~UTetradic() {}

    TArray<FVector> GenerateScheme(FVector const& HSL, uint32 NumColors=5);
};

UCLASS(BlueprintType)
  class BLOCKBREAKER_API UCustom : public ULevelPalette {
  GENERATED_BODY()
  public:
    UCustom() {}
    virtual ~UCustom() {}

    TArray<FVector> GenerateScheme(FVector const& HSL, uint32 NumColors=5);
};