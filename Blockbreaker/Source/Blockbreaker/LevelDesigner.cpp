// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelDesigner.h"
#include "LevelPalette.h"
#include "LevelPattern.h"
#include "LevelDesign.h"

// Sets default values
ALevelDesigner::ALevelDesigner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

  Palette = CreateDefaultSubobject<ULevelPalette>(TEXT("ColorPalette"));
  this->Design = CreateDefaultSubobject<ULevelDesign>(TEXT("LevelDesign"));
  this->Design->Width = 12;
  this->Design->Height = 16;
  FColor BaseC = FColor::MakeRandomColor();
  FLinearColor BaseLC(BaseC);
  FVector HSL(BaseLC);
  this->Design->Palette = Palette->GenerateScheme(HSL);
  if (Palette) {
    UE_LOG(LogTemp, Warning, TEXT("Palette successfully initialized in Level Designer"));
    for (int32 i = 0; i < this->Design->Palette.Num(); i++) {
      UE_LOG(LogTemp, Warning, TEXT("Color # %d : |H| %f |S| %f |L| %f"), i, this->Design->Palette[i].X, this->Design->Palette[i].Y, this->Design->Palette[i].Z);
    }
  } else {
    UE_LOG(LogTemp, Warning, TEXT("Palette NOT successfully initialized"));
  }
  Pattern = CreateDefaultSubobject<ULevelPattern>(TEXT("GridPattern"));
  if (Pattern){
    int32 Seed = 123456789;
    int32 W = 12, H = 16; 
    float High = -1.0f, Low = 1.0f;
    TArray<float> FloatPattern;
    Pattern->GeneratePattern(W, H, High, Low, FloatPattern, FMath::Rand());
    this->Design->Pattern = FloatPattern;
  }
}

bool ALevelDesigner::ResetLevelPattern()
{
  int32 Seed = 123456789;
  int32 W = 12, H = 16;
  float High = -1.0f, Low = 1.0f;
  TArray<float> FloatPattern;
  if (Pattern) {
    Pattern->GeneratePattern(W, H, High, Low, FloatPattern, FMath::Rand());
  }
  this->Design->Pattern = FloatPattern;
  return true;
}

bool ALevelDesigner::GetNewPalette()
{
  
  return true;
}

ULevelDesign * ALevelDesigner::GetLevelDesign()
{
  return this->Design;
}

bool ALevelDesigner::ProduceLevelDesign(ULevelDesign &DesignOutput, FString LevelName, FString PaletteSeed_HexCode, FString PatternSeed)
{

  return false;
}

// Called when the game starts or when spawned
void ALevelDesigner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALevelDesigner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

