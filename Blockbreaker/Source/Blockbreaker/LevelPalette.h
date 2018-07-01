// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Blockbreaker.h"
#include "LevelPalette.generated.h"

/**
 * 
 */
UCLASS()
class BLOCKBREAKER_API ULevelPalette : public UObject
{

  GENERATED_BODY()
public:
  FString Name;
  ULevelPalette() {}
  virtual ~ULevelPalette() {};
  /**
  * Generates a color scheme based on the provided base color
  * @param  HSL The HSL FVector of the color (NOT RGB,Convert RGB to HSL to use)
  * @param  NumColors The number of Colors in the Scheme, default = 5
  * @return A TArray of HSL FVectors
  */
  virtual TArray<FVector> GenerateScheme(FVector const& HSL, uint32 NumColors=5);
  
};

/** A Monochrome Palette */
UCLASS(BlueprintType)
class BLOCKBREAKER_API UMonochrome : public ULevelPalette
{
  GENERATED_BODY()
public:
  UMonochrome() { Name = TEXT("Monochrome"); }
  virtual ~UMonochrome() {}

  TArray<FVector> GenerateScheme(FVector const& HSL, uint32 NumColors=5);
};
/** A Complementary Palette */
UCLASS(BlueprintType)
  class BLOCKBREAKER_API UComplementary : public ULevelPalette {
  GENERATED_BODY()
  public:
    UComplementary() { Name = TEXT("Complementary"); }
    virtual ~UComplementary() {}

    TArray<FVector> GenerateScheme(FVector const& HSL, uint32 NumColors=5);
};

/** An Analogous palette */
UCLASS(BlueprintType)
  class BLOCKBREAKER_API UAnalogous : public ULevelPalette {
  GENERATED_BODY()
  public:
    UAnalogous() { Name = TEXT("Analogous"); }
    virtual ~UAnalogous() {}

    TArray<FVector> GenerateScheme(FVector const& HSL, uint32 NumColors=5);
};

/** An Accented Analogous palette */
UCLASS(BlueprintType)
  class BLOCKBREAKER_API UAccentedAnalogous : public ULevelPalette {
  GENERATED_BODY()
  public:
    UAccentedAnalogous() { Name = TEXT("Accentented Analogous"); }
    virtual ~UAccentedAnalogous() {}

    TArray<FVector> GenerateScheme(FVector const& HSL, uint32 NumColors=5);
};

/** A Triadic Palette */
UCLASS(BlueprintType)
  class BLOCKBREAKER_API UTriadic : public ULevelPalette {
  GENERATED_BODY()
  public:
    UTriadic() { Name = TEXT("Triadic"); }
    virtual ~UTriadic() {}

    TArray<FVector> GenerateScheme(FVector const& HSL, uint32 NumColors=5);
};

/** A Tetradic Palette */
UCLASS(BlueprintType)
  class BLOCKBREAKER_API UTetradic : public ULevelPalette {
  GENERATED_BODY()
  public:
    UTetradic() { Name = TEXT("Tetradic"); }
    virtual ~UTetradic() {}

    TArray<FVector> GenerateScheme(FVector const& HSL, uint32 NumColors=5);
};