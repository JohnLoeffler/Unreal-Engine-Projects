// Fill out your copyright notice in the Description page of Project Settings.

#include "BrickLayerFunctions.h"
#include "BlockbreakerGameModeBase.h"
#include "LevelBrick.h"

float BrickLayerFunction::Normalize(float Value, float NewHigh, float NewLow, float OldHigh, float OldLow) {
  return((OldHigh - OldLow) == 0.0 ? NewLow : (((Value - OldLow)*(NewHigh - NewLow) / (OldHigh - OldLow)) + (NewLow)));
}

void BrickLayerFunction::Swap(int &a, int &b) {
  b = a + b;
  a = b - a;
  b = b - a;
}

void BrickLayerFunction::GetBrickValues(int &a, int &b, EGameDifficulty Dif) {
  switch (Dif) {
    case EGameDifficulty::VERYEASY:
      a = 1; b = 0;
      break;
    case EGameDifficulty::EASY:
      a = 1 + (FMath::Rand() % 2);
      b = 0;
      break;
    case EGameDifficulty::VERYHARD:
      a = 2 + (FMath::Rand() % 2);
      do {
        b = 1 + (FMath::Rand() % 2);
      } while (a == b);
      break;
    case EGameDifficulty::HARD:
      a = 1 + (FMath::Rand() % 3);
      do {
        b = (FMath::Rand() % 3);
      } while (a == b);
      break;
    default:
      a = 1 + (FMath::Rand() % 2);
      do {
        b = (FMath::Rand() % 2);
      } while (a == b);
      break;
  }
}

BrickLayerFunction::BrickLayerFunction(){ 
  EmptyAssignment = 0; 
  StandarDAssignment = 0; 
  HardenedAssignment = 0; 
  ReinforcedAssignment = 0; 
  BombAssignment = 0; 
  BonusBlockAssignment = 0; 
}

void Checkered::FindValidCheck(int H, int W){
  FString Msg = "", Msg1 = "", Msg2 = "";
  for (int i = 1; i<= H; i++){
    if (H % i == 0){
      for (int j = 1; j < W; j++){
        if (W % j == 0){
          if(i * j <= (H*W)/4){
            int num = ValidChecks.Num();
            ValidChecks.Add(Check(j, i));
          }
        }
      }
    }
  }
}

int32 BrickLayerFunction::Build(int H, int W, TArray<int32>& Bricks, int32 Seed, EGameDifficulty Dif) {
  int a, b;
  GetBrickValues(a, b, Dif);
  b == 0 ? b = 1 : b;
  for (int i = 0; i < H*W; i++) {
    if (i / W == 0 || i / W == H - 1 || i % W == 0 || i % W == W - 1) {
      Bricks.EmplaceAt(i, b);
    }
    Bricks.EmplaceAt(i, a);
  }
  return H * W;
}

int32 Checkered::Build(int H, int W, TArray<int32>& Bricks, int32 Seed, EGameDifficulty Dif){
  Check Chk;
  FindValidCheck(H, W);
  if (ValidChecks.Num() >= 1) {
    Chk = ValidChecks[Seed % ValidChecks.Num()];
  } else {
    Chk.X = 1; Chk.Y = 1;
  }
  bool Flag = false, Toggle = ( ((Chk.X*Chk.Y) == (H*W)/3) ? true : Seed%2);
  int32 ValidBricks = H*W;
  
  int a, b;
  GetBrickValues(a, b, Dif);
  for (int i = 0; i < H; i++) {
    if (i % Chk.Y == 0){
      Flag = true;
    }
    for (int j = 0; j < W; j++) {
      if (Flag) {
        Flag = false;
      } else {
        if (j % Chk.X == 0) {
          Toggle = !Toggle;
        }
      }
      if (Toggle) {
        Bricks.Add(a);
        a == 0 ? ValidBricks-- : a;
      } else {
        Bricks.Add(b);
        b == 0 ? ValidBricks-- : b;
      }
    }
  }
  return ValidBricks;
}

int32 Striped::Build(int H, int W, TArray<int32>& Bricks, int32 Seed, EGameDifficulty Dif){
  int a, b;
  int32 ValidBricks = H*W;
  GetBrickValues(a, b, Dif);

  bool Toggle = FMath::RandBool();
  int Size;
  Size = (Seed % 5) + 1;
  Size == 4 ? Size++ : Size == 2 ? Size++ : Size;
  int sum;
  for (int i = 0; i < H*W; i++){
    sum = (i/W) + (i%W);
    if ((sum % Size) < (Size/2)) {
      Bricks.EmplaceAt(i, a);
      a == 0 ? ValidBricks-- : a;
    } else {
      Bricks.EmplaceAt(i, b);
      b == 0 ? ValidBricks-- : b;
    }
  }
  return ValidBricks;
}

bool InsideCircle(int x, int y, int c) {
  int val = (int)sqrt((double)(((y*y) + ((x*x) / 2))));
  UE_LOG(LogTemp, Warning, TEXT("%d"), val);
  return (val < c) ? true :  false;
}

int32 CenterBlob::Build(int H, int W, TArray<int32>& Bricks, int32 Seed, EGameDifficulty Dif){
  UE_LOG(LogTemp, Warning, TEXT("Inside CenterBlob..."));
  int a, b;
  int32 ValidBricks = H * W;
  b = 0;
  int x = -6, y = 10, c = 5;
  GetBrickValues(a, b, Dif);
  for (int i = 0; i < H*W; i++){
    if(InsideCircle((x+(i%W)),(y-(i/W)), c)){
      Bricks.EmplaceAt(i, a);
    } else {
      Bricks.EmplaceAt(i, b);
      ValidBricks--;
    }
  }
  return ValidBricks;
}

