// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelBrick.h"
#include "Components/StaticMeshComponent.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"

// Sets default values
ALevelBrick::ALevelBrick()
{
  // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

  BaseHealth = 1.0;

  Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BrickMesh"));
  Mesh->SetupAttachment(RootComponent);
  RootComponent = Mesh;

  static ConstructorHelpers::FObjectFinder<UStaticMesh> StandardMesh(TEXT("StaticMesh'/Game/Assets/Meshes/Bricks/Standard.Standard'"));
  static ConstructorHelpers::FObjectFinder<UStaticMesh> HardenedMesh(TEXT("StaticMesh'/Game/Assets/Meshes/Bricks/Hardened.Hardened'"));
  static ConstructorHelpers::FObjectFinder<UStaticMesh> ReinforcedMesh(TEXT("StaticMesh'/Game/Assets/Meshes/Bricks/Reinforced.Reinforced'"));
  static ConstructorHelpers::FObjectFinder<UStaticMesh> BombMesh(TEXT("StaticMesh'/Game/Assets/Meshes/Bricks/BaseBombBrick.BaseBombBrick'"));
  
  Standard = StandardMesh.Object;
  Hardened = HardenedMesh.Object;
  Reinforced = ReinforcedMesh.Object;
  Bomb = BombMesh.Object;
  //Mesh->SetStaticMesh(Standard);
}

bool ALevelBrick::SetBrickType(EBrickStrength Type)
{
  this->Type = Type;
  switch (Type) {
    case EBrickStrength::HARDENED:
      Mesh->SetStaticMesh(Hardened);
      this->BrickHealth = 2 * BaseHealth;
      break;
    case EBrickStrength::REINFORCED:
      Mesh->SetStaticMesh(Reinforced);
      this->BrickHealth = 3 * BaseHealth;
      break;
    case EBrickStrength::BOMB:
      Mesh->SetStaticMesh(Bomb);
      break;
    case EBrickStrength::EMPTY:
      Mesh->SetStaticMesh(nullptr);
      Mesh->SetCollisionProfileName("IgnoreAll");
      break;
    default:
    case EBrickStrength::STANDARD:
      Mesh->SetStaticMesh(Standard);
      break;
  }
  return Init();
}

// Called when the game starts or when spawned
void ALevelBrick::BeginPlay()
{
	Super::BeginPlay();

}

void ALevelBrick::SetBrickColor(FVector Color){
  if (MaterialInstances.Num() > 0) {
    MaterialInstances[0]->SetVectorParameterValue("Color", Color);
  }
}

void ALevelBrick::SetBrickColors(TArray<FVector> Colors) {
  if (MaterialInstances.Num() > 1) {
    MaterialInstances[0]->SetVectorParameterValue("Color", Colors[4]);
    MaterialInstances[1]->SetVectorParameterValue("Color", FVector(0.45f, 0.45f, 0.45f));
  }
}

bool ALevelBrick::Init(){
  TArray<UMaterialInterface*> MatInterfaces = this->Mesh->GetMaterials();
  int index = 0;
  for (UMaterialInterface* UMI : MatInterfaces) {
    MaterialInstances.Add(this->Mesh->CreateDynamicMaterialInstance(index, UMI));
    if (!MaterialInstances[index]) {
      return false;
    }
  }

  return true;
}

// Called every frame
void ALevelBrick::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
  float BHealth = BrickHealth;
  if (this->Type == EBrickStrength::REINFORCED && BrickHealth <= 2.0){
    this->SetBrickType(EBrickStrength::HARDENED);
  }
  if (this->Type == EBrickStrength::HARDENED && BrickHealth <= 1.0){
    this->SetBrickType(EBrickStrength::STANDARD);
  }
  BrickHealth = BHealth;
}

