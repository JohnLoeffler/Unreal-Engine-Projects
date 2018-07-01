// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blockbreaker.h"
#include "BlockbreakerGameModeBase.h"

class ALevelBrick;

/**
 * 
 */
class BLOCKBREAKER_API BrickLayerFunction{
protected:
  int EmptyAssignment, StandarDAssignment, HardenedAssignment, ReinforcedAssignment, BombAssignment, BonusBlockAssignment;
  float Normalize(float Value, float NewHigh, float NewLow, float OldHigh, float OldLow);
  void Swap(int &a, int &b);
  void GetBrickValues(int &a, int &b, EGameDifficulty Dif);
public:
  BrickLayerFunction();
  virtual ~BrickLayerFunction() {}

  virtual int32 Build(int H, int W, TArray<int32>& Bricks, int32 Seed, EGameDifficulty Dif = EGameDifficulty::HARD);
};

class BLOCKBREAKER_API Checkered : public BrickLayerFunction {
protected:
  struct Check {
    int X, Y;
    Check() {}
    Check(int x, int y) { X = x; Y = y; }
  };
  TArray<Check> ValidChecks;
  void FindValidCheck(int H, int W);
public:
  Checkered(){}
  ~Checkered(){}
  virtual int32 Build(int H, int W, TArray<int32>& Bricks, int32 Seed, EGameDifficulty Dif = EGameDifficulty::HARD) override;
};

class BLOCKBREAKER_API Striped : public BrickLayerFunction {
public:
  Striped() {}
  ~Striped() {}
  virtual int32 Build(int H, int W, TArray<int32>& Bricks, int32 Seed, EGameDifficulty Dif = EGameDifficulty::HARD) override;
};

class BLOCKBREAKER_API CenterBlob : public BrickLayerFunction {
public:
  CenterBlob() {}
  ~CenterBlob() {}
  virtual int32 Build(int H, int W, TArray<int32>& Bricks, int32 Seed, EGameDifficulty Dif = EGameDifficulty::HARD) override;
};

class BLOCKBREAKER_API Bumpers : public BrickLayerFunction {
public:
  Bumpers() {}
  ~Bumpers() {}
  virtual int32 Build(int H, int W, TArray<int32>& Bricks, int32 Seed, EGameDifficulty Dif = EGameDifficulty::HARD) override;
};

class BLOCKBREAKER_API Rectangles : public BrickLayerFunction {
public:
  Rectangles() {}
  ~Rectangles() {}
  virtual int32 Build(int H, int W, TArray<int32>& Bricks, int32 Seed, EGameDifficulty Dif = EGameDifficulty::HARD) override;
};

class BLOCKBREAKER_API Spiral : public BrickLayerFunction {
public:
  Spiral() {}
  ~Spiral() {}
  virtual int32 Build(int H, int W, TArray<int32>& Bricks, int32 Seed, EGameDifficulty Dif = EGameDifficulty::HARD) override;
};