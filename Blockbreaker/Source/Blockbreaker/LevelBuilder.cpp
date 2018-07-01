// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelBuilder.h"
#include "EmptySpace.h"
#include "LevelBrick.h"
#include "HardenedBrick.h"
#include "ReinforcedBrick.h"
#include "LevelPaddle.h"
#include "LevelSphere.h"
#include "LevelArch.h"
#include "LevelDesign.h"
#include "BrickLayerFunctions.h"
#include "BlockbreakerGameModeBase.h"
#include "Engine/World.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

/* Helper Functions */

//  Quickly grab the appropriate color index from the pallete based of color value
int GetColorIndex(float Value) {

  if (Value < -0.87f)
    return 0;
  else if (Value >= -0.87f && Value < -0.75f)
    return 1;
  else if (Value >= -0.75f && Value < -0.62f)
    return 2;
  else if (Value >= -0.62f && Value < -0.5f)
    return 3;
  else if (Value >= -0.5f && Value < -0.32f)
    return 4;
  else if (Value >= -0.32f && Value < -0.25f)
    return 5;
  else if (Value >= -0.25f && Value < -0.12f)
    return 6;
  else if (Value >= -0.12f && Value < -0.01f)
    return 7;
  else if (Value == 0.0f)
    return 8;
  else if (Value >= 0.12f && Value < 0.25f)
    return 9;
  else if (Value >= 0.25f && Value < 0.37f)
    return 10;
  else if (Value >= 0.37f && Value < 0.5f)
    return 11;
  else if (Value >= 0.5f && Value < 0.67f)
    return 12;
  else if (Value >= 0.67f && Value < 0.82f)
    return 13;
  else
    return 14;
}

EBrickType GetBrickType(int32 Value) {
  switch (Value) {
    case 1:  return EBrickType::STANDARD;
    case 2:  return EBrickType::HARDENED;
    case 3:  return EBrickType::REINFORCED;
    case 4:  return EBrickType::BOMB;
    default: return EBrickType::EMPTY;
  }
}

ESpecialType GetSpecialType(int32 Value) {
  switch (Value) {
    case 1:
    default: return ESpecialType::FIREBOMB;
  }

}


// Sets default values
ALevelBuilder::ALevelBuilder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

bool ALevelBuilder::Init(){
  GameMode = Cast<ABlockbreakerGameModeBase>(GetWorld()->GetAuthGameMode());
  return (GameMode != nullptr);
}


// Called when the game starts or when spawned
void ALevelBuilder::BeginPlay()
{
	Super::BeginPlay();
  if (Init()) {
    UE_LOG(LogTemp, Warning, TEXT("Builder Initialized with reference to World"));
  } else {
    UE_LOG(LogTemp, Warning, TEXT("Builder failed to get reference to World"));
  }
}

// Called every frame
void ALevelBuilder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

