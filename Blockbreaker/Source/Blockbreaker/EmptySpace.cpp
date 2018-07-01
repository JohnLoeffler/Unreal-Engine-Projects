// Fill out your copyright notice in the Description page of Project Settings.

#include "EmptySpace.h"

AEmptySpace::AEmptySpace() : Super() {
  this->Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
  this->SetActorEnableCollision(false);
  //SetActorHiddenInGame(true);
}



void AEmptySpace::HitByWaveform(float Force, float TimerDelay){
  return;
}

bool AEmptySpace::Init()
{
  return false;
}

void AEmptySpace::Tick(float DeltaTime)
{
}

void AEmptySpace::BeginPlay()
{
}
