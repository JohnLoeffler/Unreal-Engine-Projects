// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BlockbreakerBPFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class BLOCKBREAKER_API UBlockbreakerBPFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
  UFUNCTION(Category = "Essential Math Functions")
    static float GetSineDelta(float RunningTime, float DeltaTime);
#define SINE_DELTA(R, D) GetSineDelta(R, D);

  static float GetFloatFromHex(TCHAR& ch);
#define GET_F_FROM_HEX(ch) GetFloatFromHex(ch);

  static int32 GetIntFromHex(TCHAR& ch);
#define GET_I_FROM_HEX(ch) GetIntFromHex(ch);
  UFUNCTION(Category = "Essential Math Functions|Colors")
  static FVector GetHSLFromRGB(FVector RGB);
#define HSL_FROM_RGB(RGB) UBlockbreakerBPFunctionLibrary::GetHSLFromRGB(RGB);
  UFUNCTION(Category = "Essential Math Functions|Colors")
  static FVector GetHSVFromRGB(FVector const& RGB);
#define HSV_FROM_RGB(RGB) UBlockbreakerBPFunctionLibrary::GetHSVFromRGB(RGB);
  UFUNCTION(Category = "Essential Math Functions|Colors")
    static FVector GetHSIFromRGB(FVector const& RGB);
#define HSI_FROM_RGB(RGB) UBlockbreakerBPFunctionLibrary::GetHSIFromRGB(RGB);
  UFUNCTION(Category = "Essential Math Functions|Colors")
  static FVector GetRGBFromHSL(FVector HSL);
#define RGB_FROM_HSL(HSL) UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(HSL);
  UFUNCTION(Category = "Essential Math Functions|Colors")
  static FVector GetRGBFromHSV(FVector HSV);
#define RGB_FROM_HSV(HSV) UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(HSV);
  UFUNCTION(Category = "Essential Math Functions|Colors")
  static FVector GetRGBFromHSI(FVector HSI);
#define RGB_FROM_HSI(HSI) UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(HSI);
  static float Sign(float x) { return (x < 0 ? -1 : x > 0 ? 1 : 0); }
#define SIGN(x) UBlockbreakerBPFunctionLibrary::Sign(x); 
  static float NRoot(float x, int exp, int rad);
#define NTHROOT(x, ex, rad) UBlockbreakerBPFunctionLibrary::NRoot(x, ex, rad);
};
