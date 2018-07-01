// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelDesigner.h"
#include "LevelPalette.h"
#include "LevelPattern.h"
#include "BrickLayerFunctions.h"
#include "LevelDesign.h"
#include "BlockbreakerBPFunctionLibrary.h"

// Sets default values
ALevelDesigner::ALevelDesigner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
  FString Msg ="";
  this->Design = CreateDefaultSubobject<ULevelDesign>(TEXT("LevelDesign"));
  this->Pattern = CreateDefaultSubobject<ULevelPattern>(TEXT("BrickPatterns"));
  int32 Seed = FMath::Rand();
  switch (Seed) {
    case 1:
      Palette = CreateDefaultSubobject<UComplementary>(TEXT("ColorPalette"));
      Msg.Append(TEXT("Complementary Palette\n\t"));
      break;
    case 2:
      Palette = CreateDefaultSubobject<UAnalogous>(TEXT("ColorPalette"));
      Msg.Append(TEXT("Analogous Palette\n\t"));
      break;
    case 3:
      Palette = CreateDefaultSubobject<UAccentedAnalogous>(TEXT("ColorPalette"));
      Msg.Append(TEXT("Accented Analogous Palette\n\t"));
      break;
    case 4:
      Palette = CreateDefaultSubobject<UTriadic>(TEXT("ColorPalette"));
      Msg.Append(TEXT("Triadic Palette\n\t"));
      break;
    case 5:
      Palette = CreateDefaultSubobject<UTetradic>(TEXT("ColorPalette"));
      Msg.Append(TEXT("Tetradic Palette\n\t"));
      break;
    case 0:
    default:
      Palette = CreateDefaultSubobject<UMonochrome>(TEXT("ColorPalette"));
      Msg.Append(TEXT("Monochrome Palette\n\t"));
      break;
  }

//  FString Msg = "\n==================================================\n";
  if (Design == nullptr || Pattern == nullptr || Palette == nullptr){
    Msg.Append(FString("          ERROR IN LEVEL DESIGNER \n==================================================\n"));
    if (Design == nullptr) {
      Msg.Append(FString("Design Data member did not initialize\n---------------------------------------------------\n"));
    }

    if (Pattern == nullptr) {
      Msg.Append(FString("Pattern Data member did not initialize\n---------------------------------------------------\n"));
    }

    if (Palette == nullptr) {
      Msg.Append(FString("Palette Data member did not initialize\n---------------------------------------------------\n"));
    }
    Msg.Append(FString("==================================================\n\t"));
  //  LOG(_ERR, Msg);
    UE_LOG(LogTemp, Warning, TEXT("%s"), *Msg);
  }
  Msg.Append(FString("          LEVEL DESIGNER CONSTRUCTED SUCCESSFULLY \n---------------------------------------------------\n"));
//  LOG(_INF, Msg);
  
}

bool ALevelDesigner::Init(){
  int32 Seed = FMath::Rand();
  FString Msg = "==================================================\n\t         INITIALIZING LEVEL DESIGNER \n\t---------------------------------------------------\n\t";
  bool Init = true;
  if (Design) {
    this->Design->Width = 12;
    this->Design->Height = 16;
    this->NumBricks = 0;
  } else {
    Init = false;
    LOG(_ERR, FString("---------------------------------------------------\n\tDesign Failed to Initialize!\n\t---------------------------------------------------\n\t"));
  }

  if (GetNewPalette(Seed)) {

  }else{
    Init = false;
    LOG(_ERR, FString("---------------------------------------------------\n\tPalette Failed to Initialize!\n\t---------------------------------------------------\n\t"));
    
  }
  UE_LOG(LogTemp, Warning, TEXT("Getting New Pattern..."));
  if (GetNewPattern(Seed)) {
    UE_LOG(LogTemp, Warning, TEXT("---------------------------------------------------\n\tPattern Successfully Initialized...\n\t---------------------------------------------------\n\t"));
  } else {
    Init = false;
    UE_LOG(LogTemp, Warning, TEXT("---------------------------------------------------\n\tPattern Failed to Initialize...\n\t---------------------------------------------------\n\t"));
  }
  //UE_LOG(LogTemp, Warning, TEXT("%s"), *Msg);
  return Init;
}

