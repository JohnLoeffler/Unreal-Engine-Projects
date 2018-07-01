// Fill out your copyright notice in the Description page of Project Settings.

#include "HardenedBrick.h"
#include "LevelBrick.h"
#include "Components/StaticMeshComponent.h"
#include "BlockbreakerGameModeBase.h"
#include "Runtime/Engine/Classes/Sound/SoundCue.h"
#include "Runtime/Engine/Classes/Components/AudioComponent.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"

AHardenedBrick::AHardenedBrick() {
  

}

AHardenedBrick::~AHardenedBrick() {}


void AHardenedBrick::BeginPlay() {
  Super::BeginPlay();
  Init();
}

void AHardenedBrick::Tick(float DeltaTime) {
  Super::Tick(DeltaTime);
}



