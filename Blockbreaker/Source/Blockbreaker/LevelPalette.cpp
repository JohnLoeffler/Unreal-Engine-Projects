// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelPalette.h"
#include "BlockbreakerBPFunctionLibrary.h"

float Normalize(float Value, float NewHigh, float NewLow, float OldHigh, float OldLow) {
  return((OldHigh - OldLow) == 0.0 ? NewLow : (((Value - OldLow)*(NewHigh - NewLow) / (OldHigh - OldLow)) + (NewLow)));
}

TArray<FVector> ULevelPalette::GenerateScheme(FVector const & HSL, uint32 NumColors){
  TArray<FVector> Colors;
  
  return Colors;
}
TArray<FVector> UMonochrome::GenerateScheme(FVector const & HSL, uint32 NumColors){
  TArray<FVector> Colors;
  float X = HSL.X, Y = HSL.Y, Z = HSL.Z;
  
  float S1 = FMath::FRandRange(0.4f, 0.524f);
  float S2 = FMath::FRandRange(0.525f, 0.599f);
  float S3 = FMath::FRandRange(0.6f, 0.699f);
  float S4 = FMath::FRandRange(0.7f, 0.824f);
  float S5 = FMath::FRandRange(0.825f, 0.924f);

  float L1 = FMath::FRandRange(0.4f, 0.575f);
  float L2 = FMath::FRandRange(0.576f, 0.749f);
  float L3 = FMath::FRandRange(0.75f, 0.9f);
    
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(X, S1, L1)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(X, S1, L2)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(X, S1, L3)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(X, S2, L1)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(X, S2, L2)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(X, S2, L3)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(X, S3, L1)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(X, S3, L2)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(X, S3, L3)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(X, S4, L1)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(X, S4, L2)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(X, S4, L3)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(X, S5, L1)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(X, S5, L2)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(X, S5, L3)));
  return Colors;
}
TArray<FVector> UComplementary::GenerateScheme(FVector const & HSL, uint32 NumColors){
  TArray<FVector> Colors;
  float X = HSL.X, Y = HSL.Y, Z = HSL.Z;
  float H1 = fmodf((X + 180.0f),360.0f);
  
  float S1 = FMath::FRandRange(0.4f, 0.599f);
  float S2 = FMath::FRandRange(0.6f, 0.749f);
  float S3 = FMath::FRandRange(0.75f, 0.924f);
  float S4 = FMath::FRandRange(0.4f, 0.624f);
  float S5 = FMath::FRandRange(0.625f, 0.924f);

  float L1 = FMath::FRandRange(0.4f, 0.575f);
  float L2 = FMath::FRandRange(0.576f, 0.749f);
  float L3 = FMath::FRandRange(0.75f, 0.9f);

  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(X, S1, L1)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(X, S1, L2)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(X, S1, L3)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(X, S2, L1)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(X, S2, L2)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(X, S2, L3)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(X, S3, L1)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(X, S3, L2)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(X, S3, L3)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(H1, S4, L1)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(H1, S4, L2)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(H1, S4, L3)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(H1, S5, L1)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(H1, S5, L2)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(H1, S5, L3)));
  return Colors;
}
TArray<FVector> UAnalogous::GenerateScheme(FVector const & HSL, uint32 NumColors){
  TArray<FVector> Colors;
  float X = HSL.X, Y = HSL.Y, Z = HSL.Z;
  
  float H1 = FMath::FRandRange(X-12.0f, X-24.0f);
  float H2 = FMath::FRandRange(X, X-12.0f);
  float H3 = X;
  float H4 = FMath::FRandRange(X, X + 12.0f);
  float H5 = FMath::FRandRange(X + 12.0f, X + 24.0f);

  float S1 = FMath::FRandRange(0.4f, 0.724f);
  float S2 = FMath::FRandRange(0.725f, 0.924f);
  float S3 = FMath::FRandRange(0.4f, 0.599f);
  float S4 = FMath::FRandRange(0.6f, 0.749f);
  float S5 = FMath::FRandRange(0.75f, 0.924f);

  float L1 = FMath::FRandRange(0.4f, 0.575f);
  float L2 = FMath::FRandRange(0.576f, 0.749f);
  float L3 = FMath::FRandRange(0.75f, 0.925f);

  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(H1, S1, L1)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(H1, S1, L2)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(H1, S1, L3)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(H2, S2, L1)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(H2, S2, L2)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(H2, S2, L3)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(H3, S3, L1)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(H3, S3, L2)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(H3, S3, L3)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(H4, S4, L1)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(H4, S4, L2)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(H4, S4, L3)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(H5, S5, L1)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(H5, S5, L2)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(H5, S5, L3)));
  return Colors;
}
TArray<FVector> UAccentedAnalogous::GenerateScheme(FVector const & HSL, uint32 NumColors){
  TArray<FVector> Colors;
  float X = HSL.X, Y = HSL.Y, Z = HSL.Z;
  
  float ComplementHue = fmodf((X + 180.0f), 360.0f);

  float H1 = ComplementHue;
  float H2 = (FMath::RandBool() ? FMath::FRandRange(X, X + 12.0f) : FMath::FRandRange(X - 12.0f, X));
  float H3 = X;
  float H4 = (FMath::RandBool() ? FMath::FRandRange(X, X + 12.0f) : FMath::FRandRange(X - 12.0f, X));
  float H5 = (FMath::RandBool() ? FMath::FRandRange(X + 12.0f, X + 24.0f) : FMath::FRandRange(X - 24.0f, X - 12.0f));

  float S1 = FMath::FRandRange(0.4f, 0.724f);
  float S2 = FMath::FRandRange(0.725f, 0.924f);
  float S3 = FMath::FRandRange(0.4f, 0.599f);
  float S4 = FMath::FRandRange(0.6f, 0.749f);
  float S5 = FMath::FRandRange(0.75f, 0.924f);

  float L1 = FMath::FRandRange(0.4f, 0.575f);
  float L2 = FMath::FRandRange(0.576f, 0.749f);
  float L3 = FMath::FRandRange(0.75f, 0.925f);

  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(H1, S1, L1)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(H1, S1, L2)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(H1, S1, L3)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(H2, S2, L1)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(H2, S2, L2)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(H2, S2, L3)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(H3, S3, L1)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(H3, S3, L2)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(H3, S3, L3)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(H4, S4, L1)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(H4, S4, L2)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(H4, S4, L3)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(H5, S5, L1)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(H5, S5, L2)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(H5, S5, L3)));
  return Colors;
}
TArray<FVector> UTriadic::GenerateScheme(FVector const & HSL, uint32 NumColors){
  TArray<FVector> Colors;
  float X = HSL.X, Y = HSL.Y, Z = HSL.Z;
  float Color1 = FMath::Fmod((X - 120.f), 360.0f), 
    Color2 = FMath::Fmod((X + 120.f), 360.0f);

  float H1 = Color1;
  float H2 = X;
  float H3 = Color2;

  float S1 = FMath::FRandRange(0.4f, 0.725f);
  float S2 = FMath::FRandRange(0.726f, 0.925f);
  float S3 = FMath::FRandRange(0.5f, 0.925f);

  float L1 = FMath::FRandRange(0.4f, 0.575f);
  float L2 = FMath::FRandRange(0.576f, 0.75f);
  float L3 = FMath::FRandRange(0.76f, 0.925f);

  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(H1, S1, L1)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(H1, S1, L2)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(H1, S1, L3)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(H1, S2, L1)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(H1, S2, L2)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(H1, S2, L3)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(H2, S1, L1)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(H2, S1, L2)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(H2, S1, L3)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(H2, S2, L1)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(H2, S2, L2)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(H2, S2, L3)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(H3, S3, L1)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(H3, S3, L2)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(H3, S3, L3)));
  return Colors;
}
TArray<FVector> UTetradic::GenerateScheme(FVector const & HSL, uint32 NumColors){
  TArray<FVector> Colors;
  float X = HSL.X, Y = HSL.Y, Z = HSL.Z;
  float Color1 = FMath::Fmod((X - 90.f), 360.0f),
    Color2 = FMath::Fmod((X - 180.f), 360.0f),
    Color3 = FMath::Fmod((X - 270.f), 360.0f);

  float H1 = Color1;
  float H2 = Color2;
  float H3 = X;
  float H4 = Color3;

  float S1 = FMath::FRandRange(0.4f, 0.725f);
  float S2 = FMath::FRandRange(0.726f, 0.925f);
  float S3 = FMath::FRandRange(0.6f, 0.825f);

  float L1 = FMath::FRandRange(0.4f, 0.575f);
  float L2 = FMath::FRandRange(0.576f, 0.75f);
  float L3 = FMath::FRandRange(0.76f, 0.925f);

  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(H1, S3, L1)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(H1, S3, L2)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(H1, S3, L3)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(H2, S3, L1)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(H2, S3, L2)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(H2, S3, L3)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(H3, S1, L1)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(H3, S1, L2)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(H3, S1, L3)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(H3, S2, L1)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(H3, S2, L2)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(H3, S2, L3)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(H4, S3, L1)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(H4, S3, L2)));
  Colors.Add(UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector(H4, S3, L3)));
  return Colors;
}
