// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelPattern.h"
#include "Blockbreaker.h"
#include "MathFunctions.h"
#include <sstream>
#include <iomanip>
#include "Runtime/Core/Public/Math/UnrealMathUtility.h"


bool ULevelPattern::GeneratePattern(int32 Width, int32 Height, float& OutHigh, float& OutLow, TArray<float>& Pattern, int32 Seed=0) {
  
  std::stringstream ss;
  ss.unsetf(std::ios::floatfield);
  ss.precision(2);
  ss.setf(std::ios::fixed, std::ios::floatfield);
  ss << "\n ";
  H = Height;
  W = Width;

  Plane = new coord*[Height];
  RawOutput = new float*[Height];
  for (int i = 0; i < Height; i++) {
    Plane[i] = new coord[Width];
    RawOutput[i] = new float[Width];
  }
  
  float *x = new float(0.0f), *a = new float(0.0f), *b = new float(0.0f), *c = new float(0.0f);
  *a = static_cast<float>(Seed % 4) + 1.0;
  *b = static_cast<float>(Seed % 4);
  *c = static_cast<float>(*b * *b);
  
  int one = (Seed % 10), two = (Seed %6) + 10, three = (Seed % 3) + 16;

  for (int i = H / 2; i > -H / 2; i--) {
    for (int j = -W / 2; j < W / 2; j++) {
      Plane[(H / 2) - i][(W / 2) + j] = coord(j, i);
    }
  }

  // For Cosine and Cosecant (1 & 4), Logb(X) is undefined for all values of X, 
  //      so use Exponential function instead
  if ((one == 1 || one == 4) && two == 14) { 
    two = 15;
  }

  Function_One = MathFunction::GetFunction(one);
  Function_Two = MathFunction::GetFunction(two);
  Function_Three = MathFunction::GetFunction(three);
  
  bool inverse = Seed % 2;
  float OldHigh = -1.0f, OldLow = 1.0f, NewHigh = 1.0f, NewLow = -1.0f;
  for (int i = H / 2; i > -H / 2; i--) {
    for (int j = -W / 2; j < W / 2; j++) {
      if (!inverse) {
        *x = static_cast<float>(Plane[(H / 2) - i][(W / 2) + j].x);
      } else {
        *x = static_cast<float>(Plane[(H / 2) - i][(W / 2) + j].y);
      }
      RawOutput[(H / 2) - i][(W / 2) + j] = Function_One->Operation(x, a, b, c);
      switch (Seed % 4) {
        case 1:
          RawOutput[(H / 2) - i][(W / 2) + j] /= ((Function_Two->Operation(x, a, b, c) == 0.0 || isnan(Function_One->Operation(x, a, b, c))) ? 1.0 : Function_One->Operation(x, a, b, c));
          break;
        case 2:
          RawOutput[(H / 2) - i][(W / 2) + j] += Function_Two->Operation(x, a, b, c);
          break;
        case 3:
          RawOutput[(H / 2) - i][(W / 2) + j] -= Function_Two->Operation(x, a, b, c);
          break;
        default:
          RawOutput[(H / 2) - i][(W / 2) + j] *= Function_Two->Operation(x, a, b, c);
          break;
      }
      if (three == 18) {  // If the 3rd Function is the Square root of X, Y is undefined when X < 0
        *x = fabs(*x); // So use the Absolute value of X rather than X so we will always have a value
      } 
      float result = Function_Three->Operation(x, a, b, c);
      if (Seed % 2 == 0) {
        RawOutput[(H / 2) - i][(W / 2) + j] = (result >= RawOutput[(H / 2) - i][(W / 2) + j] ? result : RawOutput[(H / 2) - i][(W / 2) + j]);
      } else {
        RawOutput[(H / 2) - i][(W / 2) + j] = (result < RawOutput[(H / 2) - i][(W / 2) + j] ? result : RawOutput[(H / 2) - i][(W / 2) + j]);
      }
      OldHigh = (RawOutput[(H / 2) - i][(W / 2) + j] > OldHigh ? RawOutput[(H / 2) - i][(W / 2) + j] : OldHigh);
      OldLow = (RawOutput[(H / 2) - i][(W / 2) + j] < OldLow ? RawOutput[(H / 2) - i][(W / 2) + j] : OldLow);
    }
  }

  for (int i = H / 2; i > -H / 2; i--) {
    for (int j = -W / 2; j < W / 2; j++) {
      RawOutput[(H/2) - i][(W/2) + j] = MathFunction::Normalize(RawOutput[(H / 2) - i][(W / 2) + j], 1.0f, -1.0f, OldHigh, OldLow);
      ss << "|" << std::setw(5) << RawOutput[(H / 2) - i][(W / 2) + j];
      OutHigh = (RawOutput[(H / 2) - i][(W / 2) + j] > OutHigh ? RawOutput[(H / 2) - i][(W / 2) + j] : OldHigh);
      OutLow = (RawOutput[(H / 2) - i][(W / 2) + j] < OutLow ? RawOutput[(H / 2) - i][(W / 2) + j] : OldLow);
    }
    ss << "|\n";
  }
  FString Out(ss.str().c_str());
  UE_LOG(LogTemp, Warning, TEXT("%s"), *Out);
  
  ss.clear();
  
  for (int i = H / 2; i > -H / 2; i--) {
    for (int j = -W / 2; j < W / 2; j++) {
      Pattern.Add(RawOutput[(H / 2) - i][(W / 2) + j]);
    }
  }

  return true;
}
