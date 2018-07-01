// Fill out your copyright notice in the Description page of Project Settings.

#include "BlockbreakerBPFunctionLibrary.h"



float UBlockbreakerBPFunctionLibrary::NRoot(float x, int exp, int rad){
  if (rad == 0) {
    return NAN;
  } else if (rad < 0) {
    rad *= -1;
    exp *= -1;
  }
  float n = FGenericPlatformMath::Pow(x, exp);
  if (n < 0 && rad % 2 == 0) {
    return NAN;
  } else {
    float accum = n;
    for (int i = 1; i < rad; i++) {
      if (accum >= 0)
        accum = sqrt(accum);
      if (n < 0)
        accum *= -1;
    }
    return accum;
  }
}

float UBlockbreakerBPFunctionLibrary::GetSineDelta(float RunningTime, float DeltaTime) {
  return FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime);
}

float UBlockbreakerBPFunctionLibrary::GetFloatFromHex(TCHAR& ch) {
  return (float)GetIntFromHex(ch);
}

int32 UBlockbreakerBPFunctionLibrary::GetIntFromHex(TCHAR& ch) {
  const FString Hex("0123456789ABCDEF");
  int32 Val = 0;
  Hex.FindChar(ch, Val);
  return Val;
}

FVector UBlockbreakerBPFunctionLibrary::GetHSLFromRGB(FVector RGB) {
  float R = (RGB.X / 255.0f), G = (RGB.Y / 255.0f), B = (RGB.Z / 255.0f);
  float Max = FMath::Max3(R, G, B);
  float Min = FMath::Min3(R, G, B);

  float C = Max - Min;

  FVector HSL;
  float HP;

  if (C == 0.0f) {
    HP = 0.0f;
  } else if (Max == R) {
    HP = fmodf((G - B) / C, 6.0f);
  } else if (Max == G) {
    HP = (B - R) / C + 2.0f;
  } else {
    HP = (B - R) / C + 4.0f;
  }
  HSL.X = (HP * 60.0f);
  HSL.Z = (0.5f * Max + Min);
  HSL.Y = (HSL.Z == 1.0f ? 0.0f : (C / (1 - fabsf(2 * HSL.Z - 1.0f))));

  return HSL;
}


FVector UBlockbreakerBPFunctionLibrary::GetHSVFromRGB(FVector const& RGB) {
  float R = (RGB.X / 255.0f), G = (RGB.Y / 255.0f), B = (RGB.Z / 255.0f);
  float Max = FMath::Max3(R, G, B);
  float Min = FMath::Min3(R, G, B);

  float C = Max - Min;

  FVector HSV;
  float HP;

  if (C == 0.0f) {
    HP = 0.0f;
  } else if (Max == R) {
    HP = fmodf((G - B) / C, 6.0f);
  } else if (Max == G) {
    HP = (B - R) / C + 2.0f;
  } else {
    HP = (B - R) / C + 4.0f;
  }
  HSV.X = (HP * 60.0f);
  HSV.Z = Max;
  HSV.Y = (HSV.Z == 0.0f ? 0.0f : (C / HSV.Z));

  return HSV;
}

FVector UBlockbreakerBPFunctionLibrary::GetHSIFromRGB(FVector const& RGB) {
  float R = (RGB.X / 255.0f), G = (RGB.Y / 255.0f), B = (RGB.Z / 255.0f);
  float Max = FMath::Max3(R, G, B);
  float Min = FMath::Min3(R, G, B);

  float C = Max - Min;

  FVector HSI;
  float HP;

  if (C == 0.0f) {
    HP = 0.0f;
  } else if (Max == R) {
    HP = fmodf((G - B) / C, 6.0f);
  } else if (Max == G) {
    HP = (B - R) / C + 2.0f;
  } else {
    HP = (B - R) / C + 4.0f;
  }
  HSI.X = (HP * 60.0f);
  HSI.Z = (1.0 / 3.0f)*(R + G + B);
  HSI.Y = (HSI.Z == 0.0f ? 0.0f : (1 - (Min / HSI.Z)));

  return HSI;
}

