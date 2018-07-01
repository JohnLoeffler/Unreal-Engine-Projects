// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BlockbreakerWorldSettings.h"
#include "Logger.h"
static Logger* _Logger = Logger::GetLogger(_INF);

class ABlockbreakerGameModeBase;
class UProjectileMovementComponent;
class UStaticMeshComponent;
class UStaticMesh;
class USkeletalMeshComponent;
class USkeletalMesh;
class UMaterialInstanceDynamic;
class UAudioComponent;
class USoundCue;
class ALevelSphere;
class ALevelPaddle;
class ALevelBrick;
class MathFunction;
class BrickLayerFunction;
class ULevelDesigner;
class ULevelFloor;
class ULevelDesign;
class ULevelPalette;
class ULevelPattern;
class ULevelPowerup;
class AMenuController;
class APaddleController;


UENUM(BlueprintType)
enum class EGameDifficulty : uint8 {
  VERYEASY UMETA(DisplayName = "Very Easy"),
  EASY UMETA(DisplayName = "Easy"),
  NORMAL UMETA(DisplayName = "Normal"),
  HARD UMETA(DisplayName = "Hard"),
  VERYHARD UMETA(DisplayName = "Very Hard")
};