bool IsBumper(int y, int x, bool sw){
  if ((y >= 1 && y <= 3) || (y >= 11 && y <= 13)) {
    if (sw) {
      if ((x > -1 && x < 2) || (x > 3 && x < 8) || (x > 9 && x < 12)) {
        return true;
      } else {
        return false;
      }
    } else {
      if( (x > 0 && x < 5) || (x > 6 && x < 11) ){
        return true;
      } else {
        return false;
      }
    }
  } else if((y >= 6 && y <= 8) || (y >= 16 && y <= 18)){
    if (sw) {
      if ((x > 0 && x < 5) || (x > 6 && x < 11)) {
        return true;
      } else {
        return false;
      }
    } else {
      if ((x > -1 && x < 2) || (x > 3 && x < 8) || (x > 9 && x < 12)) {
        return true;
      } else {
        return false;
      }
    }
  } else {
    return false;
  }
}

int32 Bumpers::Build(int H, int W, TArray<int32>& Bricks, int32 Seed, EGameDifficulty Dif){
  UE_LOG(LogTemp, Warning, TEXT("Inside Bumpers..."));
  int a, b;
  int32 ValidBricks = H*W;
  b = 0;
  GetBrickValues(a, b, Dif);
  for (int i = 0; i < H*W; i++){
    if (IsBumper((i / W), (i%W),(Seed % 2))){
      Bricks.EmplaceAt(i, a);
    } else {
      Bricks.EmplaceAt(i, b);
      ValidBricks--;
    }
  }
  return ValidBricks;
}

bool OuterBox(int i, int j, int H=16, int W=12) {
  if (j == 0 || j == W / 2 - 1 || j == W / 2 || j == W - 1 || i == 0 || i == H / 2 - 1 || i == H / 2 || i == H - 1) {
    return true;
  }
  return false;
}

int32 Rectangles::Build(int H, int W, TArray<int32>& Bricks, int32 Seed, EGameDifficulty Dif){
  int32 ValidBricks = H * W;
  int a, b;
 
  switch (Dif) {
    case EGameDifficulty::VERYEASY:
      a = 0; b = 1;
      break;
    case EGameDifficulty::EASY:
      a = 1 + (FMath::Rand() % 2);
      b = 0;
      break;
    case EGameDifficulty::VERYHARD:
      a = 2 + (FMath::Rand() % 2);
      do {
        b = 1 + (FMath::Rand() % 2);
      } while (a == b);
      break;
    case EGameDifficulty::HARD:
      a = 1 + (FMath::Rand() % 3);
      do {
        b = (FMath::Rand() % 3);
      } while (a == b);
      break;
    default:
      a = 1 + (FMath::Rand() % 2);
      do {
        b = (FMath::Rand() % 2);
      } while (a == b);
      break;
  }
  
  for (int i = 0; i < W*H; i++){
    if ((i / W < H / 2 && i%W < W / 2) || (i / W >= H / 2 && i%W >= W / 2)) {
      if (OuterBox((i / W), (i%W))){
        Bricks.EmplaceAt(i, a);
        a == 0 ? ValidBricks--: a;
      } else{
        Bricks.EmplaceAt(i, b);
        b == 0 ? ValidBricks-- : b;
      }
    } else {
      if (OuterBox((i / W), (i%W))) {
        Bricks.EmplaceAt(i, b);
        b == 0 ? ValidBricks-- : b;
      } else {
        Bricks.EmplaceAt(i, a);
        a == 0 ? ValidBricks-- : a;
      }
    }
  }
  return ValidBricks;
}

int32 Spiral::Build(int H, int W, TArray<int32>& Bricks, int32 Seed, EGameDifficulty Dif){
  int** grid = new int*[H];
  int i = 0, j = 0;
  for (int k = 0; k<H; k++) {
    grid[k] = new int[W];
  }
  int a, b;
  GetBrickValues(a, b, Dif);
  for(int k = 0; k < H*W; k++) {
    if (k %W == W - 1) {
      grid[k / W][k%W] = 0;
    } else {
      grid[k / W][k%W] = a;
    }
    
  }

  int ValidBricks = H*W;
  int  shortenCounter = 0, Steps = 0, XDir = 0, YDir = 0;
  int XE = W, YE = H;
  bool XBit = false, YBit = false, FirstBit = true;
  while (XE > 0 && YE > 0) {
    if (XBit == YBit) {
      Steps = XE - 2;
      XDir = (XBit == true ? -1 : 1);
      XBit = !YBit;
      YDir = 0;
    } else {
      Steps = YE - 2;
      YDir = (YBit == true ? -1 : 1);
      YBit = XBit;
      XDir = 0;
    }
    if (FirstBit) {
      Steps--;
      FirstBit = false;
    }
    while (Steps > 0) {
      grid[i][j] = 0;
      i += YDir;
      j += XDir;
      Steps--;
      ValidBricks--;
    }
    shortenCounter++;
    if (shortenCounter % 2 == 0) {
      XE -= 2;
      YE -= 2;
    }
    if (XE <= 0 || YE <= 0) {
      break;
    }
  }
  for (int k = 0; k < H*W; k++) {
    Bricks.EmplaceAt(k, grid[k / W][k%W]);
  }
  
  return ValidBricks;
}