FVector UBlockbreakerBPFunctionLibrary::GetRGBFromHSL(FVector HSL) {
  float R = 0.0f, G = 0.0f, B = 0.0f;
  if (HSL.Y == 0.0) {
    R = HSL.Z;
    G = HSL.Z;
    B = HSL.Z;
  } else {

    int HP = 0;
    //  Find the Chroma
    float C = (1 - fabs(2.0f*HSL.Z - 1.0f)) * HSL.Y;

    HP = static_cast<int>(HSL.X) / 60;

    float MidValue = C * (float)(1 - abs((HP % 2) - 1));

    if (HP >= 0 && HP < 1) {
      R = C; G = MidValue;
    } else if (HP >= 1 && HP < 2) {
      R = MidValue; G = C;
    } else if (HP >= 2 && HP < 3) {
      G = C; B = MidValue;
    } else if (HP >= 3 && HP < 4) {
      G = MidValue; B = C;
    } else if (HP >= 4 && HP < 5) {
      R = MidValue; B = C;
    } else {
      R = C; B = MidValue;
    }
    float Min = HSL.Z - (0.5 * C);
    R += Min ;
    G += Min;
    B += Min;
  }

  return FVector(R, G, B);
}

FVector UBlockbreakerBPFunctionLibrary::GetRGBFromHSV(FVector HSV) {
  float R = 0.0f, G = 0.0f, B = 0.0f;
  if (HSV.Y == 0.0) {
    R = HSV.Z;
    G = HSV.Z;
    B = HSV.Z;
  } else {

    int HP = 0;
    //  Find the Chroma
    float C = HSV.Z * HSV.Y;

    HP = static_cast<int>(HSV.X) / 60;

    float MidValue = C * (float)(1 - abs((HP % 2) - 1));

    if (HP >= 0 && HP < 1) {
      R = C; G = MidValue;
    } else if (HP >= 1 && HP < 2) {
      R = MidValue; G = C;
    } else if (HP >= 2 && HP < 3) {
      G = C; B = MidValue;
    } else if (HP >= 3 && HP < 4) {
      G = MidValue; B = C;
    } else if (HP >= 4 && HP < 5) {
      R = MidValue; B = C;
    } else {
      R = C; B = MidValue;
    }
    float Min = HSV.Z - C;
    R += Min;
    G += Min;
    B += Min;
  }

  return FVector(R, G, B);
}

FVector UBlockbreakerBPFunctionLibrary::GetRGBFromHSI(FVector HSI) {
  float R = 0.0f, G = 0.0f, B = 0.0f;
  if (HSI.Y == 0.0) {
    R = HSI.Z * 255.0f;
    G = HSI.Z * 255.0f;
    B = HSI.Z * 255.0f;
  } else {

    int HP = 0;
    HP = static_cast<int>(HSI.X) / 60;
    float Z = (float)(1 - abs((HP % 2) - 1));

    //  Find the Chroma
    float C = ((3.0f * HSI.Z * HSI.Y) / 1.0 + Z);

    float MidValue = C * Z;

    if (HP >= 0 && HP < 1) {
      R = C; G = MidValue;
    } else if (HP >= 1 && HP < 2) {
      R = MidValue; G = C;
    } else if (HP >= 2 && HP < 3) {
      G = C; B = MidValue;
    } else if (HP >= 3 && HP < 4) {
      G = MidValue; B = C;
    } else if (HP >= 4 && HP < 5) {
      R = MidValue; B = C;
    } else {
      R = C; B = MidValue;
    }
    float Min = HSI.Z * (1 - HSI.Y);
    R += Min;
    G += Min;
    B += Min;
  }

  return FVector(R, G, B);
}