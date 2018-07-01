// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelPattern.h"
#include "Blockbreaker.h"
#include "MathFunctions.h"
#include "BrickLayerFunctions.h"
#include "BlockbreakerGameModeBase.h"
#include <sstream>
#include <iomanip>
#include "Runtime/Core/Public/Math/UnrealMathUtility.h"


bool ULevelPattern::GenerateColorPattern(int32 Width, 
                                    int32 Height, 
                                    TArray<float>& Pattern, 
                                    int32 Seed = 0) {

  H = Height;
  W = Width;

  Plane = new Coord*[Height];
  RawOutput = new float*[Height];
  for (int i = 0; i < Height; i++) {
    Plane[i] = new Coord[Width];
    RawOutput[i] = new float[Width];
  }

  int one = (Seed % 11), two = (Seed % 6) + 11, three = (Seed % 3) + 17;

  for (int i = H / 2; i > -H / 2; i--) {
    for (int j = -W / 2; j < W / 2; j++) {
      Plane[(H/2) - i][(W/2) + j].X = j;
      Plane[(H / 2) - i][(W / 2) + j].Y = i;
      RawOutput[(H / 2) - i][(W / 2) + j] = 0.01f;
    }
  }

  ApplyColorFunctions(Seed);

  for (int i = H / 2; i > -H / 2; i--) {
    for (int j = -W / 2; j < W / 2; j++) {
      Pattern.Add(RawOutput[(H / 2) - i][(W / 2) + j]);
    }
  }
  return true;
}

bool ULevelPattern::GenerateBrickPattern(int32 Width, int32 Height, TArray<int32>& Pattern, int32 Seed, EGameDifficulty Dif){
  UE_LOG(LogTemp, Warning, TEXT("In LevelPattern::GenerateBrickPattern..."));
  UE_LOG(LogTemp, Warning, TEXT("Seed = %d, picking %d"), Seed, Seed%9);
  BrickLayerFunction* Function;
  switch (Seed % 7) {
    case 1:
      Function = new Spiral();
      break;
    case 2:
      Function = new Rectangles();
      break;
    case 3:
      Function = new Striped();
      break;
    case 4:
      Function = new Checkered();
      break;
    case 5:
      Function = new Bumpers();
      break;
    case 6:
      Function = new CenterBlob();
      break;
    default: 
      Function = new BrickLayerFunction();
      break;
  }
  int BrickCount = 0, LoopBreakCounter = 0;

  while (BrickCount < (H*W) /2 || BrickCount > (H*W)*3 / 4) {
    BrickCount = Function->Build(H, W, Pattern, Seed, Dif);
    NumberOfValidBricks = BrickCount;
    LoopBreakCounter++;
    if (LoopBreakCounter > 100) {
      return false;
    }
      
  }
  return true;
}

bool ULevelPattern::GenerateSpecialData(int32 Width, int32 Height, TArray<int32>& Pattern, int32 Seed)
{
  //UE_LOG(LogTemp, Warning, TEXT("GenerateSpecialData() Not yet Inplemented"));
  return true;
}

bool ULevelPattern::ApplyColorFunctions(int32 const& Seed){
  float OldHigh = -1.0f, OldLow = 1.0f, NewHigh = 2.5f, NewLow = -2.5f;
float *x = new float(0.0f), *y = new float(0.0f),
    *a = new float(0.0f), *b = new float(0.0f), *c = new float(0.0f);
  
  *a = static_cast<float>(Seed % 2) + 1.0;
  *b = static_cast<float>(Seed % 4);
  *c = static_cast<float>(*b * *b);

  /* random selection of functions to use to apply to the plane */
  // Function 1 deforms the plane using periodic functions, Function 2 determins colors to be applied, function three applies decorative accents 
  int one = (Seed % 10), two = (Seed % 6) + 10, three = (Seed % 3) + 17;

  // Cosine and Cosecant (1 & 4) do not play well with Loge(X), 
  //      so use Exponential function instead 
  if ((one == 1 || one == 4) && two == 14) {
    two = 15;
  }

  MathFunction* Func;

  for (int n = 0; n < 3; n++) {
    switch (n) {
      case 1:  Func = MathFunction::GetFunction(two); break;
      case 2:  Func = MathFunction::GetFunction(three); break;
      default: Func = MathFunction::GetFunction(one); break;
    }
    
    int Adjustment = rand() % 4;
    for (int i = H / 2; i > -H / 2; i--) {
      for (int j = -W / 2; j < W / 2; j++) {
        bool SwapXY = Seed % 2;
        if (!SwapXY) {
          *x = static_cast<float>(Plane[(H / 2) - i][(W / 2) + j].X);
          *y = static_cast<float>(Plane[(H / 2) - i][(W / 2) + j].Y);
        } else {
          *x = static_cast<float>(Plane[(H / 2) - i][(W / 2) + j].Y);
          *y = static_cast<float>(Plane[(H / 2) - i][(W / 2) + j].X);
        }

        Func->Operation(x, y, a, b, c);
        float result = *y;
        switch(Adjustment){
          case 1:   
            result =- RawOutput[(H / 2) - i][(W / 2) + j];
            break;
          case 2:   
            result  = RawOutput[(H / 2) - i][(W / 2) + j] - result;
            break;
          case 3:   
            result *= RawOutput[(H / 2) - i][(W / 2) + j];
            break;
          default:  
            result += RawOutput[(H / 2) - i][(W / 2) + j];
            break;
        }

        result = (isnan(result) ? 0.01 : result);

        RawOutput[(H / 2) - i][(W / 2) + j] = result;
        
        OldHigh = (RawOutput[(H / 2) - i][(W / 2) + j] > OldHigh ? RawOutput[(H / 2) - i][(W / 2) + j] : OldHigh);
        OldLow = (RawOutput[(H / 2) - i][(W / 2) + j] < OldLow ? RawOutput[(H / 2) - i][(W / 2) + j] : OldLow);
      }
    }

    for (int i = H / 2; i > -H / 2; i--){
      for (int j = -W / 2; j < W / 2; j++){
        RawOutput[(H / 2) - i][(W / 2) + j] = MathFunction::Normalize(RawOutput[(H / 2) - i][(W / 2) + j], 1.0f, -1.0f, OldHigh, OldLow);
        RealHigh = (RawOutput[(H / 2) - i][(W / 2) + j] > RealHigh ? RawOutput[(H / 2) - i][(W / 2) + j] : OldHigh);
        RealLow = (RawOutput[(H / 2) - i][(W / 2) + j] < RealLow ? RawOutput[(H / 2) - i][(W / 2) + j] : OldLow);
      }
    }
  }
  return false;
}

