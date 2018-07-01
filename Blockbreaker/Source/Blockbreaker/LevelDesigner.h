// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Blockbreaker.h"
#include "LevelDesigner.generated.h"

class ULevelDesign;

UCLASS()
class BLOCKBREAKER_API ALevelDesigner : public AActor
{
	GENERATED_BODY()
	
public:	

  class ULevelDesign* Design;
  class ULevelPalette* Palette;
  class ULevelPattern* Pattern;

  // Sets default values for this actor's properties
	ALevelDesigner();

  bool Init();

  UFUNCTION(BlueprintCallable, Category = "Level Design | Pattern")
    bool GetNewPattern(int32 Seed);
  UFUNCTION(BlueprintCallable, Category = "Level Design | Palette")
    bool GetNewPalette(int32 Seed);
  
  UFUNCTION(BlueprintCallable, Category = "Level Design | Palette")
    ULevelDesign* GetLevelDesign();
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
    int32 NumBricks;

  //bool ProduceLevelDesign(ULevelDesign& DesignOutput, FString LevelName = "DefaultMap", FString PaletteSeed_HexCode = "000000", FString PatternSeed = "123456789");

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
