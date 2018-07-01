// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelBrick.h"
#include "EmptySpace.generated.h"

/**
 * 
 */
UCLASS()
class BLOCKBREAKER_API AEmptySpace : public ALevelBrick
{
  GENERATED_BODY()

  AEmptySpace();
  
  virtual ~AEmptySpace() {}
  
  void HitByWaveform(float Force, float TimerDelay);

  virtual bool Init() override;

  virtual void Tick(float DeltaTime) override;

  virtual void BeginPlay() override;
	
};
