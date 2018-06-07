// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LevelPattern.generated.h"

class MathFunction;

UCLASS()
class BLOCKBREAKER_API ULevelPattern : public UObject
{
  GENERATED_BODY()
public:
  ULevelPattern() {}
  virtual ~ULevelPattern() {}
	
  MathFunction *Function_One, *Function_Two, *Function_Three;

  virtual bool GeneratePattern(int32 Width, int32 Height, float& OutHigh, float& OutLow, TArray<float>& Pattern, int32 Seed);
protected:
  struct coord {
    int x;
    int y;
    coord() {}
    coord(int x, int y) { this->x = x; this->y = y; }
  };

  int32 H, W;
  coord **Plane;
  float **RawOutput;
};


