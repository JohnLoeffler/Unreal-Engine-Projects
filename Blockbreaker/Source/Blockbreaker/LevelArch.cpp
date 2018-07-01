// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelArch.h"
#include "LevelSphere.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Runtime/Engine/Classes/Sound/SoundCue.h"
#include "Runtime/Engine/Classes/Components/AudioComponent.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"

// Sets default values
ALevelArch::ALevelArch(){
  static ConstructorHelpers::FObjectFinder<UStaticMesh> Archmesh(TEXT(
    "StaticMesh'/Game/Assets/Meshes/LevelProps/BasicBoundingArch.BasicBoundingArch'"));
  // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
  Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ArchMesh"));
  Mesh->SetupAttachment(RootComponent);
  RootComponent = Mesh;
  
  UStaticMesh* SMesh = Archmesh.Object;
  Mesh->SetStaticMesh(SMesh);
  Mesh->SetWorldScale3D(FVector(1.25f, 1.0f, 1.25f));

  Mesh->OnComponentHit.AddDynamic(this, &ALevelArch::OnHit);

  static ConstructorHelpers::FObjectFinder<USoundCue> HitSoundCue(TEXT(
    "SoundCue'/Game/Assets/Audio/SoundEffects/ArchHitSoundCue.ArchHitSoundCue'"));

  AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
  AudioComponent->bAutoActivate = false;
  AudioComponent->SetupAttachment(RootComponent);

  this->HitSound = HitSoundCue.Object;
}

// Called when the game starts or when spawned
void ALevelArch::BeginPlay(){
	Super::BeginPlay();
  AudioComponent->SetSound(HitSound);
}

void ALevelArch::PlayHitSound(){
  AudioComponent->Play();
}

// Called every frame
void ALevelArch::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
}

void ALevelArch::OnHit_Implementation(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit){
  if (ALevelSphere* Sphere = Cast<ALevelSphere>(OtherActor)) {
    PlayHitSound();
  } 
}

