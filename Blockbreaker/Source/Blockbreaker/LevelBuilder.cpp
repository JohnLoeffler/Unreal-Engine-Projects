// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelBuilder.h"
#include "LevelBrick.h"
#include "LevelPaddle.h"
#include "LevelSphere.h"
#include "LevelArch.h"
#include "LevelDesign.h"

// Sets default values
ALevelBuilder::ALevelBuilder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ALevelBuilder::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALevelBuilder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

TArray<ALevelBrick*> ALevelBuilder::BuildLevel(ULevelDesign * Design)
{
  FVector ArchLoc(0.0f, 1700.0f, 20.0f);
  FRotator ArchRot(0.0f, 0.0f, 0.0f);
  FVector BrickLoc(0.0f, 0.0f, 0.0f);
  FRotator BrickRot(0.0f, -90.0f, 0.0f);
  FVector PaddleLoc(0.0f, 0.0f, 0.0f);
  FRotator PaddleRot(0.0f, 0.0f, 0.0f);
  FVector SphereLoc(0.0f, 0.0f, 0.0f);
  FRotator SphereRot(0.0f, 0.0f, 0.0f);

  TArray<ALevelBrick*> Bricks;

  FActorSpawnParameters ArchSpawnInfo;
  ArchSpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
  GetWorld()->SpawnActor<ALevelArch>(ArchLoc, ArchRot, ArchSpawnInfo);
  
  FActorSpawnParameters PaddleSpawnInfo;
  PaddleSpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
  GetWorld()->SpawnActor<ALevelPaddle>(PaddleLoc, PaddleRot, PaddleSpawnInfo);

  FActorSpawnParameters SphereSpawnInfo;
  SphereSpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
  GetWorld()->SpawnActor<ALevelSphere>(SphereLoc, SphereRot, SphereSpawnInfo);

  int32 Width = Design->Width;
  int32 Height = Design->Height;
  TArray<FVector> Colors = Design->Palette;
  TArray<float> Pattern = Design->Pattern;

  int NumColors = Colors.Num();
  /*
  * Here, once the the basic concept is proven, identify the color indices, and 
  *   the shader indices, and use the number of colors to determine a broad 
  *   range, with the shaders filling in the areas within those range divisions
  */
  int BrickNumber = 0;
  for (int i = 0; i < Height; i++){
    for (int j = 0; j < Width; j++) {
      FActorSpawnParameters SpawnInfo;
      BrickLoc.X = 273.0f - j * 50.0f;
      BrickLoc.Y = 1700.0f;
      BrickLoc.Z = 879.0f - i * 22.0f;
      SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
      ALevelBrick* Brick = GetWorld()->SpawnActor<ALevelBrick>(BrickLoc, BrickRot, SpawnInfo);
      float BrickInfo = Pattern[BrickNumber];
      //UE_LOG(LogTemp, Warning, TEXT("BrickInfo = %f"), BrickInfo);
      if (fabs(BrickInfo) == 1.0f || fabs(BrickInfo) == 0.5f) {
        Brick->SetBrickType(EBrickStrength::HARDENED);
      } else if (fabs(BrickInfo) == 0.25f) {
        Brick->SetBrickType(EBrickStrength::REINFORCED);
      } else if (fabs(BrickInfo) >= 0.0 && fabs(BrickInfo) < 0.25){
        Brick->SetBrickType(EBrickStrength::EMPTY);
      }else {
        Brick->SetBrickType(EBrickStrength::STANDARD);
      }
      if (BrickInfo < -0.50f) {
        Brick->SetBrickColor(Colors[0]);
      } else if(BrickInfo < -0.75f){
        Brick->SetBrickColor(Colors[1]);
      } else if(BrickInfo < 0.0f) {
        Brick->SetBrickColor(Colors[2]);
      } else if (BrickInfo == 0.25f) {
        Brick->SetBrickColors(Colors);
      } else if (BrickInfo < 0.5f){
        Brick->SetBrickColor(Colors[3]);
      } else {
        Brick->SetBrickColor(Colors[4]);
      }
      Bricks.Add(Brick);
      BrickNumber++;
    }
  }
  int Bombs = FMath::Rand() % 5;
  int SubDiv = Bricks.Num() / 5;
  for (int i = 0; i < Bombs; i++) {
    int Loc = FMath::Rand() % SubDiv + (i * SubDiv);
    if (Bricks[Loc]->Type != EBrickStrength::BOMB && Bricks[Loc]->Type != EBrickStrength::EMPTY) {
      Bricks[Loc]->SetBrickType(EBrickStrength::BOMB);
    }
  }
  return Bricks;
}

