// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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

  UFUNCTION(BlueprintCallable, Category = "Level Design | Pattern")
    bool ResetLevelPattern();
  UFUNCTION(BlueprintCallable, Category = "Level Design | Palette")
    bool GetNewPalette();
  UFUNCTION(BlueprintCallable, Category = "Level Design | Palette")
    ULevelDesign* GetLevelDesign();


  bool ProduceLevelDesign(ULevelDesign& DesignOutput, FString LevelName = "DefaultMap", FString PaletteSeed_HexCode = "000000", FString PatternSeed = "123456789");

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
