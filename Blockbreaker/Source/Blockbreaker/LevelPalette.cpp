// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelPalette.h"

static float Normalize(float Value, float NewHigh, float NewLow, float OldHigh, float OldLow) {
  return((OldHigh - OldLow) == 0.0 ? NewLow : (((Value - OldLow)*(NewHigh - NewLow) / (OldHigh - OldLow)) + (NewLow)));
}

TArray<FVector> ULevelPalette::GenerateScheme(FVector const & HSL, uint32 NumColors){
  TArray<FVector> Colors;
  float X = HSL.X, Y = HSL.Y, Z = HSL.Z;
  int32 Rem = (int32)NumColors % 2;
  UE_LOG(LogTemp, Warning, TEXT("REM == %d"), Rem);
  float incr = Normalize((0.1*Y), 1.0, 0.0, Y, 0.0);
  for (int32 i = -(int32)NumColors/2; i < (int32)NumColors/2; i++) {
    UE_LOG(LogTemp, Warning, TEXT("Increment is %f"), incr*(float)i);
    FVector C(X, (Y = ((HSL.Y + (incr*(float)i) == 0.0 ? 1.0 : HSL.Y + (incr*(float)i)))),Z);
    Colors.Add(C);
  }
  if (Rem == 1) {
    Y = (HSL.Y + (incr*(float)(NumColors / 2)));
    Colors.Add(FVector(X, Y, Z));
  }
  return Colors;
}
TArray<FVector> UMonochrome::GenerateScheme(FVector const & HSL, uint32 NumColors){
  UE_LOG(LogTemp, Warning, TEXT("Made it inside UMonochrome::GenerateScheme"));
  return TArray<FVector>();
}
TArray<FVector> UComplementary::GenerateScheme(FVector const & HSL, uint32 NumColors){
  UE_LOG(LogTemp, Warning, TEXT("Made it inside UComplementary::GenerateScheme"));
  return TArray<FVector>();
}
TArray<FVector> UAnalogous::GenerateScheme(FVector const & HSL, uint32 NumColors){
  UE_LOG(LogTemp, Warning, TEXT("Made it inside UAnalogous::GenerateScheme"));
  return TArray<FVector>();
}
TArray<FVector> UAccentedAnalogous::GenerateScheme(FVector const & HSL, uint32 NumColors){
  UE_LOG(LogTemp, Warning, TEXT("Made it inside UAccentedAnalogous::GenerateScheme"));
  return TArray<FVector>();
}
TArray<FVector> UTriadic::GenerateScheme(FVector const & HSL, uint32 NumColors){
  UE_LOG(LogTemp, Warning, TEXT("Made it inside UTriadic::GenerateScheme"));
  return TArray<FVector>();
}
TArray<FVector> UTetradic::GenerateScheme(FVector const & HSL, uint32 NumColors){
  UE_LOG(LogTemp, Warning, TEXT("Made it inside UTetradic::GenerateScheme"));
  return TArray<FVector>();
}
TArray<FVector> UCustom::GenerateScheme(FVector const & HSL, uint32 NumColors){
  UE_LOG(LogTemp, Warning, TEXT("Made it inside UCustom::GenerateScheme"));
  return TArray<FVector>();
}