TArray<ALevelBrick*> ALevelBuilder::BuildLevel(ULevelDesign * Design){
  if (!Cast<ABlockbreakerGameModeBase>(GetWorld()->GetAuthGameMode())->IsGridInitialized()){

    UE_LOG(LogTemp, Warning, TEXT("%d bricks in the level according to LevelDesign"), Design->BricksInLevel);

    FVector ArchLoc(0.0f, 1700.0f, 20.0f);
    FRotator ArchRot(0.0f, 0.0f, 0.0f);
    FVector BrickLoc(0.0f, 0.0f, 0.0f);
    FRotator BrickRot(0.0f, -90.0f, 0.0f);
    FVector PaddleLoc(0.0f, 1700.0f, 84.0f);
    FRotator PaddleRot(0.0f, 0.0f, 0.0f);
    FVector SphereLoc(0.0f, 1700.0f, 104.0f);
    FRotator SphereRot(0.0f, 0.0f, 0.0f);

    FActorSpawnParameters ArchSpawnInfo;
    ArchSpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    GetWorld()->SpawnActor<ALevelArch>(ArchLoc, ArchRot, ArchSpawnInfo);

    int32 Width = Design->Width;
    int32 Height = Design->Height;
    TArray<FVector> Colors = Design->Palette;
    TArray<float> ColorPattern = Design->ColorPattern;
    TArray<int32> BrickTypes = Design->BrickTypes;
    TArray<int32> SpecialTypes = Design->SpecialTypes;

    int NumColors = Colors.Num();
    
    int32 BrickNumber = 0, ValidCounter = 240;
    for (int i : Design->BrickTypes) {
      i == 0 ? ValidCounter-- : i;
    }

    FActorSpawnParameters SpawnInfo;
    for (int i = 0; i < Height; i++) {
      for (int j = 0; j < Width; j++) {
        BrickLoc.X = 273.0f - j * 50.0f;
        BrickLoc.Y = 1700.0f;
        BrickLoc.Z = 879.0f - i * 22.0f;
        SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
        
        float ColorInfo = ColorPattern[BrickNumber];
        int32 BrickType = BrickTypes[BrickNumber];
        ALevelBrick* Brick;
        Brick = GetWorld()->SpawnActor<ALevelBrick>(BrickLoc, BrickRot, SpawnInfo);
        switch (GetBrickType(BrickType)){
          case EBrickType::STANDARD:
            Brick->SetBrickType(EBrickType::STANDARD);
            break;
          case EBrickType::HARDENED:
            Brick->SetBrickType(EBrickType::HARDENED);
            break;
          case EBrickType::REINFORCED:
            Brick->SetActorScale3D(FVector(0.95f, 0.95f, 0.80f));
            Brick->SetBrickType(EBrickType::REINFORCED);
            break;
          case EBrickType::EMPTY:
          default:
            Brick->SetBrickType(EBrickType::EMPTY);
            break;
        }
        Brick->SetBrickType(GetBrickType(BrickType));
        bool Pos = ((ColorPattern[BrickNumber] >= 0.0) ?  true : false);
//        Msg.Append((Pos ? "+" : "-"));
        int32 value = (int32)(ColorPattern[BrickNumber] * 100.0);
        if (value < 10){
//          Msg.Append(" ");
//          Msg.AppendInt(value);
        } else {
//          Msg.AppendInt(value);
        }
        
        Brick->SetBrickColor(Colors[GetColorIndex(ColorInfo)]);

        Brick->SetBrickNumber(BrickNumber);
        BrickNumber++;
        Brick->SetGameModeRef(Cast<ABlockbreakerGameModeBase>(GetWorld()->GetAuthGameMode()));
        Bricks.Add(Brick);
      }
    }
//    Msg.Append("\n");
   
    int count = 0;
    for (int i = 0; i < Height; i++) {
      for (int j = 0; j < Width; j++) {
        if (i == 0 && j == 0) { //  TOP LEFT
          Bricks[count]->AboveBrick = nullptr;
          Bricks[count]->LeftBrick = nullptr;
          Bricks[count]->RightBrick = Bricks[j+1];
          Bricks[count]->BelowBrick = Bricks[Width];
        } else if (i == 0 && j == Width-1) {  //  TOP RIGHT
          Bricks[count]->AboveBrick = nullptr;
          Bricks[count]->LeftBrick = Bricks[j-1];
          Bricks[count]->RightBrick = nullptr;
          Bricks[count]->BelowBrick = Bricks[Width+(j)];
        } else if (i == Height-1 && j == 0) {  //  BOTTOM LEFT
          Bricks[count]->AboveBrick = Bricks[i - Width];
          Bricks[count]->LeftBrick = nullptr;
          Bricks[count]->RightBrick = Bricks[(i*Width) + 1];
          Bricks[count]->BelowBrick = nullptr;
        } else if (i == Height-1 && j == Width-1) { //  BOTTOM RIGHT
          Bricks[count]->AboveBrick = Bricks[i - Width];
          Bricks[count]->LeftBrick = Bricks[i*Width + Width-2];
          Bricks[count]->RightBrick = nullptr;
          Bricks[count]->BelowBrick = nullptr;
        } else if (j == 0) {  //  LEFT EDGE
          Bricks[count]->AboveBrick = Bricks[(i-1) * Width];
          Bricks[count]->LeftBrick = nullptr;
          Bricks[count]->RightBrick = Bricks[(i*Width) + 1];
          Bricks[count]->BelowBrick = Bricks[(i + 1) * Width];
        } else if (j == Width - 1) { //  RIGHT EDGE
          Bricks[count]->AboveBrick = Bricks[(i-1) * Width + j];
          Bricks[count]->LeftBrick = Bricks[(i - 1)*Width + (j-1)];
          Bricks[count]->RightBrick = nullptr;
          Bricks[count]->BelowBrick = Bricks[((i+1)*Width) + j];
        } else if (i == 0) { //  TOP EDGE
          Bricks[count]->AboveBrick = nullptr;
          Bricks[count]->LeftBrick = Bricks[j - 1];
          Bricks[count]->RightBrick = Bricks[j + 1];
          Bricks[count]->BelowBrick = Bricks[j + Width];
        } else if (i == Height-1) { // BOTTOM EDGE
          Bricks[count]->AboveBrick = Bricks[(i - 1) * Width + j];
          Bricks[count]->LeftBrick = Bricks[(i - 1) * Width + (j-1)];
          Bricks[count]->RightBrick = Bricks[(i - 1) * Width + (j+1)];
          Bricks[count]->BelowBrick = nullptr;
        } else {  //  MIDDLE Bricks
          Bricks[count]->AboveBrick = Bricks[(i - 1) * Width + j];
          Bricks[count]->LeftBrick = Bricks[(i - 1) * Width + (j - 1)];
          Bricks[count]->RightBrick = Bricks[(i - 1) * Width + (j + 1)];
          Bricks[count]->BelowBrick = Bricks[(i + 1) * Width + j];
        }
        count++;
      }
    }
    Cast<ABlockbreakerGameModeBase>(GetWorld()->GetAuthGameMode())->ReportBuildSuccess(Design->BricksInLevel);
//    Msg.Append("----------------------------------------------------------------------\n");
//    Msg.Append("\tLevel Successfully Built!\n================================================\n");
//   LOG(_INF, Msg);
  }
  return Bricks;
}

