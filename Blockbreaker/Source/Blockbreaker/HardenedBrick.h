// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blockbreaker.h"
#include "LevelBrick.h"
#include "HardenedBrick.generated.h"

/**
 * 
 */
UCLASS()
class BLOCKBREAKER_API AHardenedBrick : public ALevelBrick
{
  GENERATED_BODY()
protected:

      //                        //
      //  Class data fields     //
      //                        //
  bool bDevolvedToNormal;

      //                        //
      //  Cached Assets         //
      //                        //

         /* Mesh Assets    */
  UStaticMesh* HardenedMeshAsset;

         /* Audio Assets   */
  /** A Cached Reference to the Sound Cue Asset being used by HardenedBrick */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Brick|Assets")
    USoundCue* HardenedBreakSound;

public:

      //                        //
      //  Public Methods        //
      //                        //      
  AHardenedBrick();
  virtual ~AHardenedBrick();
  virtual void Tick(float DeltaTime);
  virtual void BeginPlay();
      //                        //
      //  Blueprint Native      //
      //      Events            //
      //                        //

	
	
	
};