bool ALevelDesigner::GetNewPattern(int32 Seed = FMath::Rand()){
  UE_LOG(LogTemp, Warning, TEXT("In LevelDesigner::GetNewPattern..."));
  // TArray<float> FloatPattern;
  //TArray<int32> BrickTypes, SpecialTypes;
  for(int i = 0; i < 5000; i++){
    FMath::Rand();
  }

  if(Pattern){
    UE_LOG(LogTemp, Warning, TEXT("Getting color pattern"));
    Pattern->GenerateColorPattern(this->Design->Width, this->Design->Height, this->Design->ColorPattern, FMath::Rand());
    UE_LOG(LogTemp, Warning, TEXT("Getting brick pattern"));
    Pattern->GenerateBrickPattern(this->Design->Width, this->Design->Height, this->Design->BrickTypes, FMath::Rand());
    UE_LOG(LogTemp, Warning, TEXT("Getting special pattern"));
    Pattern->GenerateSpecialData(this->Design->Width, this->Design->Height, this->Design->SpecialTypes, FMath::Rand());
    Design->BricksInLevel = Pattern->NumberOfValidBricks;
  }else{
    UE_LOG(LogTemp, Warning, TEXT("====================================\n\tPattern was not initialized before attempting to generate data!\n\t====================================\n"));
    return false;
  }

  if(Design->ColorPattern.Num() == 0){
    UE_LOG(LogTemp, Warning, TEXT("ColorPattern is NULL"));
  }else{
    UE_LOG(LogTemp, Warning, TEXT("ColorPattern is Initialized"));
  }
  if(Design->BrickTypes.Num() == 0){
    UE_LOG(LogTemp, Warning, TEXT("BrickTypes is NULL"));
  }else{
    UE_LOG(LogTemp, Warning, TEXT("BrickTypes is Initialized"));
  }
  if(Design->SpecialTypes.Num() != 0){
    UE_LOG(LogTemp, Warning, TEXT("SpecialTypes is NULL"));
  }else{
    UE_LOG(LogTemp, Warning, TEXT("SpecialTypes is Initialized"));
  }
  return true;
}

bool ALevelDesigner::GetNewPalette(int32 Seed = FMath::Rand())
{
  /* TArray to hold colors producted by the Palette Function in RGB format */
  TArray<FVector> RGBs;
  
  /* Collects the function debug text */
  FString Msg; 
  Msg.Append("====================================\n\tUsing ");
  
    FVector RGB(FMath::FRandRange(0, 255), FMath::FRandRange(0, 255), FMath::FRandRange(0, 255));
    FVector HSL = HSL_FROM_RGB(RGB);

    RGBs = Palette->GenerateScheme(HSL);
    this->Design->Palette = RGBs;
    for (int32 i = 0; i < this->Design->Palette.Num(); i++) {
      char Buffer[512];
      int32 size = sprintf_s(Buffer,
        "--------------------------------------------------\n\tColor # %d : |R| %f |G| %f |B| %f\n\t--------------------------------------------------\n",
        i, this->Design->Palette[i].X, this->Design->Palette[i].Y, this->Design->Palette[i].Z);
      Msg = FString(Buffer);
      UE_LOG(LogTemp, Warning, TEXT("%s"), *Msg);
    }

    
  Msg = ("==================================================\n\tPalette SUCCESSFULLY initialized\n==================================================\n");
  //LOG(_INF, Msg);
  UE_LOG(LogTemp, Warning, TEXT("%s"), *Msg);
  return true;
}

ULevelDesign * ALevelDesigner::GetLevelDesign(){return this->Design;}

// Called when the game starts or when spawned
void ALevelDesigner::BeginPlay(){
	Super::BeginPlay();
  if (Init()) {
    //LOG(_INF, FString("\n==================================================\n\tLEVEL DESIGNER SUCCESSFULLY INITIALIZED\n==================================================\n"));
    UE_LOG(LogTemp, Warning, TEXT("\n==================================================\n\tLEVEL DESIGNER SUCCESSFULLY INITIALIZED\n==================================================\n"));
  } else {
    //LOG(_ERR, FString("==================================================\n\tLEVEL DESIGNER NOT SUCCESSFULLY INITIALIZED\n==================================================\n"));
    //UE_LOG(LogTemp, Warning, TEXT("%s"), *Msg);
  }
}

// Called every frame
void ALevelDesigner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

