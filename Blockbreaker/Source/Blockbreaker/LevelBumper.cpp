// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelBumper.h"
#include "LevelPaddle.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"

// Sets default values
ALevelBumper::ALevelBumper()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

  StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BumperStaticMesh"));
  SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BumperSkeletalMesh"));

  static ConstructorHelpers::FObjectFinder<UStaticMesh> DefaultMeshAsset(TEXT("StaticMesh'/Game/Assets/Meshes/Paddles/Bumpers/DefaultPaddleBumperCap.DefaultPaddleBumperCap'"));
  //static ConstructorHelpers::FObjectFinder<UStaticMesh> GunsMeshAsset(TEXT("StaticMesh'/Game/Assets/Meshes/Paddles/Bumpers/GunsBumperCap.DefaultPaddleBumperCap'"));

  DefaultMesh = DefaultMeshAsset.Object;
  //GunsMesh = GunsMeshAsset.Object;
  bTrailing = true;
}

bool ALevelBumper::SetActiveMesh(EBumperType Type = EBumperType::NORMAL){
  switch (Type){
    case EBumperType::GUNS:
      SkeletalMesh->SetSkeletalMesh(this->GunsMesh);
      break;
    default:
      StaticMesh->SetStaticMesh(this->DefaultMesh);
      break;
  }
  return true;
}

// Called when the game starts or when spawned
void ALevelBumper::BeginPlay(){
	Super::BeginPlay();
  StaticMesh->SetStaticMesh(DefaultMesh);
}

// Called every frame
void ALevelBumper::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
  FVector ParentPosition = ParentPaddle->GetActorLocation();
  LastParentPosition = ParentPosition.X;
  float Difference = GetActorLocation().X - ParentPosition.X;
  float DeltaMovement = ParentPosition.X - GetActorLocation().X;
  FVector BumperLocation = GetActorLocation();
  if (fabs(Difference) >= 58.0f) {
    if (bTrailing) {
      BumperLocation.X += (DeltaMovement * 0.75);
      if (fabs(Difference) >= 66.0f) {
        bTrailing = false;
      }
    } else {
      BumperLocation.X += (DeltaMovement);
      if (fabs(Difference) <= 50.0f) {
        bTrailing = true;
      }
    }
  }
}

