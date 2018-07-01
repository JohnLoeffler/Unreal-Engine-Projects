// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Blockbreaker.h"
#include "LevelBuilder.generated.h"

class ULevelDesign;
class ABlockbreakerGameModeBase;

UCLASS()
class BLOCKBREAKER_API ALevelBuilder : public AActor
{
	GENERATED_BODY()
	
public:	

	// Sets default values for this actor's properties
	ALevelBuilder();
  
  /** The Design to use for the Grid */
  class ULevelDesign *Design;
  
  /** The Array holding the Bricks for the level */
  TArray<ALevelBrick*> Bricks;

  /** A flag indicating whether or not the level has been build */
  ABlockbreakerGameModeBase* GameMode;

  /** Initializes the Builder; must be used outside of the constructor! Use it in BeginPlay() instead */
  UFUNCTION(Category = "")
    bool Init();


  

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
  /** Builds the grid for the current level from the provided design */
  UFUNCTION(BlueprintCallable)
    TArray<ALevelBrick*> BuildLevel(ULevelDesign* Design);
};
