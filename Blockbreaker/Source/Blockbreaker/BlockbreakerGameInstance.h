// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BlockbreakerGameInstance.generated.h"

UCLASS()
class BLOCKBREAKER_API UBlockbreakerGameInstance : public UGameInstance
{
  GENERATED_BODY()
public:
  FString GameFileName;
  int32 LevelNumber;
  int32 GoldScore, SilverScore, BronzeScore;
  int32 PlayerAmmo, PlayerLives, PlayerScore;
  EGameDifficulty Difficulty;

};
